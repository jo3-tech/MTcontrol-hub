// Copyright (C) 2017 - 2018 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//HEADER FILE
//=======================================================================================================================================

#include "modeJogToolbar.h"

//GLOBAL VARIABLES & CONSTANTS
//=======================================================================================================================================

//Toolbar and Tool Control
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const char* jogMachineToolbarName = "Jog Machine";
const float jogMachineToolbarPosX = 8.0, jogMachineToolbarPosY = 25.0;
const ImVec2 jogMachineToolbarPos = {jogMachineToolbarPosX, jogMachineToolbarPosY};

const float jogMachineToolsSpacing = 50.0;
const int jogMachineToolsMessageSize = generalToolMessageSize;

const char idleMessage = '0';

//Keyboard input
//--------------

const int upKey = OF_KEY_UP, leftKey = OF_KEY_LEFT, rightKey = OF_KEY_RIGHT, downKey = OF_KEY_DOWN;
//OR
//const int upKey = 357, leftKey = 356, rightKey = 358, downKey = 359;

//'1' = 49, '2' = 50, '3' = 51, '4' = 52, '5' = 53, '6' = 54  As per the ASCII table
const int oneKey = '1', twoKey = '2', threeKey = '3', fourKey = '4';

bool upKeyHeld = false;
bool leftKeyHeld = false;
bool rightKeyHeld = false;
bool downKeyHeld = false;

//Reset jog parameters
//--------------------

unsigned char resetJogParametersMessage[jogMachineToolsMessageSize] = {'J', '2', '5', '5', '\n'};

//Auto calibrate
//--------------

char* autoCalibrateToolName = "Auto Calibration";
unsigned char autoCalibrateToolMessage[jogMachineToolsMessageSize] = {'J', '2', '5', '4', '\n'};
const float autoCalibrateToolPosX = 180.0, autoCalibrateToolPosY = 20.0;
const ImVec2 autoCalibrateToolPos = {autoCalibrateToolPosX, autoCalibrateToolPosY};

const char calibrationCompleteMessage = '}';
const char endCalibrationMessage = '{';

//Auto calibrate flags
//--------------------

bool calibrating = false;

//Select jog speed
//----------------

char* selectJogSpeedToolName = "Joint \nJog \nSpeed (%)";
unsigned char selectJogSpeedToolMessage[jogMachineToolsMessageSize] = {'J', '2', '5', '3', ' '};	//NOTE: '\n' is left out on purpose since the jog speed will be sent after this message.
const float selectJogSpeedToolPosX = autoCalibrateToolPosX - 130.0, selectJogSpeedToolPosY = autoCalibrateToolPosY + jogMachineToolsSpacing;
const ImVec2 selectJogSpeedToolPos = {selectJogSpeedToolPosX, selectJogSpeedToolPosY};
const ImVec2 selectJogSpeedToolSize = {50, 50};

const int defaultJogSpeed = 50;			//(%)
int currentJogSpeed = defaultJogSpeed;	//(%)
const int minJogSpeed = 0;				//(%)
const int maxJogSpeed = 100;			//(%)

//Select jog speed flags
//----------------------

bool selectJogSpeedToolHeld = false; 
bool sendJogSpeed = false;

//Up
//--

char* upToolName = "Up";
unsigned char upToolMessage[jogMachineToolsMessageSize] = {'J', '0', '1', '3', '\n'};
const float upToolPosX = selectJogSpeedToolPosX + 180.0, upToolPosY = selectJogSpeedToolPosY;
const ImVec2 upToolPos = {upToolPosX, upToolPosY};

//Up flags
//--------

bool upToolHeld = false;

//Left
//----

char* leftToolName = "Left";
unsigned char leftToolMessage[jogMachineToolsMessageSize] = {'J', '0', '1', '1', '\n'};
const float leftToolPosX = upToolPosX - 38.0, leftToolPosY = upToolPosY + 25.0;
const ImVec2 leftToolPos = {leftToolPosX, leftToolPosY};

//Left flags
//----------

bool leftToolHeld = false;

//Right
//-----

char* rightToolName = "Right";
unsigned char rightToolMessage[jogMachineToolsMessageSize] = {'J', '0', '1', '2', '\n'};
const float rightToolPosX = upToolPosX + 22.0, rightToolPosY = leftToolPosY;
const ImVec2 rightToolPos = {rightToolPosX, rightToolPosY};

//Right flags
//-----------

bool rightToolHeld = false;

//Down
//----

char* downToolName = "Down";
unsigned char downToolMessage[jogMachineToolsMessageSize] = {'J', '0', '1', '4', '\n'};
const float downToolPosX = upToolPosX - 7.0, downToolPosY = leftToolPosY + 25.0;
const ImVec2 downToolPos = {downToolPosX, downToolPosY};

//Down flags
//----------

bool downToolHeld = false;

//Select joint 1
//--------------

