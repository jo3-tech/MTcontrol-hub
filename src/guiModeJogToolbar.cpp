// Copyright (C) 2017 - 2020 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//HEADER FILE
//=======================================================================================================================================

#include "guiModeJogToolbar.h"

//GLOBAL VARIABLES & CONSTANTS
//=======================================================================================================================================

//Control Flags/Indicator Variables
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Keyboard Input
//++++++++++++++

bool guiUpKeyHeld = false;
bool guiLeftKeyHeld = false;
bool guiRightKeyHeld = false;
bool guiDownKeyHeld = false;

//Auto Calibrate
//++++++++++++++

bool guiCalibrating = false;
bool guiCalibrated = false;

//Home Position
//+++++++++++++

bool guiHoming = false;

//Select Jog Speed
//++++++++++++++++

bool guiSelectJogSpeedToolHeld = false; 
bool guiSendJogSpeed = false;

//Up, Left, Right, Down
//+++++++++++++++++++++

bool guiUpToolHeld = false;
bool guiLeftToolHeld = false;
bool guiRightToolHeld = false;
bool guiDownToolHeld = false;

//Gripper
//+++++++

bool guiGripperMoveToolHeld = false;

//Extruder
//++++++++

const char guiExtruderReadyMessage = '}';

bool guiHotExtruderConfirmed = false;
bool guiHotExtruderWaiting = false;
bool guiColdExtruderSelected = false;
bool guiExtruderExtruding = false;

//Create File
//+++++++++++

bool guiOutFilePathLoaded = false;

//Record
//++++++

int guiCurrentLine = 0;
bool guiWaitingForPose = false;

//Toolbar
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Jog
//+++

const float guiJogToolSpacingX = 2.0; //*guiScaleFactor.
const float guiJogToolSpacingY = 2.0; // "

const int guiJogToolsMessageSize = guiGeneralToolMessageSize;

//Tools and Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Keyboard Input
//++++++++++++++

const int guiUpKey = OF_KEY_UP, guiLeftKey = OF_KEY_LEFT, guiRightKey = OF_KEY_RIGHT, guiDownKey = OF_KEY_DOWN;
//OR
//const int guiUpKey = 357, guiLeftKey = 356, guiRightKey = 358, guiDownKey = 359;

//'1' = 49, '2' = 50, '3' = 51, '4' = 52, '5' = 53, '6' = 54  As per the ASCII table
const int guiOneKey = '1', guiTwoKey = '2', guiThreeKey = '3', guiFourKey = '4';

//Reset Jog Parameters
//++++++++++++++++++++

unsigned char guiResetJogParametersMessage[guiJogToolsMessageSize] = {'J', '2', '5', '5', '\n'};

//Auto Calibrate
//++++++++++++++

char* guiAutoCalibrateToolName = "Auto Calibration";
unsigned char guiAutoCalibrateToolMessage[guiJogToolsMessageSize] = {'J', '2', '5', '1', '\n'};

//Auto Calibrate Info
//+++++++++++++++++++

char* guiCalibrationRequiredInfo = "Calibration required.        ";
char* guiCalibratingInfo = "Calibrating..click to cancel.";
char* guiCalibratedInfo = "Calibration performed.       ";

//Home Position
//+++++++++++++

char* guiHomePositionToolName = "Home Position";
unsigned char guiHomePositionToolMessage[guiJogToolsMessageSize] = {'R', '0', '0', '5', '\n'};

//Home Position Info
//++++++++++++++++++

char* guiHomingInfo = "Going home..click to cancel.";

//Select Jog Speed
//++++++++++++++++

char* guiSelectJogSpeedToolName = "Joint \nJog \nSpeed \n(%)";
unsigned char guiSelectJogSpeedToolMessage[guiJogToolsMessageSize] = {'J', '2', '5', '2', ' '}; //NOTE: '\n' is left out on purpose since the jog speed will be sent after this message.

const int guiDefaultJogSpeed = 98;		     //(%).
int guiCurrentJogSpeed = guiDefaultJogSpeed; // "
const int guiMinJogSpeed = 0;			     // "
const int guiMaxJogSpeed = 100;		         // "

//Up
//++

char* guiUpToolName = "Up";
unsigned char guiUpToolMessage[guiJogToolsMessageSize] = {'J', '0', '1', '3', '\n'};

//Left
//++++

char* guiLeftToolName = "Left";
unsigned char guiLeftToolMessage[guiJogToolsMessageSize] = {'J', '0', '1', '1', '\n'};

//Right
//+++++

char* guiRightToolName = "Right";
unsigned char guiRightToolMessage[guiJogToolsMessageSize] = {'J', '0', '1', '2', '\n'};

//Down
//++++

char* guiDownToolName = "Down";
unsigned char guiDownToolMessage[guiJogToolsMessageSize] = {'J', '0', '1', '4', '\n'};

//Select Joint General
//++++++++++++++++++++

int guiSelectedJoint = 2;

//Select Joint 1
//++++++++++++++

char* guiSelectJointOneToolName = "Select Joint 1";
unsigned char guiSelectJointOneToolMessage[guiJogToolsMessageSize] = {'J', '0', '0', '1', '\n'};

//Select Joint 2
//++++++++++++++

