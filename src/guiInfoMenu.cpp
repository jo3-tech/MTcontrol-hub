// Copyright (C) 2017 - 2020 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//HEADER FILE
//=======================================================================================================================================

#include "guiInfoMenu.h"

//GLOBAL VARIABLES & CONSTANTS
//=======================================================================================================================================

//Menu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Info
//++++

const char* guiInfoMenuName = "MTarm Information";

ImVec2 guiInfoMenuPos = {410, 440};

const int guiInfoToolsMessageSize = guiGeneralToolMessageSize;

string guiInfoWindowConnectionInfo = "...Waiting for connection...\n\n";

string guiInfoWindowWaitingInfo = "...Getting information...\n\n";

string guiInfoWindowInfo = "(Drag to reposition window)\n\n";

string guiIwInfoToDisplay = guiInfoWindowConnectionInfo;

//Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Firmware & Hardware/Robot Version Information
//+++++++++++++++++++++++++++++++++++++++++++++

string guiFirmWareAndRobotInfo;

string guiFrInfoToDisplay;

//Robot and Tool Parameters
//+++++++++++++++++++++++++

string guiRobotParameters;

string guiRpInfoToDisplay;

//FUNCTION IMPLEMENTATIONS
//=======================================================================================================================================

//Menu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiInfoMenu(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display info menu.

ImGui::SetNextWindowPos(guiInfoMenuPos, ImGuiCond_FirstUseEver);

ImGui::Begin(guiInfoMenuName, NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings); //Show info menu window.

guiDisplayInfoTool();

guiCheckForVersionInfo(); 

guiCheckForRobotParameters();

guiResetInfoParameters();

ImGui::End();

}

//Tools
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiDisplayInfoTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Tool to display (firmware & hardware/robot) version information and robot parameters.

const char* tempguiIwInfoToDisplay = guiIwInfoToDisplay.c_str();
ImGui::Text(tempguiIwInfoToDisplay);

const char* tempguiFrInfoToDisplay = guiFrInfoToDisplay.c_str();
ImGui::Text(tempguiFrInfoToDisplay);

const char* tempguiRpInfoToDisplay = guiRpInfoToDisplay.c_str();
ImGui::Text(tempguiRpInfoToDisplay);

}

//Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiCheckForVersionInfo(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Check for (firmware & hardware/robot) version information from robot.

if((guiSerial.isInitialized() == true) && (guiVersionInfoObtained == false))
{
	guiIwInfoToDisplay = guiInfoWindowWaitingInfo;
	guiCurrentModeBusy = true;

	while(guiSerial.available() > 0)
	{
		char c = guiSerial.readByte(); //Read a character/byte of data.

		//DEBUGGING.
		//cout << "reading byte" << endl;
		//cout << c << endl;
		
		if(c == guiDeviceReadyMessage)
		{
			guiFrInfoToDisplay = guiFirmWareAndRobotInfo; 
			guiFirmWareAndRobotInfo =  "";
			guiVersionInfoObtained = true;	

			guiIwInfoToDisplay = guiInfoWindowInfo;
		
			if(guiModeMenuToolbarId == guiJogToolbarId)
			{
				//DEFERRED. guiInfoMenu.
				//guiSerial.writeBytes(&guiRequestRobotParametersMessage[0], guiInfoToolsMessageSize); 
				
				guiListenForRobotParameters = true; 
			}
			
			guiCurrentModeBusy = false;

			break; 
		}
		else{ guiFirmWareAndRobotInfo = guiFirmWareAndRobotInfo + c; }

	} //End of while(guiSerial.available() > 0)

} //End of if((guiSerial.isInitialized() == true) && (guiVersionInfoObtained == false))

} //End of void guiCheckForVersionInfo()

void guiCheckForRobotParameters(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Check for robot parameters from the robot.

if(guiListenForRobotParameters == true)
{
	//DEBUGGING.
	//cout << "I should be getting robot parameters now!" << endl;

	while(guiSerial.available() > 0)
	{
		char c = guiSerial.readByte(); //Read a character/byte of data.

		//DEBUGGING.
		//cout << "reading byte" << endl;
		//cout << c << endl;
		
		if(c == guiDeviceReadyMessage)
		{ 
			//DEBUGGING.
			//cout << "I've got them!" << endl;

			guiRpInfoToDisplay = guiRobotParameters;
			guiRobotParameters = "";
			guiListenForRobotParameters = false; 

			break; 
		}
		else{ guiRobotParameters = guiRobotParameters + c; }
	}

} //End of if((guiSerial.isInitialized() == false) || (guiModeMenuToolbarId != guiJogToolbarId))

} //End of void guiCheckForRobotParameters()

void guiResetInfoParameters(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to reset jog parameters.

if((guiSerial.isInitialized() == false) || (guiModeMenuToolbarId != guiJogToolbarId))
{
	guiListenForRobotParameters = false;
	guiRobotParameters = "";
	guiRpInfoToDisplay = "";

	if(guiSerial.isInitialized() == false)
	{
		guiIwInfoToDisplay = guiInfoWindowConnectionInfo;
		guiVersionInfoObtained = false;
		guiFirmWareAndRobotInfo = "";
		guiFrInfoToDisplay = "";
	}

}

}