char* selectJointOneToolName = "Select Joint 1";
unsigned char selectJointOneToolMessage[jogMachineToolsMessageSize] = {'J', '0', '0', '1', '\n'};
const float selectJointOneToolPosX = rightToolPosX + 80.0, selectJointOneToolPosY = upToolPosY - 15.0;
const ImVec2 selectJointOneToolPos = {selectJointOneToolPosX, selectJointOneToolPosY};

//Select joint 2
//--------------

char* selectJointTwoToolName = "Select Joint 2";
unsigned char selectJointTwoToolMessage[jogMachineToolsMessageSize] = {'J', '0', '0', '2', '\n'};
const float selectJointTwoToolPosX = selectJointOneToolPosX, selectJointTwoToolPosY = selectJointOneToolPosY + jogMachineToolsSpacing;
const ImVec2 selectJointTwoToolPos = {selectJointTwoToolPosX, selectJointTwoToolPosY};

//Select joint 3
//--------------

char* selectJointThreeToolName = "Select Joint 3";
unsigned char selectJointThreeToolMessage[jogMachineToolsMessageSize] = {'J', '0', '0', '3', '\n'};
const float selectJointThreeToolPosX = selectJointOneToolPosX, selectJointThreeToolPosY = selectJointTwoToolPosY + jogMachineToolsSpacing;
const ImVec2 selectJointThreeToolPos = {selectJointThreeToolPosX, selectJointThreeToolPosY};

//Select joint 4
//--------------

char* selectJointFourToolName = "Select Joint 4";
unsigned char selectJointFourToolMessage[jogMachineToolsMessageSize] = {'J', '0', '0', '4', '\n'};
const float selectJointFourToolPosX = selectJointOneToolPosX, selectJointFourToolPosY = selectJointThreeToolPosY + jogMachineToolsSpacing;
const ImVec2 selectJointFourToolPos = {selectJointFourToolPosX, selectJointFourToolPosY};

//Select joints flags
//-------------------

int selectedJoint = 2;

//Gripper move
//------------

char* gripperMoveToolName = "Move Gripper";
unsigned char gripperMoveToolMessage[jogMachineToolsMessageSize] = {'J', '0', '3', '2', '\n'};
const float gripperMoveToolPosX = leftToolPosX + 5.0, gripperMoveToolPosY = downToolPosY + jogMachineToolsSpacing;
const ImVec2 gripperMoveToolPos = {gripperMoveToolPosX, gripperMoveToolPosY};

//Gripper direction
//-----------------

char* gripperDirectionToolName = "Gripper Direction";
unsigned char gripperDirectionToolMessage[jogMachineToolsMessageSize] = {'J', '0', '3', '3', '\n'};
const float gripperDirectionToolPosX = leftToolPosX - 10.0, gripperDirectionToolPosY = gripperMoveToolPosY + jogMachineToolsSpacing;
const ImVec2 gripperDirectionToolPos = {gripperDirectionToolPosX, gripperDirectionToolPosY};

//Gripper info
//------------

char* gripperGripInfo = "Direction: Grip.\nClick for release.";
char* gripperReleaseInfo = "Direction: Release.\nClick for grip.";
const float gripperDirectionInfoPosX = gripperDirectionToolPosX, gripperDirectionInfoPosY = gripperDirectionToolPosY + 30.0;
const ImVec2 gripperDirectionInfoPos = {gripperDirectionInfoPosX, gripperDirectionInfoPosY};

//Gripper flags
//-------------

const int grip = 1, release = -1;
int gripperDirection = grip;		

bool gripperMoveToolHeld = false;

//Extruder on hot
//---------------

char* extruderOnHotToolName = "Select Extruder\n (Heated)";
unsigned char extruderOnHotToolMessage[jogMachineToolsMessageSize] = {'J', '0', '4', '2', '\n'};
const float extruderOnHotToolPosX = selectJointOneToolPosX, extruderOnHotToolPosY = selectJointFourToolPosY + jogMachineToolsSpacing;
const ImVec2 extruderOnHotToolPos = {extruderOnHotToolPosX, extruderOnHotToolPosY};

//Extruder on hot info
//--------------------

char* hotExtruderWaitingInfo = "Heating..click to cancel.";
char* hotExtruderConfirmedInfo = "Hot..click to turn off.";
const char extruderReadyMessage = '}';
unsigned char printingOffMessage[jogMachineToolsMessageSize] = {'J', '0', '5', '4', '\n'};
const float extruderHeatStatusInfoPosX = extruderOnHotToolPosX - 25, extruderHeatStatusInfoPosY = extruderOnHotToolPosY + 30;
const ImVec2 extruderHeatStatusInfoPos = {extruderHeatStatusInfoPosX, extruderHeatStatusInfoPosY};

//Extruder on cold
//----------------

char* extruderOnColdToolName = "Select Extruder\n (No Heat)";
unsigned char extruderOnColdToolMessage[jogMachineToolsMessageSize] = {'J', '0', '4', '3', '\n'};
const float extruderOnColdToolPosX = selectJointOneToolPosX, extruderOnColdToolPosY = extruderOnHotToolPosY + jogMachineToolsSpacing;
const ImVec2 extruderOnColdToolPos = {extruderOnColdToolPosX, extruderOnColdToolPosY};