char* guiSelectJointTwoToolName = "Select Joint 2";
unsigned char guiSelectJointTwoToolMessage[guiJogToolsMessageSize] = {'J', '0', '0', '2', '\n'};

//Select Joint 3
//++++++++++++++

char* guiSelectJointThreeToolName = "Select Joint 3";
unsigned char guiSelectJointThreeToolMessage[guiJogToolsMessageSize] = {'J', '0', '0', '3', '\n'};

//Select Joint 4
//++++++++++++++

char* guiSelectJointFourToolName = "Select Joint 4";
unsigned char guiSelectJointFourToolMessage[guiJogToolsMessageSize] = {'J', '0', '0', '4', '\n'};

//Create File
//+++++++++++

char* guiCreateFileToolName = "Create Record File";

ofBuffer guiOutFileBuffer; //Buffer to store output file data.
string guiOutFilePath;

//Create File Info
//++++++++++++++++

string guiOutFileInfo = "No file created.";

//Select Feed Rate
//++++++++++++++++

char* guiSelectFeedRateToolName = "Feed Rate \n(mm/min)";

const int guiDefaultFeedRate = 4273;	     //(mm/min). //NOTE: Set these based on the min/max feedrates for the robot with no tool selected!
int guiCurrentFeedRate = guiDefaultFeedRate; // "
const int guiMinFeedRate = 116;		         // "
const int guiMaxFeedRate = 15726;		     // "

//Record Pose
//+++++++++++

char* guiRecordPoseToolName = "Record Pose";
unsigned char guiRecordPoseToolMessage[guiJogToolsMessageSize] = {'J', '2', '5', '3', '\n'};

//Record Pose Info
//++++++++++++++++

string guiRecordedLinesInfo = "Lines recorded: 0";

//Playback
//++++++++

char * guiPlayBackToolName = "Playback";

//Gripper General
//+++++++++++++++

const int guiGrip = 1, guiRelease = -1;
int guiGripperDirection = guiGrip;

//Gripper Move
//++++++++++++

char* guiGripperMoveToolName = "Move Gripper";
unsigned char guiGripperMoveToolMessage[guiJogToolsMessageSize] = {'J', '0', '3', '2', '\n'};

//Gripper Direction
//+++++++++++++++++

char* guiGripperDirectionToolName = "Gripper Direction";
unsigned char guiGripperDirectionToolMessage[guiJogToolsMessageSize] = {'J', '0', '3', '3', '\n'};

//Gripper Info
//++++++++++++

char* guiGripperGripInfo = "Direction: Grip.\nClick for release.";
char* guiGripperReleaseInfo = "Direction: Release.\nClick for grip.";

//Extruder General
//++++++++++++++++

const int guiExtrude = 1, retract = -1;
int guiExtruderDirection = guiExtrude;

//Extruder On Hot
//+++++++++++++++

char* guiExtruderOnHotToolName = "Select Extruder\n (Heated)";
unsigned char guiExtruderOnHotToolMessage[guiJogToolsMessageSize] = {'J', '0', '4', '2', '\n'};

//Extruder On Hot Info
//++++++++++++++++++++

char* guiHotExtruderIdleInfo = "Cooling..click to heat.";
char* guiHotExtruderWaitingInfo = "Heating..click to cool.";
char* guiHotExtruderConfirmedInfo = "Hot..click to cool.    ";

unsigned char guiPrintingOffMessage[guiJogToolsMessageSize] = {'J', '0', '4', '6', '\n'};

//Extruder On Cold
//++++++++++++++++

char* guiExtruderOnColdToolName = "Select Extruder\n (No Heat)";
unsigned char guiExtruderOnColdToolMessage[guiJogToolsMessageSize] = {'J', '0', '4', '3', '\n'};

//Extruder Toggle
//+++++++++++++++

char* guiExtruderToggleToolName = "Toggle Extruder";
unsigned char guiExtruderToggleToolMessage[guiJogToolsMessageSize] = {'J', '0', '4', '4', '\n'};

//Extruder Direction
//++++++++++++++++++

char* guiExtruderDirectionToolName = "Extruder Direction";
unsigned char guiExtruderDirectionToolMessage[guiJogToolsMessageSize] = {'J', '0', '4', '5', '\n'};

//Extruder Direction Info
//+++++++++++++++++++++++

char* guiExtruderExtrusionInfo = "Direction: Extrude.\nClick for retraction.";
char* guiExtruderRetractionInfo = "Direction: Retract.\nClick for extrusion.";

//FUNCTION IMPLEMENTATIONS
//=======================================================================================================================================

