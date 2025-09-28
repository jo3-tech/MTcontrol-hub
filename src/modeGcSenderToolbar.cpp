// Copyright (C) 2017 - 2018 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//HEADER FILE
//=======================================================================================================================================

#include "modeGcSenderToolbar.h"

//GLOBAL VARIABLES & CONSTANTS
//=======================================================================================================================================

//Toolbar and Tool Control
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const char* gCodeSenderToolbarName = "G-Code Sender";
const float gCodeSenderToolbarPosX = 100.0, gCodeSenderToolbarPosY = 25.0;
const ImVec2 gCodeSenderToolbarPos = {gCodeSenderToolbarPosX, gCodeSenderToolbarPosY};

const float gCodeSenderToolsSpacing = 50.0;
const int gCodeSenderToolsMessageSize = generalToolMessageSize;
const char* userInputToolsAreaName = "User Input Tools Area";
ImVec2 userInputToolsAreaSize = {0, 70};

string commandHistory = "";
string oldCommandHistory = "";
bool sendingFileData = false;
bool deviceReadyForNextLine = false;
bool autoScroll = true;

//Command
//-------

const char* commandToolName = ":Command";
const float commandToolPosX = 0.0, commandToolPosY = 0.0;
const ImVec2 commandToolPos = {commandToolPosX, commandToolPosY};
const int commandMessageBufferSize = 63;    //Max no. of G-code message characters (from one line of code) to store.
char commandMessageBuffer[commandMessageBufferSize] = "Manual Entry of G- or M-codes Here";

//Auto scroll
//-----------

const char* autoScrollToolname = "Auto scroll";
const float autoScrollToolPosX = 600.0, autoScrollToolPosY = commandToolPosY;
const ImVec2 autoScrollToolPos = {autoScrollToolPosX, autoScrollToolPosY};

//Load file
//---------

char* loadFileToolName = "Load";
const float loadFileToolPosX = commandToolPosX, loadFileToolPosY = 25.0;
const ImVec2 loadFileToolPos = {loadFileToolPosX, loadFileToolPosY};

ofBuffer inFileBuffer;            //Common variable defintion. Buffer to store input file data.
string inFilePath;				  //Common variable defintion.

//Load file info
//--------------

string inFileInfo = "No file loaded."; //Common variable defintion.

const float inFileInfoPosX = commandToolPosX, inFileInfoPosY = loadFileToolPosY + 25;
const ImVec2 inFileInfoPos = {inFileInfoPosX, inFileInfoPosY};

//Load file flags
//---------------

bool inFilePathLoaded = false;    //Common variable defintion.

//Send file
//---------

const char* sendFileToolName = "Send";
const char* stopFileToolName = "Stop";
const float sendFileToolPosX = loadFileToolPosX + gCodeSenderToolsSpacing, sendFileToolPosY = loadFileToolPosY;
const ImVec2 sendFileToolPos = {sendFileToolPosX, sendFileToolPosY};

//Resume file
//-----------

const char* resumeFileToolName = "Resume";
const char* pauseFileToolName = "Pause";
const float resumeFileToolPosX = sendFileToolPosX + gCodeSenderToolsSpacing, resumeFileToolPosY = loadFileToolPosY;
const ImVec2 resumeFileToolPos = {resumeFileToolPosX, resumeFileToolPosY};

//Console
//-------

const char* consoleToolName = "Console";

//Update robot pose
//-----------------

unsigned char updateRobotPoseMessage[gCodeSenderToolsMessageSize] = {'M', '0', '1', '6', '\n'};

//FUNCTION IMPLEMENTATIONS
//=======================================================================================================================================