//Extruder toggle
//---------------

char* extruderToggleToolName = "Toggle Extruder";
unsigned char extruderToggleToolMessage[jogMachineToolsMessageSize] = {'J', '0', '4', '4', '\n'};
const float extruderToggleToolPosX = leftToolPosX - 6.0, extruderToggleToolPosY = downToolPosY + jogMachineToolsSpacing;
const ImVec2 extruderToggleToolPos = {extruderToggleToolPosX, extruderToggleToolPosY};

//Extruder direction
//------------------

char* extruderDirectionToolName = "Extruder Direction";
unsigned char extruderDirectionToolMessage[jogMachineToolsMessageSize] = {'J', '0', '4', '5', '\n'};
const float extruderDirectionToolPosX = leftToolPosX - 15.0, extruderDirectionToolPosY = extruderToggleToolPosY + jogMachineToolsSpacing;
const ImVec2 extruderDirectionToolPos = {extruderDirectionToolPosX, extruderDirectionToolPosY};

//Extruder direction info
//-----------------------

char* extruderExtrusionInfo = "Direction: Extrude.\nClick for retraction.";
char* extruderRetractionInfo = "Direction: Retract.\nClick for extrusion.";
const float extruderDirectionInfoPosX = extruderDirectionToolPosX, extruderDirectionInfoPosY = extruderDirectionToolPosY + 30.0;
const ImVec2 extruderDirectionInfoPos = {extruderDirectionInfoPosX, extruderDirectionInfoPosY};

//Extruder flags
//--------------

bool hotExtruderConfirmed = false;
bool hotExtruderWaiting = false;
bool coldExtruderSelected = false;
bool extruderExtruding = false;

const int extrude = 1, retract = -1;
int extruderDirection = extrude;

//Create file
//-----------

char* createFileToolName = "Create Record File";
const float createFileToolPosX = selectJointOneToolPosX + 150.0, createFileToolPosY = selectJointOneToolPosY;
const ImVec2 createFileToolPos = {createFileToolPosX, createFileToolPosY};

ofBuffer outFileBuffer;			//Buffer to store output file data.
string outFilePath;

//Create file info
//----------------

string outFileInfo = "No file created.";
const float outFileInfoPosX = createFileToolPosX, outFileInfoPosY = createFileToolPosY + 25.0;
const ImVec2 outFileInfoPos = {outFileInfoPosX, outFileInfoPosY};

//Create file flags
//-----------------

bool outFilePathLoaded = false;
bool newFileCreated = false;

//Select feed rate
//----------------

char* selectFeedRateToolName = "Feed Rate \n(mm/min)";
const float selectFeedRateToolPosX = createFileToolPosX, selectFeedRateToolPosY = createFileToolPosY + jogMachineToolsSpacing;
const ImVec2 selectFeedRateToolPos = {selectFeedRateToolPosX, selectFeedRateToolPosY};
const ImVec2 selectFeedRateToolSize = {50, 50};

const int defaultFeedRate = 1300;		//(mm/min)	//NOTE: Set these based on the min/max feedrates for the robot with no tool selected!
int currentFeedRate = defaultFeedRate;	//(mm/min)
const int minFeedRate = 1000;			//(mm/min)
const int maxFeedRate = 4500;			//(mm/min)

//Record pose
//-----------

char* recordPoseToolName = "Record Pose";
unsigned char recordPoseToolMessage[jogMachineToolsMessageSize] = {'M', '1', '3', '7', '\n'};
const float recordPoseToolPosX = createFileToolPosX, recordPoseToolPosY = selectFeedRateToolPosY + jogMachineToolsSpacing + 12.5;
const ImVec2 recordPoseToolPos = {recordPoseToolPosX, recordPoseToolPosY};

//Record pose info
//----------------

string recordedLinesInfo = "Lines recorded: 0";
const float recordedLinesInfoPosX = createFileToolPosX, recordedLinesInfoPosY = recordPoseToolPosY + 25.0;
const ImVec2 recordedLinesInfoPos = {recordedLinesInfoPosX, recordedLinesInfoPosY};

//Record flags
//------------

int currentLine = 0;
bool waitingForPose = false;

//Playback
//--------

char * playBackToolName = "Playback";
const float playBackToolPosX = createFileToolPosX, playBackToolPosY = recordPoseToolPosY + jogMachineToolsSpacing;
const ImVec2 playBackToolPos = {playBackToolPosX, playBackToolPosY};

//FUNCTION IMPLEMENTATIONS
//=======================================================================================================================================