//Toolbar
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiJogToolbar(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display jog toolbar.

if(guiModeMenuToolbarId == guiJogToolbarId)
{
	//DEFERRED. guiInfoMenu.
	//if((guiReEntryIntoJog == true) && (guiListenForRobotParameters == false) && (guiCurrentModeBusy == false) && (guiSerial.isInitialized()))
	//{ guiSerial.flush(true, true); guiSerial.writeBytes(&guiRequestRobotParametersMessage[0], guiGeneralToolMessageSize); guiListenForRobotParameters = true; guiCurrentModeBusy = true; }
	//else if((guiReEntryIntoJog == true) && (guiListenForRobotParameters == false))
	//{ guiResetJogParameters(); guiReEntryIntoJog = false; guiCurrentModeBusy = false; } //In order to stop/clear heaters (in case activated by g-code sender) and to start jog toolbar with fresh parameters. 
	
	if(guiReEntryIntoJog == true)
	{
		guiResetJogParameters(); guiReEntryIntoJog = false;
	}
	
	//Tools and Tool Actions
	//----------------------

	guiGeneralGuiVerticalSpacing(guiJogToolSpacingY/2);
	
	{ //Calibrate
	ImGui::BeginGroup();

		guiCalibrateTool();

	ImGui::EndGroup(); 
	}

	guiGeneralGuiHorizontalSpacing(guiJogToolSpacingX);

	{ //Go home
	ImGui::BeginGroup();

		guiGoHomeTool();

	ImGui::EndGroup(); 
	}

	guiGeneralGuiVerticalSpacing(guiJogToolSpacingY);

	{ //Select joint group.
	ImGui::BeginGroup(); 
		
		guiSelectJointTool(1, guiSelectJointOneToolName, guiSelectJointOneToolMessage); //Select joint 1.

		guiGeneralGuiVerticalSpacing(guiJogToolSpacingY);
		guiSelectJointTool(2, guiSelectJointTwoToolName, guiSelectJointTwoToolMessage); //Select joint 2.

		guiGeneralGuiVerticalSpacing(guiJogToolSpacingY);
		guiSelectJointTool(3, guiSelectJointThreeToolName, guiSelectJointThreeToolMessage); //Select joint 3.

		guiGeneralGuiVerticalSpacing(guiJogToolSpacingY);
		guiSelectJointTool(4, guiSelectJointFourToolName, guiSelectJointFourToolMessage); //Select joint 4.

	ImGui::EndGroup();
	}

	guiGeneralGuiHorizontalSpacing(guiJogToolSpacingX);

	{ //Select jog speed group
	ImGui::BeginGroup(); 

		guiGeneralGuiVerticalSpacing(guiJogToolSpacingY);
		guiSelectJogSpeedTool();

	ImGui::EndGroup();
	}

	guiGeneralGuiHorizontalSpacing(guiJogToolSpacingX);

	{ //Select direction group
	ImGui::BeginGroup(); 

		guiGeneralGuiVerticalSpacing(guiJogToolSpacingY); 
		guiGeneralGuiHorizontalSpacing(1.5);	
		guiSelectDirectionTool(guiUpToolHeld, guiUpToolName, ImGuiDir_Up, guiUpToolMessage); //Up.

		//TESTING.
		//guiSelectDirectionTool(guiUpToolHeld, guiUpToolName, upToolPos, guiUpToolMessage); //Up.

		guiSelectDirectionTool(guiLeftToolHeld, guiLeftToolName, ImGuiDir_Left, guiLeftToolMessage); //Left.
		//TESTING.
		//guiSelectDirectionTool(guiLeftToolHeld, guiLeftToolName, leftToolPos, guiLeftToolMessage); //Left.

		guiGeneralGuiHorizontalSpacing(1.8);
		guiSelectDirectionTool(guiRightToolHeld, guiRightToolName, ImGuiDir_Right, guiRightToolMessage); //Right.

		//TESTING.
		//guiSelectDirectionTool(guiRightToolHeld, guiRightToolName, rightToolPos, guiRightToolMessage); //Right.

		//TESTING.
		//ImGui::NewLine(); //Force new line. In this case there seems to be 0 spacing but this doesn't seem to be the case when used in other places.

		ImGui::Spacing(); //Force new line with 0 spacing. 
		guiGeneralGuiHorizontalSpacing(1.5);

		guiSelectDirectionTool(guiDownToolHeld, guiDownToolName, ImGuiDir_Down, guiDownToolMessage); //Down.

		//TESTING.
		//guiSelectDirectionTool(guiDownToolHeld, guiDownToolName, downToolPos, guiDownToolMessage); //Down.

	ImGui::EndGroup();
	}

	guiGeneralGuiHorizontalSpacing(guiJogToolSpacingX);

	{ //Record and playback group
	ImGui::BeginGroup(); 

		//Create file (for record)

		guiCreateFileTool();

		//Select feed rate (for record)

		guiGeneralGuiVerticalSpacing(guiJogToolSpacingY*0.5);

		ImGui::SetNextItemWidth(7*guiScaleFactor);
		ImGui::SliderInt(guiSelectFeedRateToolName, &guiCurrentFeedRate, guiMinFeedRate, guiMaxFeedRate);

		//TESTING.
		//ImGui::VSliderInt(guiSelectFeedRateToolName, ImVec2(50, 50), &guiCurrentFeedRate, guiMinFeedRate, guiMaxFeedRate);

		//Record

		guiGeneralGuiVerticalSpacing(guiJogToolSpacingY*0.5);
		guiRecordPoseTool();

		//DEFERRED.
		//Delete last pose
		//To do this, you will have to read the file into the buffer line by line only up to the 2nd to the last line.
		//then overwrite the data in the file with the buffer data
		//This functionality shall not be included for now.
		//This can be done manually by simply taking note of the line number(s) you want to delete and deleting them in the file.

		//Playback

		guiGeneralGuiVerticalSpacing(guiJogToolSpacingY*0.5);
		guiPlaybackTool();

	ImGui::EndGroup();
	}

	guiGeneralGuiVerticalSpacing(guiJogToolSpacingY*0.5);

	//NOTE: A switch case doesn't work for these because similar to array size consts,
	//the extern guidelines also don't work for switch case label consts.

	if(rbtToolSelected == rbtGripper)
	{
		guiGeneralGuiHorizontalSpacing(guiJogToolSpacingX*7.5);

		ImGui::BeginGroup();

 			guiGripperMoveTool();

			guiGeneralGuiVerticalSpacing(guiJogToolSpacingY*0.5);
			guiGripperDirectionTool();

		ImGui::EndGroup();
	}
	else if(rbtToolSelected == rbtExtruder)
	{
		ImGui::BeginGroup();
			
			guiExtruderOnHotTool();

			guiGeneralGuiVerticalSpacing(guiJogToolSpacingY*0.5);
			guiExtruderOnColdTool();

		ImGui::EndGroup();

		guiGeneralGuiHorizontalSpacing(guiJogToolSpacingX);

		ImGui::BeginGroup();

			guiExtruderToggleTool();

			guiGeneralGuiVerticalSpacing(guiJogToolSpacingY*0.5);
			guiExtruderDirectionTool();

		ImGui::EndGroup();
	}

	//Reset jog parameters

	if(guiSerial.isInitialized() == false)
	{ guiResetJogParameters();	}

} //End of if(guiModeMenuToolbarId == guiJogToolbarId)

}// End of void guiJogToolbar()

