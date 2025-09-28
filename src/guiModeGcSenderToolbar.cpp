// Copyright (C) 2017 - 2020 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//HEADER FILE
//=======================================================================================================================================

#include "guiModeGcSenderToolbar.h"

//GLOBAL VARIABLES & CONSTANTS
//=======================================================================================================================================

//General
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

string guiCommandHistory = "";
string guiOldCommandHistory = "";

//Control Flags/Indicator Variables
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool guiSendingFileData = false;
bool guiDeviceReadyForNextLine = false;
bool guiAutoScroll = true;

//Toolbar
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//G-code Sender
//+++++++++++++

const float guiGcSenderToolsSpacingX = 2.0; //*guiScaleFactor.
const float guiGcSenderToolsSpacingY = 2.0; // "

const int guiGcSenderToolsMessageSize = guiGeneralToolMessageSize;

//Tools and Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Command
//+++++++

const char* guiCommandToolName = "Command";
const int guiCommandMessageBufferSize = 63; //Max no. of G-code message characters (from one line of code) to store.
char guiCommandMessageBuffer[guiCommandMessageBufferSize] = "Manual Entry of G-, R- or M-codes Here";

//Auto Scroll
//+++++++++++

const char* guiAutoScrollToolname = "Auto scroll";

//Load File
//+++++++++

char* guiLoadFileToolName = "Load File";

//Send File
//+++++++++

const char* guiSendFileToolName = "Send";
const char* guiStopFileToolName = "Stop";

//Resume File
//+++++++++++

const char* guiResumeFileToolName = "Resume";
const char* guiPauseFileToolName = "Pause";

//Console
//+++++++

const char* guiConsoleToolName = "Console";

unsigned char guiUpdateRobotPoseMessage[guiGcSenderToolsMessageSize] = {'R', '0', '1', '0', '\n'};

//FUNCTION IMPLEMENTATIONS
//=======================================================================================================================================

//Toolbar
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiGcSenderToolbar(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display G-code sender toolbar.

if(guiModeMenuToolbarId == guiGcSenderToolbarId)
{
	//Tools and Tool Actions
	//----------------------

	guiGeneralGuiVerticalSpacing(guiGcSenderToolsSpacingY/2);

	{ //User input tools group
	ImGui::BeginGroup();
			
		guiReadDeviceMessages(); //Check for/read guiSerial messages from device.

		guiCommandTool();

		guiGeneralGuiHorizontalSpacing(guiGcSenderToolsSpacingX); //Show the next tool on the same line.
		ImGui::Checkbox(guiAutoScrollToolname, &guiAutoScroll);

		guiLoadFileTool();

		guiGeneralGuiHorizontalSpacing(guiGcSenderToolsSpacingX);
		guiSendResumeStopFileTool();

		guiSendDeviceMessages(); //Send guiSerial messages to device.

		const char* tempInFileInfo = guiInFileInfo.c_str(); //Convert c++ string to c-string required by ImGui::Text(...).
		ImGui::Text(tempInFileInfo); //Display loaded file info.

	ImGui::EndGroup(); 
	}

	guiConsoleTool();

	if(guiSerial.isInitialized() == false)
	{ guiResetGcSenderParameters(); } //Reset g-code sender parameters if connection is lost.

} //End of else if(guiModeMenuToolbarId == guiGcSenderToolbarId)

} //End of void guiGcSenderToolbar()

//Tools
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiCommandTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to input G-code commands.
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

ImGui::SetNextItemWidth(26*guiScaleFactor);

if(ImGui::InputText(guiCommandToolName, guiCommandMessageBuffer, guiCommandMessageBufferSize, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsUppercase))
{
	if(guiSendingFileData == false)
	{
		int index = 0;
		while(true)
		{
			if((guiCommandMessageBuffer[index] == '\0') || (index >= guiCommandMessageBufferSize))
			{
				guiSerial.writeByte('\n');
				guiCommandHistory = guiCommandHistory + ">>" + guiCommandMessageBuffer + "\n";
				break;
			}
			guiSerial.writeByte(guiCommandMessageBuffer[index]);
			index++;
		}
		
		//TESTING.
		//Alternative to using the while loop above
		//unsigned char* tempMessageBuffer = (unsigned char*)guiCommandMessageBuffer;

		//guiSerial.writeBytes(&tempMessageBuffer[0], guiCommandMessageBufferSize);
		//guiCommandHistory = ">>" + guiCommandHistory + guiCommandMessageBuffer + "\n";
		
		//DEBUGGING.
		//cout << guiCommandMessageBuffer << endl;

		ImGui::SetKeyboardFocusHere();
	}
	else
	{
		//Manually input g-code message will not be sent while a file is being sent.

		//DEFERRED.
		//Later buttons can be added to allow the user to change speed, etc while the file is being sent.
	}

} //End of if(ImGui::InputText(guiCommandToolName, ...)

} //End of void guiCommandTool()

void guiLoadFileTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to load file from directory via system dialogue.

if(ImGui::Button(guiLoadFileToolName))
{
	bool newFileLoaded = guiLoadFileViaDialogue(guiInFileInfo, guiInFilePath, guiInFileBuffer);
	
	if(newFileLoaded == true){ guiInFilePathLoaded = true; }
}

}

void guiSendResumeStopFileTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to send (or stop) and resume sending G-code commands from file.