//Toolbar
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void jogToolbar(){
//---------------------------------------------------------------------------------------------------------------------------------------

ImGui::SetCursorPos(jogMachineToolbarPos);

if(MODE_MENU != Jog)
{
	ImGui::PushStyleColor(ImGuiCol_Button, toolbarColour);
	if(ImGui::Button(jogMachineToolbarName))		//Show jog machine toolbar.
	{
		if(currentModeBusy == true)
		{
			displayBusyPopup = true;
		}
		else
		{
			MODE_MENU = Jog;
			resetJogParameters();
		}
	}
	ImGui::PopStyleColor();
	
}
else if(MODE_MENU == Jog)
{
	ImGui::PushStyleColor(ImGuiCol_Button, toolbarActiveColour);
	ImGui::Button(jogMachineToolbarName);			//Show highlighted jog machine toolbar.
	ImGui::PopStyleColor();

	ImGui::BeginChild(jogMachineToolbarName);		//Show jog machine tools in a sub-window.

		//Tools
		//-----

		//Calibrate

		calibrateTool();

		//Select jog speed

		selectJogSpeedTool();

		//Up

		selectDirectionTool(upToolHeld, upToolName, upToolPos, upToolMessage);

		//Left

		selectDirectionTool(leftToolHeld, leftToolName, leftToolPos, leftToolMessage);

		//Right

		selectDirectionTool(rightToolHeld, rightToolName, rightToolPos, rightToolMessage);

		//Down

		selectDirectionTool(downToolHeld, downToolName, downToolPos, downToolMessage);

		//Select joint 1

		selectJointTool(1, selectJointOneToolName, selectJointOneToolPos, selectJointOneToolMessage);
			
		//Select joint 2

		selectJointTool(2, selectJointTwoToolName, selectJointTwoToolPos, selectJointTwoToolMessage);
			
		//Select joint 3

		selectJointTool(3, selectJointThreeToolName, selectJointThreeToolPos, selectJointThreeToolMessage);
			
		//Select joint 4

		selectJointTool(4, selectJointFourToolName, selectJointFourToolPos, selectJointFourToolMessage);

		//NOTE: A switch case doesn't work for these because similar to array size consts,
		//the extern guidelines also don't work for switch case label consts

		//No tool

		//N/A

		//Gripper

		if(toolSelected == Gripper)
		{
			//Gripper move
			gripperMoveTool();

			//Gripper direction
			gripperDirectionTool();
		}

		//Extruder

		else if(toolSelected == Extruder)
		{
			//Extruder on hot
			extruderOnHotTool();

			//Extruder on cold
			extruderOnColdTool();

			//Toggle extruder
			extruderToggleTool();

			//Extruder direction
			extruderDirectionTool();
		}
		
		//Create file (for record)

		newFileCreated = createFileTool(outFileInfo, outFilePath, outFilePathLoaded, createFileToolName, createFileToolPos);

		const char* tempOutFileInfo = outFileInfo.c_str();

		ImGui::SetCursorPos(outFileInfoPos);
		ImGui::Text(tempOutFileInfo);

		//Select feed rate (for record)

		ImGui::SetCursorPos(selectFeedRateToolPos);
		ImGui::VSliderInt(selectFeedRateToolName, selectFeedRateToolSize, &currentFeedRate, minFeedRate, maxFeedRate);

		if(newFileCreated == true){ currentLine = 0; recordedLinesInfo = "Lines recorded: 0"; outFileBuffer.clear(); }

		//Record

		recordPoseTool();
			
		const char* tempRecordedLinesInfo = recordedLinesInfo.c_str();

		ImGui::SetCursorPos(recordedLinesInfoPos);
		ImGui::Text(tempRecordedLinesInfo);

		//Delete last pose
		//To do this, you will have to read the file into the buffer line by line only up to the 2nd to the last line.
		//then overwrite the data in the file with the buffer data
		//This functionality shall not be included for now.
		//This can be done manually by simply taking note of the line number(s) you want to delete and deleting them in the file.

		//Playback

		ImGui::SetCursorPos(playBackToolPos);
		if(ImGui::Button(playBackToolName))
		{
			if(outFilePathLoaded == true)
			{
				loadFile(inFileInfo, inFilePath, inFilePathLoaded, inFileBuffer, outFilePath);	//Pass the file to the gcode sender toolbar.

				MODE_MENU = Gcode_Sender;	//Open the gcode sender toolbar.
			}
		}

		//Reset jog parameters

		if(serial.isInitialized() == false)
		{ resetJogParameters();	}

	ImGui::EndChild(); //End of ImGui::BeginChild(jogMachineToolbarName);

} //End of else if(MODE_MENU == Jog_Mode)

}// End of void jogToolbar()

//Tools
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Robot jog tools
//---------------

void jogKeyboardInput(bool keyPressed, int key){
//---------------------------------------------------------------------------------------------------------------------------------------

switch(key)
{
	case oneKey:{ selectJointKeyboardInput(keyPressed, 1, selectJointOneToolMessage); } break;
	case twoKey:{ selectJointKeyboardInput(keyPressed, 2, selectJointTwoToolMessage); } break;
	case threeKey:{ selectJointKeyboardInput(keyPressed, 3, selectJointThreeToolMessage); } break;
	case fourKey:{ selectJointKeyboardInput(keyPressed, 4, selectJointFourToolMessage); } break;
	case upKey:{ selectDirectionKeyboardInput(keyPressed, upKeyHeld, upToolMessage); } break;
	case leftKey:{ selectDirectionKeyboardInput(keyPressed, leftKeyHeld, leftToolMessage); } break;
	case rightKey:{ selectDirectionKeyboardInput(keyPressed, rightKeyHeld, rightToolMessage); } break;
	case downKey:{ selectDirectionKeyboardInput(keyPressed, downKeyHeld, downToolMessage); } break;
}

} //End of void keyboardInput(bool keyPressed, int key)