//Tools
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Robot Jog Tools
//+++++++++++++++

void guiJogKeyboardInput(bool keyPressed, int key){
//---------------------------------------------------------------------------------------------------------------------------------------

//Check for keyboard input within jog toolbar.

if(guiModeMenuToolbarId == guiJogToolbarId)
{	
	switch(key)
	{
		case guiOneKey:{ guiSelectJointKeyboardInput(keyPressed, 1, guiSelectJointOneToolMessage); } break;
		case guiTwoKey:{ guiSelectJointKeyboardInput(keyPressed, 2, guiSelectJointTwoToolMessage); } break;
		case guiThreeKey:{ guiSelectJointKeyboardInput(keyPressed, 3, guiSelectJointThreeToolMessage); } break;
		case guiFourKey:{ guiSelectJointKeyboardInput(keyPressed, 4, guiSelectJointFourToolMessage); } break;
		case guiUpKey:{ guiSelectDirectionKeyboardInput(keyPressed, guiUpKeyHeld, guiUpToolMessage); } break;
		case guiLeftKey:{ guiSelectDirectionKeyboardInput(keyPressed, guiLeftKeyHeld, guiLeftToolMessage); } break;
		case guiRightKey:{ guiSelectDirectionKeyboardInput(keyPressed, guiRightKeyHeld, guiRightToolMessage); } break;
		case guiDownKey:{ guiSelectDirectionKeyboardInput(keyPressed, guiDownKeyHeld, guiDownToolMessage); } break;
	}
}

}

void guiSelectJointKeyboardInput(bool keyPressed, int jointToSelect, unsigned char toolMessage[]){
//---------------------------------------------------------------------------------------------------------------------------------------

//Select joint from keyboard input.

if((keyPressed == true) && (guiCurrentModeBusy == false))
{
	if((guiSelectedJoint != jointToSelect) && (jointToSelect != 1))
	{
		guiSerial.writeBytes(&toolMessage[0], guiJogToolsMessageSize);
		guiSelectedJoint = jointToSelect;
		
		guiSerial.flush(true, false); //Clear the incomings serial buffers.

		//DEBUGGING.
		//cout << "Selected joint" << endl;
		//cout << guiSelectedJoint << endl;
	}
}

}

void guiSelectDirectionKeyboardInput(bool keyPressed, bool &directionKeyHeld, unsigned char toolMessage[]){
//---------------------------------------------------------------------------------------------------------------------------------------

//Move robot in selected direction from keyboard input.

if(keyPressed == true)
{
	if(directionKeyHeld == false)
	{
		guiSerial.writeBytes(&toolMessage[0], guiJogToolsMessageSize);
		directionKeyHeld = true;
	}
}
else if(directionKeyHeld == true) //keyPressed = false i.e. key has been released.
{
	guiSerial.writeByte(guiCancelActionMessage);
	directionKeyHeld = false;

	guiSerial.flush(true, false); //Clear the incomings serial buffer.
}

//DEBUGGING.
//cout << directionKeyHeld << endl;

}

void guiCalibrateTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to calibrate robot.
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