//Toolbar
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void gcSenderToolbar(){
//---------------------------------------------------------------------------------------------------------------------------------------

ImGui::SetCursorPos(gCodeSenderToolbarPos);

if(MODE_MENU != Gcode_Sender)
{
	ImGui::PushStyleColor(ImGuiCol_Button, toolbarColour);
	if(ImGui::Button(gCodeSenderToolbarName))		//Show g-code sender toolbar.
	{
		if(currentModeBusy == true)
		{
			displayBusyPopup = true;
		}
		else
		{
			MODE_MENU = Gcode_Sender;
			//serial.flush(true, true);	//Clear the incoming and outgoing serial buffers.
		}
	}
	ImGui::PopStyleColor();

}
else if(MODE_MENU == Gcode_Sender)
{
	ImGui::PushStyleColor(ImGuiCol_Button, toolbarActiveColour);
	ImGui::Button(gCodeSenderToolbarName);			//Show highlighted g-code sender toolbar.
	ImGui::PopStyleColor();

	ImGui::BeginChild(gCodeSenderToolbarName);		//Show g-code sender tools in a sub-window.

		ImGui::BeginChild(userInputToolsAreaName, userInputToolsAreaSize);		//Show command tool in a sub-window.

			//Tools
			//-----

			//Check for/read serial messages from device
			
			readDeviceMessages();

			//Command

			commandTool();

			ImGui::SetCursorPos(autoScrollToolPos);
			ImGui::Checkbox(autoScrollToolname, &autoScroll);

			//Load file

			loadFileTool(inFileInfo, inFilePath, inFilePathLoaded, inFileBuffer, loadFileToolName, loadFileToolPos);

			//Loaded file info
			const char* tempInFileInfo = inFileInfo.c_str();

			ImGui::SetCursorPos(inFileInfoPos);
			ImGui::Text(tempInFileInfo);

			//Send file, stop file, resume file tools

			sendResumeStopFileTool();

			//Send serial messages to device

			sendDeviceMessages();

		ImGui::EndChild(); //End of ImGui::BeginChild(userInputToolsAreaName...);

		//Console

		consoleTool();

		//Reset g-code sender parameters

		if(serial.isInitialized() == false)
		{ resetGcSenderParameters();	}

	ImGui::EndChild(); //End of ImGui::BeginChild(gCodeSenderToolbarName);	

} //End of else if(MODE_MENU == Gcode_Sender)

} //End of void gcSenderToolbar()

//Tools
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void consoleTool(){
//---------------------------------------------------------------------------------------------------------------------------------------
ImGui::BeginChild(consoleToolName);

	const char* tempCommandHistory = commandHistory.c_str();		//Convert string to const char*
	const char* tempOldCommandHistory = oldCommandHistory.c_str();

	ImGui::TextUnformatted(tempOldCommandHistory);
	ImGui::TextUnformatted(tempCommandHistory);
	ImGui::TextUnformatted("\n\n\n");

	//ImGui::Text(tempOldCommandHistory);
	//ImGui::Text(tempCommandHistory);
	//ImGui::Text("\n\n\n");

	if(commandHistory.length() >= 20000)		//5000 //If using ImGui::Text(...)
	{
		oldCommandHistory = commandHistory;
		commandHistory = "";	//Clear the command history so it doesn't grow too large.
		//This was originally done because the display of text stops after about 5000 characters although 
		//the program continues to work. There is a limit on the size of text ImGui::Text(..) can display
		//as it uses a buffer (which has a size limit).
				
		//Although ImGui::TextUnformatted(...) (which has no size limit) is now being used, this is still
		//useful as it may slow down the program or crash after a while if the command histroy is not clamped.
	}		

	if(autoScroll == true)
	{
		ImGui::SetScrollHere();
	}

	ImGui::EndChild(); //End of ImGui::BeginChild(consoleToolName);

} //End of void consoleTool()