void selectJointKeyboardInput(bool keyPressed, int jointToSelect, unsigned char toolMessage[]){
//---------------------------------------------------------------------------------------------------------------------------------------

if(keyPressed == true)
{
	if((selectedJoint != jointToSelect) && (jointToSelect != 1))
	{
		serial.writeBytes(&toolMessage[0], jogMachineToolsMessageSize);
		selectedJoint = jointToSelect;
		
		//cout << "Selected joint" << endl;
		//cout << selectedJoint << endl;
	}
}

} //End of void selectJointKeyboardInput(int jointToSelect, unsigned char toolMessage[])

void selectDirectionKeyboardInput(bool keyPressed, bool &directionKeyHeld, unsigned char toolMessage[]){
//---------------------------------------------------------------------------------------------------------------------------------------

if(keyPressed == true)
{
	if(directionKeyHeld == false)
	{
		serial.writeBytes(&toolMessage[0], jogMachineToolsMessageSize);
		directionKeyHeld = true;
	}
}
else if(directionKeyHeld == true)	//keyPressed = false i.e. key has been released
{
	serial.writeByte(idleMessage);
	directionKeyHeld = false;
}
//cout << directionKeyHeld << endl;

} //End of void selectDirectionKeyboardInput(bool keyPressed, bool &directionKeyHeld, unsigned char toolMessage[])


void calibrateTool(){
//---------------------------------------------------------------------------------------------------------------------------------------
//Calibrate tool pseudo-code:
//Check if tool is NOT selected (via a flag),
//  if not selected, check if it is clicked,
//    if clicked, send message and set flag to say it is clicked.
//Else if it is selected, 
//  highlight tool and check if it is clicked,
//    if clicked, send message and set flag to say it is cancelled/complete.
//  else if it not clicked,
//	  check if there is a serial message indicating it is complete,
//      if there is a ready message, set flag to say it is complete.
//(Display of the tool is performed in the clicked checks.)

//*
ImGui::SetCursorPos(autoCalibrateToolPos);
if(calibrating ==  false)
{
	if(ImGui::Button(autoCalibrateToolName))
	{
		serial.writeBytes(&autoCalibrateToolMessage[0], jogMachineToolsMessageSize);
		calibrating = true;

		currentModeBusy = true;
		//cout << "calibrating = true" << endl;
	}
}
else
{
	ImGui::PushStyleColor(ImGuiCol_Button, toolActiveColour);
	if(ImGui::Button(autoCalibrateToolName))
	{
		serial.writeByte(endCalibrationMessage);
		calibrating = false;

		currentModeBusy = false;
		//cout << "calibrating = false" << endl;
	}
	else
	{
		if(serial.available() > 0)
		{
			char c = serial.readByte(); //Read a character/byte of data.
			//cout << "reading byte" << endl;
			//cout << c << endl;
			if(c == calibrationCompleteMessage)
			{
				calibrating = false;

				currentModeBusy = false;
				//cout <<" calibrating = false;" << endl;
			}
		}
	}
ImGui::PopStyleColor();
}

//*/

} //End of void calibrateTool()


void selectJogSpeedTool(){
//---------------------------------------------------------------------------------------------------------------------------------------
ImGui::SetCursorPos(selectJogSpeedToolPos);
ImGui::VSliderInt(selectJogSpeedToolName, selectJogSpeedToolSize, &currentJogSpeed, minJogSpeed, maxJogSpeed);

if(ImGui::IsItemActive()){ selectJogSpeedToolHeld = true; sendJogSpeed = true; }
else
{ 
	selectJogSpeedToolHeld = false;
	
	if(sendJogSpeed == true) 
	{
		serial.writeBytes(&selectJogSpeedToolMessage[0], jogMachineToolsMessageSize);

		stringstream currentJogSpeedToString; currentJogSpeedToString << currentJogSpeed;	//Convert int to string.
		string valueToSend = "T" + currentJogSpeedToString.str();
		int valueMessageSize = strlen(valueToSend.c_str());

		int index = 0;
		while (true)
		{
			if (index >= valueMessageSize)
			{
				serial.writeByte('\n');
				//cout << "end of value message reached" << endl;
				break;
			}

			serial.writeByte(valueToSend[index]);

			index++;
		}

		sendJogSpeed = false; 
	}
}

} //End of void selectJogSpeedTool()