if(guiCalibrating == false)
{
	if(ImGui::Button(guiAutoCalibrateToolName) && (guiCurrentModeBusy == false))
	{
		guiSerial.flush(true, false); //Clear the incomings serial buffer.

		guiSerial.writeBytes(&guiAutoCalibrateToolMessage[0], guiJogToolsMessageSize);
		guiCalibrating = true;

		guiCurrentModeBusy = true;
		
		//DEBUGGING.
		//cout << "guiCalibrating = true" << endl;
	}
}
else
{
	ImGui::PushStyleColor(ImGuiCol_Button, guiToolActiveColour);

	if(ImGui::Button(guiAutoCalibrateToolName))
	{
		guiSerial.writeByte(guiCancelActionMessage);
		guiCalibrating = false;
		guiCalibrated = false;

		guiCurrentModeBusy = false;

		guiSerial.flush(true, false); //Clear the incomings serial buffers.

		//DEBUGGING.
		//cout << "guiCalibrating = false" << endl;
	}
	else if(guiSerial.available() > 0)
	{
		char c = guiSerial.readByte(); //Read a character/byte of data.

		//DEBUGGING.
		//cout << "reading byte" << endl;
		//cout << c << endl;

		if(c == guiDeviceReadyMessage)
		{
			guiCalibrating = false;
			guiCalibrated = true;

			guiCurrentModeBusy = false;

			guiSerial.flush(true, false); //Clear the incomings serial buffers.

			//DEBUGGING.
			//cout <<" guiCalibrating = false;" << endl;
		}
	}

	ImGui::PopStyleColor();

} //End of if(guiCalibrating == false), else...

if(guiCalibrating == true){ ImGui::Text(guiCalibratingInfo); }
else if(guiCalibrated == false){ ImGui::Text(guiCalibrationRequiredInfo); }
else{ ImGui::Text(guiCalibratedInfo); }

} //End of void guiCalibrateTool()

void guiGoHomeTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to home robot.

if(guiHoming == false)
{
	if(ImGui::Button(guiHomePositionToolName) && (guiCurrentModeBusy == false))
	{
		guiSerial.flush(true, false); //Clear the incoming serial buffer.

		guiSerial.writeBytes(&guiHomePositionToolMessage[0], guiJogToolsMessageSize);
		guiHoming = true;

		guiCurrentModeBusy = true;
		
		//DEBUGGING.
		//cout << "guiHoming = true" << endl;
	}
}
else
{
	ImGui::PushStyleColor(ImGuiCol_Button, guiToolActiveColour);

	if(ImGui::Button(guiHomePositionToolName))
	{
		guiSerial.writeByte(guiCancelActionMessage);
		guiHoming = false;

		guiCurrentModeBusy = false;

		guiSerial.flush(true, false); //Clear the incomings serial buffers.

		//DEBUGGING.
		//cout << "cancelled going home" << endl;
	}
	else if(guiSerial.available() > 0)
	{
		char c = guiSerial.readByte(); //Read a character/byte of data.

		//DEBUGGING.
		//cout << "reading byte" << endl;
		//cout << c << endl;

		if(c == guiDeviceReadyMessage)
		{
			guiHoming = false;

			guiCurrentModeBusy = false;

			guiSerial.flush(true, false); //Clear the incomings serial buffers.

			//DEBUGGING.
			//cout <<" guiHoming done" << endl;
		}
	}

	ImGui::PopStyleColor();

} //End of if(guiHoming == false), else...

if(guiHoming == true){ ImGui::Text(guiHomingInfo); }

} //End of void guiGoHomeTool()

void guiSelectJogSpeedTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to select jog speed.

int savedJogSpeed = guiCurrentJogSpeed;

ImVec2 jogSpeedToolSize = {4*guiScaleFactor, 5*guiScaleFactor};
ImGui::VSliderInt(guiSelectJogSpeedToolName, jogSpeedToolSize, &guiCurrentJogSpeed, guiMinJogSpeed, guiMaxJogSpeed);

//TESTING.
//ImGui::SliderInt(guiSelectJogSpeedToolName, &guiCurrentJogSpeed, guiMinJogSpeed, guiMaxJogSpeed);

if(ImGui::IsItemActive()){ guiSelectJogSpeedToolHeld = true; guiSendJogSpeed = true; }
else
{ 
	guiSelectJogSpeedToolHeld = false;

	if(guiCurrentModeBusy == true){ guiSendJogSpeed == false; guiCurrentJogSpeed = savedJogSpeed; }
	else if(guiSendJogSpeed == true) 
	{
		guiSerial.writeBytes(&guiSelectJogSpeedToolMessage[0], guiJogToolsMessageSize);

		stringstream currentJogSpeedToString; currentJogSpeedToString << guiCurrentJogSpeed; //Convert int to string.
		string valueToSend = "T" + currentJogSpeedToString.str();
		int valueMessageSize = strlen(valueToSend.c_str());

		int index = 0;
		while (true)
		{
			if(index >= valueMessageSize)
			{
				guiSerial.writeByte('\n');

				guiSerial.flush(true, false); //Clear the incomings serial buffers.

				//DEBUGGING.
				//cout << "end of value message reached" << endl;

				break;
			}

			guiSerial.writeByte(valueToSend[index]);
			index++;
		}

		guiSendJogSpeed = false; 

	} //End of if(guiCurrentModeBusy == true), else if(guiSendJogSpeed == true) 

} //End of if(ImGui::IsItemActive()), else...

} //End of void guiSelectJogSpeedTool()

void guiSelectJointTool(int jointToSelect, char* toolName, unsigned char toolMessage[]){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to select joint.
//Select joint tools pseudo-code:
//Check if tool is NOT selected (via a flag),
//  if not selected, check if it is clicked,
//    if clicked, return flag to indicate message should be sent and flag set to say it is selected.
//Else if it is selected,
//  highlight it.
//(Display of the tool is performed in the clicked checks.)

if((guiSelectedJoint != jointToSelect) && (jointToSelect != 1))
{
	if(ImGui::Button(toolName) && (guiCurrentModeBusy == false))
	{
		guiSerial.writeBytes(&toolMessage[0], guiJogToolsMessageSize);
		guiSelectedJoint = jointToSelect;

		guiSerial.flush(true, false); //Clear the incomings serial buffers.
	}
}
else
{
	ImGui::PushStyleColor(ImGuiCol_Button, guiToolActiveColour);
	ImGui::Button(toolName);
	ImGui::PopStyleColor();
}

}