if(guiSendingFileData == false)
{
	if(ImGui::Button(guiSendFileToolName))
	{
		if(guiInFilePathLoaded == true)
		{
			guiInFileBuffer = ofBufferFromFile(guiInFilePath); //This reloads the file into the buffer. It achieves the same result of
														 //resetting the iterator but is a bit overkill since the file is already loaded.
														 //However there doesn't seem to be another way as begin() doesn't work.	
			guiDeviceReadyForNextLine = true;
			guiSendingFileData = true; guiCurrentModeBusy = true;
			guiSerial.writeBytes(&guiUpdateRobotPoseMessage[0], guiGcSenderToolsMessageSize);

			//DEBUGGING.
			//cout << "file loaded" << endl;
		}
	}

	guiGeneralGuiHorizontalSpacing(guiGcSenderToolsSpacingX);

	if(ImGui::Button(guiResumeFileToolName))
	{
		if(guiInFilePathLoaded == true)
		{
			guiSendingFileData = true; guiCurrentModeBusy = true;
		}
	}

} //End of if(guiSendingFileData == false)
else
{
	if(ImGui::Button(guiStopFileToolName))
	{
		guiSendingFileData = false; guiCurrentModeBusy = false;
		guiSerial.writeBytes(&guiUpdateRobotPoseMessage[0], guiGcSenderToolsMessageSize);
	}

	guiGeneralGuiHorizontalSpacing(guiGcSenderToolsSpacingX);

	if(ImGui::Button(guiPauseFileToolName))
	{
		guiSendingFileData = false; guiCurrentModeBusy = true;	
	}
}

} //End of void guiSendResumeStopFileTool()

void guiConsoleTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to show (in a console) G-code commands being sent to device.

ImGui::BeginChild(guiConsoleToolName); //Show console tool in a sub-window.

	const char* tempCommandHistory = guiCommandHistory.c_str(); //Convert c++ string to c-string required by ImGui::TextUnformatted(...).
	const char* tempOldCommandHistory = guiOldCommandHistory.c_str();

	ImGui::TextUnformatted(tempOldCommandHistory);
	ImGui::TextUnformatted(tempCommandHistory);
	ImGui::TextUnformatted("\n\n\n");
	
	//TESTING.
	//ImGui::Text(tempOldCommandHistory);
	//ImGui::Text(tempCommandHistory);
	//ImGui::Text("\n\n\n");

	if(guiCommandHistory.length() >= 20000) //5000 //If using ImGui::Text(...) - TESTING.
	{
		guiOldCommandHistory = guiCommandHistory;
		guiCommandHistory = ""; //Clear the command history so it doesn't grow too large.

		//NOTE:
		//This was originally done because the display of text stops after about 5000 characters although 
		//the program continues to work. There is a limit on the size of text ImGui::Text(..) can display
		//as it uses a buffer (which has a size limit).
				
		//Although ImGui::TextUnformatted(...) (which has no size limit) is now being used, this is still
		//useful as it may slow down the program or crash after a while if the command histroy is not clamped.
	}		

	if(guiAutoScroll == true)
	{
		ImGui::SetScrollHere();
	}

ImGui::EndChild();

} //End of void guiConsoleTool()

//Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiReadDeviceMessages(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Read guiSerial messages from device.

//DEFERRED. guiInfoMenu.
//if(guiVersionInfoObtained == false){ return; } //Wait until the robot has started up and the info menu has read the version info.

while(guiSerial.available() > 0)
{
	char c = guiSerial.readByte(); //Read a character/byte of data.
	guiCommandHistory = guiCommandHistory + c;

	//DEBUGGING.
	//cout << "reading byte" << endl;
	//cout << c << endl;

	if(c == guiDeviceReadyMessage)
	{
		guiDeviceReadyForNextLine = true;
		
		//DEBUGGING.
		//cout <<" ready for next line" << endl;
	}
}

}

void guiSendDeviceMessages(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Send guiSerial messages to device.

if(guiSendingFileData == true)
{
	if(guiDeviceReadyForNextLine == true)
	{
		string fileMessageBuffer = guiInFileBuffer.getNextLine();

		int fileMessageBufferSize = strlen(fileMessageBuffer.c_str());

		guiCommandHistory = guiCommandHistory + ">>" + fileMessageBuffer;

		//DEBUGGING.
		//cout << "next line loaded" << endl;
		//cout << "line size = " << fileMessageBufferSize << endl;

		int index = 0;
		while(true)
		{
			if(index >= fileMessageBufferSize)
			{
				guiSerial.writeByte('\n');
				guiCommandHistory = guiCommandHistory + "\n";

				//DEBUGGING.
				//cout << "breaking because buffer end reached" << endl;
				
				break;
			}

			guiSerial.writeByte(fileMessageBuffer[index]);

			index++;
		}

		guiDeviceReadyForNextLine = false;

		//DEBUGGING.
		//cout << fileMessageBuffer << endl;

		if(guiInFileBuffer.isLastLine())
		{
			guiSendingFileData = false; guiCurrentModeBusy = false;
			guiSerial.writeBytes(&guiUpdateRobotPoseMessage[0], guiGcSenderToolsMessageSize);
		}

	} //End of if(guiDeviceReadyForNextLine == true)

} //End of if(guiSendingFileData == true)

} //End of void guiSendDeviceMessages()

void guiResetGcSenderParameters(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Reset G-code sender parameters.

if(guiSerial.isInitialized() == false)
{
	guiSendingFileData = false;
	guiDeviceReadyForNextLine = false;
	guiCurrentModeBusy = false;
}

}