void commandTool(){
//---------------------------------------------------------------------------------------------------------------------------------------
//Command tool pseudo-code:
//Check if enter is pressed on the command tool,
//  if pressed, check if a file is being sent,
//    if file not being sent, send input text message.
//		add current input text to the command history with "\n" and ">" character.
//		autoselect the current text in the command tool (incase the user wants to replace the entire text with new text).
//		set the keyboard focus to the current widget (i.e the command tool) to prevent the cursor from leaving (so further text can be input if required).
//    else if file is being sent,
//		manually input messages are not sent.
//(Display of the tool is performed in the clicked checks.)

ImGui::SetCursorPos(commandToolPos);
if(ImGui::InputText(commandToolName, commandMessageBuffer, commandMessageBufferSize, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
{
	if(sendingFileData == false)
	{
		int index = 0;
		while(true)
		{
			if((commandMessageBuffer[index] == '\0') || (index >= commandMessageBufferSize))
			{
				serial.writeByte('\n');
				commandHistory = commandHistory + ">>" + commandMessageBuffer + "\n";
				break;
			}
			serial.writeByte(commandMessageBuffer[index]);
			index++;
		}
		/*
		//Alternative to using the while loop above
		//unsigned char* tempMessageBuffer = (unsigned char*)commandMessageBuffer;

		serial.writeBytes(&tempMessageBuffer[0], commandMessageBufferSize);
		commandHistory = ">>" + commandHistory + commandMessageBuffer + "\n";
		//*/

		//cout << commandMessageBuffer << endl;

		ImGui::SetKeyboardFocusHere();
	}
	else
	{
		//Manually input g-code message will not be sent while a file is being sent.
		//**Later buttons cann be added to allow the user to change speed, etc while the file is being sent.**
	}
}

} //End of void commandTool()

void sendResumeStopFileTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

if(sendingFileData == false)
{
	ImGui::SetCursorPos(sendFileToolPos);
	if(ImGui::Button(sendFileToolName))
	{
		if(inFilePathLoaded == true)
		{
			inFileBuffer = ofBufferFromFile(inFilePath);	//This is the only way I could find to reset the iterator so it starts sending form the beginning.

			deviceReadyForNextLine = true;
			sendingFileData = true; currentModeBusy = true;
			serial.writeBytes(&updateRobotPoseMessage[0], gCodeSenderToolsMessageSize);
			//cout << "file loaded" << endl;
		}
	}

	ImGui::SetCursorPos(resumeFileToolPos);
	if(ImGui::Button(resumeFileToolName))
	{
		if(inFilePathLoaded == true)
		{
			sendingFileData = true; currentModeBusy = true;
		}
	}
} //End of if(sendingFileData == false)
else
{
	ImGui::SetCursorPos(sendFileToolPos);
	if(ImGui::Button(stopFileToolName))
	{
		sendingFileData = false; currentModeBusy = false;
		serial.writeBytes(&updateRobotPoseMessage[0], gCodeSenderToolsMessageSize);
	}

	ImGui::SetCursorPos(resumeFileToolPos);
	if(ImGui::Button(pauseFileToolName))
	{
		sendingFileData = false; currentModeBusy = true;	
	}
}

} //End of void sendResumeStopFileTool()


//Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void readDeviceMessages(){
//---------------------------------------------------------------------------------------------------------------------------------------

//*
while(serial.available() > 0)
{
	char c = serial.readByte(); //Read a character/byte of data.
	commandHistory = commandHistory + c;
	//cout << "reading byte" << endl;
	//cout << c << endl;

	if(c == deviceReadyMessage)
	{
		deviceReadyForNextLine = true;
		//cout <<" ready for next line" << endl;
	}
}
//*/

} //End of void readDeviceMessages()


void sendDeviceMessages(){
//---------------------------------------------------------------------------------------------------------------------------------------

if(sendingFileData == true)
{
	if(deviceReadyForNextLine == true)
	{
		serial.flush(true, true);	//Clear the incoming and outgoing serial buffers.

		string fileMessageBuffer = inFileBuffer.getNextLine();

		int fileMessageBufferSize = strlen(fileMessageBuffer.c_str());

		commandHistory = commandHistory + ">>" + fileMessageBuffer;

		//cout << "next line loaded" << endl;
		//cout << "line size = " << fileMessageBufferSize << endl;

		int index = 0;
		while(true)
		{
			if(index >= fileMessageBufferSize)
			{
				serial.writeByte('\n');
				commandHistory = commandHistory + "\n";
				//cout << "breaking because buffer end reached" << endl;
				break;
			}

			serial.writeByte(fileMessageBuffer[index]);

			index++;
		}
		deviceReadyForNextLine = false;

		//cout << fileMessageBuffer << endl;

		if(inFileBuffer.isLastLine())
		{
			sendingFileData = false; currentModeBusy = false;
			serial.writeBytes(&updateRobotPoseMessage[0], gCodeSenderToolsMessageSize);
		}
	} //End of if(deviceReadyForNextLine == true)
} //End of if(sendingFileData == true)

} //End of void sendDeviceMessages()

void resetGcSenderParameters(){
//---------------------------------------------------------------------------------------------------------------------------------------

if(serial.isInitialized() == false)
{
	sendingFileData = false;
	deviceReadyForNextLine = false;
}

} //End of void resetGcSenderParameters()