//TESTING.
//void guiSelectDirectionTool(bool &directionToolHeld, char* toolName, unsigned char toolMessage[]){

void guiSelectDirectionTool(bool &directionToolHeld, char* toolName, ImGuiDir_ arrowType, unsigned char toolMessage[]){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to move robot in selected direction.
//Direction (left, right, up and down) tools pseudo-code:
//Display tool.
//Check if tool is pressed, 
//  if pressed, check if this is the first time (via a flag),
//    if first time, send message and set flag to say it is pressed.
//Else if not pressed, check if it was pressed before, 
//  if pressed before, send message and set flag to say it not pressed.
//(No message is sent while it is pressed/held down.)

//TESTING.
//ImGui::Button(toolName);

ImGui::ArrowButton(toolName, arrowType);

if(ImGui::IsItemActive() && (guiCurrentModeBusy == false))
{
	if(directionToolHeld == false)
	{
		guiSerial.writeBytes(&toolMessage[0], guiJogToolsMessageSize);
		directionToolHeld = true;
	}
}
else if(directionToolHeld == true)
{
	guiSerial.writeByte(guiCancelActionMessage);
	directionToolHeld = false;

	guiSerial.flush(true, false); //Clear the incomings serial buffers.
}

//DEBUGGING.
//cout << directionToolHeld << endl;

}

void guiCreateFileTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to create file.

if(ImGui::Button(guiCreateFileToolName) && (guiCurrentModeBusy == false))
{
	bool newFileCreated =  guiCreateFileViaDialogue("Record.txt", guiOutFileInfo, guiOutFilePath);

	if(newFileCreated == true){ guiOutFilePathLoaded = true; guiCurrentLine = 0; guiRecordedLinesInfo = "Lines recorded: 0"; guiOutFileBuffer.clear(); }
}

const char* tempOutFileInfo = guiOutFileInfo.c_str();
ImGui::Text(tempOutFileInfo);

//DEFERRED.
//guiOutFileBuffer = ofBufferFromFile(guiOutFilePath); //Create ofBuffer from file. This will allow continued recording from the end of a previously recorded file.
//We may need to add a separate load file button for this and call the guiLoadFile method instead.
//NOT INCLUDING THIS FUNCTIONALITY FOR NOW... THIS CAN BE DONE MANUALLY BY SIMPLY COMBINING THE DATA FROM TWO RECORDED FILES.

}

void guiRecordPoseTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to record robot pose.

if(ImGui::Button(guiRecordPoseToolName) && (guiCurrentModeBusy == false))
{
	if((guiOutFilePathLoaded == true) && (guiWaitingForPose ==  false))
	{
		guiSerial.flush(true, false); //Clear the incomings serial buffers.

		guiSerial.writeBytes(&guiRecordPoseToolMessage[0], guiJogToolsMessageSize);

		stringstream guiCurrentFeedRateToString; guiCurrentFeedRateToString << guiCurrentFeedRate; //Convert int to string.
		string outputFeedRate = "G0 F" + guiCurrentFeedRateToString.str() + "\n";
		guiOutFileBuffer.append(outputFeedRate);

		guiWaitingForPose = true;
		guiCurrentModeBusy = true; //This is mainly to prevent any further message exchange with the robot via other tools.
	}
}
else if(guiWaitingForPose == true)
{
	while(guiSerial.available() > 0)
	{
		char c = guiSerial.readByte(); //Read a character/byte of data.

		//DEBUGGING.
		//cout << "reading byte" << endl;
		//cout << c << endl;
		
		if(c == guiDeviceReadyMessage)
		{
			ofBufferToFile(guiOutFilePath, guiOutFileBuffer); //Write the buffer data to file.
			guiCurrentLine++;
			stringstream guiCurrentLineToString; guiCurrentLineToString << guiCurrentLine; //Convert int to string.
			guiRecordedLinesInfo = "Lines recorded: " + guiCurrentLineToString.str();

			//DEBUGGING.
			//cout <<" pose recorded" << endl;

			guiWaitingForPose = false;
			guiCurrentModeBusy = false;

			guiSerial.flush(true, false); //Clear the incoming serial buffers.

			break;
		}
		else
		{		
			string outputPose = string(1, c); //Convert char to string. 

			//TESTING.
			//OR string outputPose = c; 
			
			guiOutFileBuffer.append(outputPose);
		}

	} //End of while(guiSerial.available() > 0)

} //End of if(ImGui::Button(guiRecordPoseToolName) && (guiCurrentModeBusy == false)), else if(guiWaitingForPose == true)

const char* tempRecordedLinesInfo = guiRecordedLinesInfo.c_str();
ImGui::Text(tempRecordedLinesInfo);

} //End of void guiRecordPoseTool()

void guiPlaybackTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to playback recorded actions.