void selectJointTool(int jointToSelect, char* toolName, ImVec2 toolPos, unsigned char toolMessage[]){
//---------------------------------------------------------------------------------------------------------------------------------------
//Select joint tools pseudo-code:
//Check if tool is NOT selected (via a flag),
//  if not selected, check if it is clicked,
//    if clicked, return flag to indicate message should be sent and flag set to say it is selected.
//Else if it is selected,
//  highlight it.
//(Display of the tool is performed in the clicked checks.)

//*
ImGui::SetCursorPos(toolPos);
if((selectedJoint != jointToSelect) && (jointToSelect != 1))
{
	if(ImGui::Button(toolName))
	{
		serial.writeBytes(&toolMessage[0], jogMachineToolsMessageSize);
		selectedJoint = jointToSelect;
	}
}
else
{
	ImGui::PushStyleColor(ImGuiCol_Button, toolActiveColour);
	ImGui::Button(toolName);
	ImGui::PopStyleColor();
}
//*/

} //End of void selectJointTool(int jointToSelect, char* toolName, ImVec2 toolPos, unsigned char toolMessage[])

void selectDirectionTool(bool &directionToolHeld, char* toolName, ImVec2 toolPos, unsigned char toolMessage[]){
//---------------------------------------------------------------------------------------------------------------------------------------
//Direction (left, right, up and down) tools pseudo-code:
//Display tool.
//Check if tool is pressed, 
//  if pressed, check if this is the first time (via a flag),
//    if first time, send message and set flag to say it is pressed.
//Else if not pressed, check if it was pressed before, 
//  if pressed before, send message and set flag to say it not pressed.
//(No message is sent while it is pressed/held down.)

ImGui::SetCursorPos(toolPos);
ImGui::Button(toolName);
if(ImGui::IsItemActive())
{
	if(directionToolHeld == false)
	{
		serial.writeBytes(&toolMessage[0], jogMachineToolsMessageSize);
		directionToolHeld = true;
	}
}
else if(directionToolHeld == true)
{
	serial.writeByte(idleMessage);
	directionToolHeld = false;
}
//cout << directionToolHeld << endl;

} //End of void selectDirectionTool(bool &directionToolHeld, char* toolName, ImVec2 toolPos, unsigned char toolMessage[])

void recordPoseTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//*

ImGui::SetCursorPos(recordPoseToolPos);
if(ImGui::Button(recordPoseToolName))
{
	if((outFilePathLoaded == true) && (waitingForPose ==  false))
	{
		serial.flush(true, true);	//Clear the incoming and outgoing serial buffers.
		//OR
		//while(serial.available() > 0) { char discard = serial.readByte(); } //Clear the incoming serial buffer.
		serial.writeBytes(&recordPoseToolMessage[0], jogMachineToolsMessageSize);

		stringstream currentFeedRateToString; currentFeedRateToString << currentFeedRate;	//Convert int to string.
		string outputFeedRate = "G0 F" + currentFeedRateToString.str() + "\n";
		outFileBuffer.append(outputFeedRate);

		waitingForPose = true;
	}
}
else if(waitingForPose == true)
{
	while(serial.available() > 0)
	{
		char c = serial.readByte(); //Read a character/byte of data.
		//cout << "reading byte" << endl;
		//cout << c << endl;
		
		if(c == deviceReadyMessage)
		{
			ofBufferToFile(outFilePath, outFileBuffer); //Write the buffer data to file.
			waitingForPose = false;
			currentLine++;
			stringstream currentLineToString; currentLineToString << currentLine;	//Convert int to string.
			recordedLinesInfo = "Lines recorded: " + currentLineToString.str();
			//cout <<" pose recorded" << endl;
		}
		else
		{		
			string outputPose = string(1, c);
			outFileBuffer.append(outputPose);
		}
	}
}
//*/

} //End of void recordPoseTool()

//Robot-tools jog tools
//---------------------

//Gripper

void gripperMoveTool(){
//---------------------------------------------------------------------------------------------------------------------------------------
//Gripper move tools pseudo-code:
//Display tool.
//Check if tool is pressed, 
//  if pressed, check if this is the first time (via a flag),
//    if first time, send message and set flag to say it is pressed.
//Else if not pressed, check if it was pressed before, 
//  if pressed before, send message and set flag to say it not pressed.
//(No message is sent while it is pressed/held down.)
			
ImGui::SetCursorPos(gripperMoveToolPos);
ImGui::Button(gripperMoveToolName);
if(ImGui::IsItemActive())
{
	if(gripperMoveToolHeld == false)
	{
		serial.writeBytes(&gripperMoveToolMessage[0], jogMachineToolsMessageSize);
		gripperMoveToolHeld = true;
	}
}
else if(gripperMoveToolHeld == true)
{
	serial.writeByte(idleMessage);
	gripperMoveToolHeld = false;
}
//cout << gripperMoveHeld << endl;

} //End of void gripperMoveTool()