if(ImGui::Button(guiPlayBackToolName) && (guiCurrentModeBusy == false))
{
	if((guiOutFilePathLoaded == true))
	{
		guiInFilePath = guiOutFilePath; //Transfer the file path created in jog mode to the file path for g-code sender
		guiLoadFile(guiInFileInfo, guiInFilePath, guiInFileBuffer); //Pass the file to the g-code sender toolbar.
		guiInFilePathLoaded = true;
		guiModeMenuToolbarId = guiGcSenderToolbarId; //Open the gcode sender toolbar.
	}
}

}

//Gripper Jog Tools
//+++++++++++++++++

void guiGripperMoveTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to move gripper.
//Gripper move tools pseudo-code:
//Display tool.
//Check if tool is pressed, 
//  if pressed, check if this is the first time (via a flag),
//    if first time, send message and set flag to say it is pressed.
//Else if not pressed, check if it was pressed before, 
//  if pressed before, send message and set flag to say it not pressed.
//(No message is sent while it is pressed/held down.)
			
ImGui::Button(guiGripperMoveToolName);

if(ImGui::IsItemActive()) //If button is pressed.
{
	if(guiGripperMoveToolHeld == false)
	{
		guiSerial.writeBytes(&guiGripperMoveToolMessage[0], guiJogToolsMessageSize);
		guiGripperMoveToolHeld = true;
	}
}
else if(guiGripperMoveToolHeld == true)
{
	guiSerial.writeByte(guiCancelActionMessage);
	guiGripperMoveToolHeld = false;

	guiSerial.flush(true, false); //Clear the incoming serial buffers.
}

//DEBUGGING.
//cout << gripperMoveHeld << endl;

} //End of void guiGripperMoveTool()

void guiGripperDirectionTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to change gripper direction.

if(ImGui::Button(guiGripperDirectionToolName) && (guiCurrentModeBusy == false))
{
	guiSerial.writeBytes(&guiGripperDirectionToolMessage[0], guiJogToolsMessageSize);
		
	if(guiGripperDirection == guiGrip)
	{ 
		guiGripperDirection = guiRelease;
		
		//DEBUGGING.
		//cout << "gripper direction = release" << endl;
	}
	else //guiGripperDirection = guiRelease
	{
		guiGripperDirection = guiGrip;
		
		//DEBUGGING.
		//cout << "gripper direction = grip" << endl;
	}

	guiSerial.flush(true, false); //Clear the incoming serial buffers.
}

if(guiGripperDirection == guiRelease){ ImGui::Text(guiGripperReleaseInfo); }
else{ ImGui::Text(guiGripperGripInfo); }

} //End of void guiGripperDirectionTool()

//Extruder Jog Tools
//++++++++++++++++++

void guiExtruderOnHotTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to switch extruder on (heated).
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

if(guiHotExtruderWaiting == false && guiHotExtruderConfirmed == false)
{
	if(ImGui::Button(guiExtruderOnHotToolName) && (guiCurrentModeBusy == false))
	{
		guiSerial.flush(true, false); //Clear the incoming serial buffer.

		guiSerial.writeBytes(&guiExtruderOnHotToolMessage[0], guiJogToolsMessageSize);
		guiHotExtruderWaiting = true;
		guiColdExtruderSelected = false;
		guiExtruderExtruding = false;

		guiCurrentModeBusy = true;

		//DEBUGGING.
		//cout <<" extruder waiting = true" << endl;
	}

	ImGui::Text(guiHotExtruderIdleInfo);
}

if(guiHotExtruderWaiting == true)
{
	ImGui::PushStyleColor(ImGuiCol_Button, guiToolActiveColour);

	if(ImGui::Button(guiExtruderOnHotToolName))
	{
		guiSerial.writeBytes(&guiPrintingOffMessage[0], guiJogToolsMessageSize);
		guiHotExtruderWaiting = false;
		guiExtruderExtruding = false;

		guiCurrentModeBusy = false;
		
		guiSerial.flush(true, false); //Clear the incoming serial buffers.
		
		//DEBUGGING.
		//cout <<" extruder waiting = false" << endl;
	}
	else if(guiSerial.available() > 0)
	{
		char c = guiSerial.readByte(); //Read a character/byte of data.

		//DEBUGGING.
		//cout << "reading byte" << endl;
		//cout << c << endl;

		if(c == guiExtruderReadyMessage)
		{
			guiHotExtruderWaiting = false; 
			guiHotExtruderConfirmed = true; 

			guiCurrentModeBusy = false;
			guiCurrentModeStillBusy = true;

			guiSerial.flush(true, false); //Clear the incoming serial buffers.

			//DEBUGGING.
			//cout <<" extruder waiting = false" << endl;
		}
	}

	ImGui::PopStyleColor();
		
	ImGui::Text(guiHotExtruderWaitingInfo);

} //End of if(guiHotExtruderWaiting == true)

if(guiHotExtruderConfirmed == true)
{
	ImGui::PushStyleColor(ImGuiCol_Button, guiToolActiveColour);

	if(ImGui::Button(guiExtruderOnHotToolName))
	{
		guiSerial.writeBytes(&guiPrintingOffMessage[0], guiJogToolsMessageSize);
		guiHotExtruderConfirmed = false;
		guiExtruderExtruding = false;

		guiCurrentModeStillBusy = false;

		guiSerial.flush(true, false); //Clear the incoming serial buffers.

		//DEBUGGING.
		//cout <<" extruder confirmed = false" << endl;

	}

	ImGui::PopStyleColor();

	ImGui::Text(guiHotExtruderConfirmedInfo);
}

} //End of void guiExtruderOnHotTool()

void guiExtruderOnColdTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to switch extruder on (cold).
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

if(guiColdExtruderSelected == false)
{
	if(ImGui::Button(guiExtruderOnColdToolName) && (guiCurrentModeBusy == false))
	{
		guiSerial.writeBytes(&guiExtruderOnColdToolMessage[0], guiJogToolsMessageSize);
		guiColdExtruderSelected = true;
		guiHotExtruderWaiting = false;
		guiHotExtruderConfirmed = false;
		guiExtruderExtruding = false;

		guiSerial.flush(true, false); //Clear the incoming serial buffers.

		//DEBUGGING.
		//cout << "cold extruder = true" << endl;
	}
}
else
{
	ImGui::PushStyleColor(ImGuiCol_Button, guiToolActiveColour);

	if(ImGui::Button(guiExtruderOnColdToolName))
	{
		guiSerial.writeBytes(&guiPrintingOffMessage[0], guiJogToolsMessageSize);
		guiColdExtruderSelected = false;
		guiExtruderExtruding = false;

		guiSerial.flush(true, false); //Clear the incoming serial buffers.

		//DEBUGGING.
		//cout << "cold extruder = false" << endl;
	}

	ImGui::PopStyleColor();
}

} //End of void guiExtruderOnColdTool()

void guiExtruderToggleTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to toggle (start if stopped/stop if started) extruder.
//Toggle extruder tool pseudo-code:
//Check if tool is NOT selected (via a flag),
//  if not selected, check if it is clicked,
//    if clicked, check if hot extruder confirmed or cold extruder flags are set,
//      if set, send message and set flag to say it is selceted.
//Else if it is selected, 
//  highlight tool and check if it is clicked,
//    if clicked, send message and set flag to say it is no longer selected.
//(Display of the tool is performed in the clicked checks.)

if(guiExtruderExtruding ==  false)
{
	if(ImGui::Button(guiExtruderToggleToolName) && (guiCurrentModeBusy == false))
	{
		if(guiHotExtruderConfirmed == true || guiColdExtruderSelected == true)
		{
			guiSerial.writeBytes(&guiExtruderToggleToolMessage[0], guiJogToolsMessageSize);
			guiExtruderExtruding = true;

			guiCurrentModeBusy = true;

			guiSerial.flush(true, false); //Clear the incoming serial buffers.

			//DEBUGGING.
			//cout << "extruder extruding = true" << endl;
		}
	}
}
else
{
	ImGui::PushStyleColor(ImGuiCol_Button, guiToolActiveColour);

	if(ImGui::Button(guiExtruderToggleToolName))
	{
		guiSerial.writeBytes(&guiExtruderToggleToolMessage[0], guiJogToolsMessageSize);
		guiExtruderExtruding = false;

		guiSerial.flush(true, false); //Clear the incoming serial buffers.

		//DEBUGGING.
		//cout << "extruder extruding = false" << endl;
	}

	ImGui::PopStyleColor();
}

} //End of void guiExtruderToggleTool()

void guiExtruderDirectionTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to change extrude direction.

if(ImGui::Button(guiExtruderDirectionToolName) && (guiCurrentModeBusy == false))
{
	guiSerial.writeBytes(&guiExtruderDirectionToolMessage[0], guiJogToolsMessageSize);
		
	if(guiExtruderDirection == guiExtrude)
	{ 
		guiExtruderDirection = retract;
		
		//DEBUGGING.
		//cout << "extruder direction = retract" << endl;
	}
	else //guiExtruderDirection = retract
	{
		guiExtruderDirection = guiExtrude;
		
		//DEBUGGING.
		//cout << "gripper direction = grip" << endl;
	}

	guiSerial.flush(true, false); //Clear the incoming serial buffers.

}

if(guiExtruderDirection == retract){ ImGui::Text(guiExtruderRetractionInfo); }
else{ ImGui::Text(guiExtruderExtrusionInfo); }

} //End of void guiExtruderDirectionTool()

//Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiResetJogParameters(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Reset jog parameters.

if(guiSerial.isInitialized() == true)
{
	guiSerial.writeBytes(&guiResetJogParametersMessage[0], guiJogToolsMessageSize);
}

guiCurrentModeBusy = false;
guiCurrentModeStillBusy = false;

guiCalibrating = false;

guiHoming = false;

guiCurrentJogSpeed = guiDefaultJogSpeed;

guiSelectedJoint = 2;

guiGripperDirection = guiGrip;

guiHotExtruderConfirmed = false;
guiHotExtruderWaiting = false;
guiColdExtruderSelected = false;
guiExtruderExtruding = false;

guiExtruderDirection = guiExtrude;

guiWaitingForPose = false;

guiCurrentFeedRate = guiDefaultFeedRate;

if(guiSerial.isInitialized() == false)
{
	guiCalibrated = false;
	rbtToolSelected = rbtNoTool;
}

guiSerial.flush(true, false); //Clear the incoming serial buffers.

} //End of void guiResetJogParameters()