void gripperDirectionTool(){
//---------------------------------------------------------------------------------------------------------------------------------------
//Gripper direction tool pseudo-code:
//Check if direction is grip (via a flag),
//  if grip, check if it is clicked,
//    if clicked, send message and set flag to say direction is release.
//  if grip display grip message.
//Check if direction is release (via flag), 
//  if release, check if it is clicked,
//    if clicked, send message and set flag to say direction is grip.
//  if release, display release message.
//(Display of the tool is performed in the clicked checks.)

//*
ImGui::SetCursorPos(gripperDirectionToolPos);
if(gripperDirection == grip)
{
	if(ImGui::Button(gripperDirectionToolName))
	{
		serial.writeBytes(&gripperDirectionToolMessage[0], jogMachineToolsMessageSize);
		gripperDirection = release;
		//cout << "gripper direction = release" << endl;
	}
	ImGui::SetCursorPos(gripperDirectionInfoPos);
	ImGui::Text(gripperGripInfo);
}
ImGui::SetCursorPos(gripperDirectionToolPos);			
if(gripperDirection == release)
{
	if(ImGui::Button(gripperDirectionToolName))
	{
		serial.writeBytes(&gripperDirectionToolMessage[0], jogMachineToolsMessageSize);
		gripperDirection = grip;
		//cout << "gripper direction = extrude" << endl;
	}
	ImGui::SetCursorPos(gripperDirectionInfoPos);
	ImGui::Text(gripperReleaseInfo);
}

//*/

} //End of void gripperDirectionTool()


//Extruder

void extruderOnHotTool(){
//---------------------------------------------------------------------------------------------------------------------------------------
//Extruder on hot tool pseudo-code:
//Check if heat status is NOT waiting and NOT confirmed (via flags),
//  if not waiting/confirmed check if it is clicked,
//    if clicked flush in/out messages, send message and set flag to say it is selected and heat status should be waiting.
//	  deselect cold extruder and extruding flags.
//Check if heat status is waiting,
//  if waiting, highlight tool and check if it is clicked,
//    if clicked, send message and set flag to say it is no longer selected.
//    deselect extruding flag.
//  else if it not clicked,
//	  check if there is a serial message indicating it is ready,
//      if there is a ready message, set flag to say it is confirmed.
//      deselect waiting flag.
//  if waiting, display waiting message.
//Check if heat status is confirmed,
//  if confirmed, highlight tool and check if it is clicked,
//    if clicked, send message and set flag to say it is no longer selected.
//      deselect extruding flag.
//  if confirmed, display confirmed message.
//(Display of the tool is performed in the clicked checks.)

//*
ImGui::SetCursorPos(extruderOnHotToolPos);
if(hotExtruderWaiting == false && hotExtruderConfirmed == false)
{
	if(ImGui::Button(extruderOnHotToolName))
	{
		serial.flush(true, true);	//Clear the incoming and outgoing serial buffers.
		serial.writeBytes(&extruderOnHotToolMessage[0], jogMachineToolsMessageSize);
		hotExtruderWaiting = true;
		coldExtruderSelected = false;
		extruderExtruding = false;

		currentModeBusy = true;
		//cout <<" extruder waiting = true" << endl;
	}
}
if(hotExtruderWaiting == true)
{
	ImGui::PushStyleColor(ImGuiCol_Button, toolActiveColour);
	if(ImGui::Button(extruderOnHotToolName))
	{
		serial.writeBytes(&printingOffMessage[0], jogMachineToolsMessageSize);
		hotExtruderWaiting = false;
		extruderExtruding = false;

		currentModeBusy = false;
		//cout <<" extruder waiting = false" << endl;
	}
	else
	{
		if(serial.available() > 0)
		{
			char c = serial.readByte(); //Read a character/byte of data.
			//cout << "reading byte" << endl;
			//cout << c << endl;
			if(c == extruderReadyMessage)
			{
				hotExtruderWaiting = false; 
				hotExtruderConfirmed = true; 
				//cout <<" extruder waiting = false" << endl;
			}
		}
	}
	ImGui::PopStyleColor();
		
	ImGui::SetCursorPos(extruderHeatStatusInfoPos);
	ImGui::Text(hotExtruderWaitingInfo);
}
ImGui::SetCursorPos(extruderOnHotToolPos);
if(hotExtruderConfirmed == true)
{
	ImGui::PushStyleColor(ImGuiCol_Button, toolActiveColour);
	if(ImGui::Button(extruderOnHotToolName))
	{
		serial.writeBytes(&printingOffMessage[0], jogMachineToolsMessageSize);
		hotExtruderConfirmed = false;
		extruderExtruding = false;

		currentModeBusy = false;
		//cout <<" extruder confirmed = false" << endl;

	}
	ImGui::PopStyleColor();

	ImGui::SetCursorPos(extruderHeatStatusInfoPos);
	ImGui::Text(hotExtruderConfirmedInfo);
}

//*/

} //End of void extruderOnHotTool()

void extruderOnColdTool(){
//---------------------------------------------------------------------------------------------------------------------------------------
//Extruder on cold tool pseudo-code:
//Check if tool is NOT selected (via a flag),
//  if not selected, check if it is clicked,
//    if clicked, send message and set flag to say it is selected.
//    deselect waiting, confirmed and extruding flags.
//Else if it is selected, 
//  highlight tool and check if it is clicked,
//    if clicked, send message and set flag to say it is no longer selected.
//    deselect extruding flag.
//(Display of the tool is performed in the clicked checks.)
//*

ImGui::SetCursorPos(extruderOnColdToolPos);
if(coldExtruderSelected == false)
{
	if(ImGui::Button(extruderOnColdToolName))
	{
		serial.writeBytes(&extruderOnColdToolMessage[0], jogMachineToolsMessageSize);
		coldExtruderSelected = true;
		hotExtruderWaiting = false;
		hotExtruderConfirmed = false;
		extruderExtruding = false;
		//cout << "cold extruder = true" << endl;
	}
}
else
{
	ImGui::PushStyleColor(ImGuiCol_Button, toolActiveColour);
	if(ImGui::Button(extruderOnColdToolName))
	{
		serial.writeBytes(&printingOffMessage[0], jogMachineToolsMessageSize);
		coldExtruderSelected = false;
		extruderExtruding = false;
		//cout << "cold extruder = false" << endl;
	}
	ImGui::PopStyleColor();
}
//*/

} //End of void extruderOnColdTool()

void extruderToggleTool(){
//---------------------------------------------------------------------------------------------------------------------------------------
//Toggle extruder tool pseudo-code:
//Check if tool is NOT selected (via a flag),
//  if not selected, check if it is clicked,
//    if clicked, check if hot extruder confirmed or cold extruder flags are set,
//      if set, send message and set flag to say it is selceted.
//Else if it is selected, 
//  highlight tool and check if it is clicked,
//    if clicked, send message and set flag to say it is no longer selected.
//(Display of the tool is performed in the clicked checks.)

//*
ImGui::SetCursorPos(extruderToggleToolPos);
if(extruderExtruding ==  false)
{
	if(ImGui::Button(extruderToggleToolName))
	{
		if(hotExtruderConfirmed == true || coldExtruderSelected == true)
		{
			serial.writeBytes(&extruderToggleToolMessage[0], jogMachineToolsMessageSize);
			extruderExtruding = true;
			//cout << "extruder extruding = true" << endl;
		}
	}
}
else
{
	ImGui::PushStyleColor(ImGuiCol_Button, toolActiveColour);
	if(ImGui::Button(extruderToggleToolName))
	{
		serial.writeBytes(&extruderToggleToolMessage[0], jogMachineToolsMessageSize);
		extruderExtruding = false;
		//cout << "extruder extruding = false" << endl;
	}
	ImGui::PopStyleColor();
}
//*/

} //End of void extruderToggleTool()

void extruderDirectionTool(){
//---------------------------------------------------------------------------------------------------------------------------------------
//Extruder direction tool pseudo-code:
//Check if direction is extrude (via a flag),
//  if extrude, check if it is clicked,
//    if clicked, send message and set flag to say direction is retract.
//  if extrude display extrude message.
//Check if direction is retract (via flag), 
//  if retract, check if it is clicked,
//    if clicked, send message and set flag to say direction is extrude.
//  if retract, display retract message.
//(Display of the tool is performed in the clicked checks.)

//*
ImGui::SetCursorPos(extruderDirectionToolPos);
if(extruderDirection == extrude)
{
	if(ImGui::Button(extruderDirectionToolName))
	{
		serial.writeBytes(&extruderDirectionToolMessage[0], jogMachineToolsMessageSize);
		extruderDirection = retract;
		//cout << "extruder direction = retract" << endl;
	}
	ImGui::SetCursorPos(extruderDirectionInfoPos);
	ImGui::Text(extruderExtrusionInfo);
}
ImGui::SetCursorPos(extruderDirectionToolPos);			
if(extruderDirection == retract)
{
	if(ImGui::Button(extruderDirectionToolName))
	{
		serial.writeBytes(&extruderDirectionToolMessage[0], jogMachineToolsMessageSize);
		extruderDirection = extrude;
		//cout << "extruder direction = extrude" << endl;
	}
	ImGui::SetCursorPos(extruderDirectionInfoPos);
	ImGui::Text(extruderRetractionInfo);
}

//*/

} //End of void extruderDirectionTool()

//Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void resetJogParameters(){
//---------------------------------------------------------------------------------------------------------------------------------------

if(serial.isInitialized() == true)
{
	serial.writeBytes(&resetJogParametersMessage[0], jogMachineToolsMessageSize);
}

calibrating = false;

currentJogSpeed = defaultJogSpeed;

selectedJoint = 2;

gripperDirection = grip;		

hotExtruderConfirmed = false;
hotExtruderWaiting = false;
coldExtruderSelected = false;
extruderExtruding = false;

extruderDirection = extrude;

waitingForPose = false;

currentFeedRate = defaultFeedRate;

if(serial.isInitialized() == false)
{
	toolSelected = Pen;
}

} //End of void resetJogParameters()