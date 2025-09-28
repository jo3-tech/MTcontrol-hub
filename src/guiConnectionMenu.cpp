// Copyright (C) 2017 - 2020 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//HEADER FILE
//=======================================================================================================================================

#include "guiConnectionMenu.h"

//GLOBAL VARIABLES & CONSTANTS
//=======================================================================================================================================

//Menu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Connection
//++++++++++

const char* guiConnectionMenuName = "Connection";

float guiConnectionToolsSpacingX = 0.7; //*guiScaleFactor.

//Tools and Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Scan
//++++

const char* guiScanDevicesToolName = "Scan for Devices";

//Port
//++++

const char* guiPortToolName = "Port"; //Port drop-down name.
string guiNoDeviceInfo = "No devices";
vector<string> guiDeviceNames = { guiNoDeviceInfo }; //Vector of strings to store guiSerial device/port names.
												  //We could actually use a simple string - 
												  //see "Combo" and "guiScanDevices" methods for more info.
vector<int> guiComPorts;
int guiCurrentDeviceIndex = 0;	//Current index of user-selected device/port from the device/port names.

//Baud
//++++

const char* guiBaudToolName = "Baud";	//Baud drop-down name.
vector<string> guiBaudRates = { "2000000", "1000000", "500000", "250000", "230400", "115200", "76800", "57600", "38400", "28800", "19200", "14400", "9600", "4800", "2400" }; //(/s) guiSerial communication speed.
int guiCurrentBaudIndex = 5;

//Connect
//+++++++

const char* guiConnectToDeviceToolName = " Connect Device  ";
const char* guiDisconnectFromDeviceToolName = "Disconnect Device";

const char guiCloseSerialConnectionMessage = '[';

//FUNCTION IMPLEMENTATIONS
//=======================================================================================================================================

//Menu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiConnectionMenu(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display connection menu and tools.

guiGeneralGuiVerticalSpacing(guiMenuSpacingY);

guiMenuHeaderTitle(guiConnectionMenuName, true);

//Tools
//-----

guiScanTool();

guiGeneralGuiHorizontalSpacing(guiConnectionToolsSpacingX); //Show the next tool on the same line.
ImGui::SetNextItemWidth(10*guiScaleFactor);
guiPortTool();

guiGeneralGuiHorizontalSpacing(guiConnectionToolsSpacingX);
ImGui::SetNextItemWidth(5*guiScaleFactor);
guiBaudTool();

guiGeneralGuiHorizontalSpacing(guiConnectionToolsSpacingX);
guiConnectTool();

}

//Tools
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiScanTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to scan for devices.

if(ImGui::Button(guiScanDevicesToolName)) //Show button to scan devices.
{
	guiScanDevices();
}

}

void guiPortTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to select a serial port.

guiCombo(guiPortToolName, &guiCurrentDeviceIndex, guiDeviceNames); //Show drop-down list of user-selectable devices/ports.

}

void guiBaudTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to select a baud rate.

guiCombo(guiBaudToolName, &guiCurrentBaudIndex, guiBaudRates); //Show drop-down list of user-selectable baud rates.

}

void guiConnectTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to connect to a serial device.

if(guiSerial.isInitialized() ==  false)
{
	if(ImGui::Button(guiConnectToDeviceToolName)) //Show button to connect to device.
	{
		guiConnectToDevice();
	}
}
else
{
	if(ImGui::Button(guiDisconnectFromDeviceToolName))	//Show button to disconnect from device.
	{
		guiConnectToDevice();
	}
}

} //End of void guiConnectTool()

//Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiScanDevices(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Scan guiSerial ports for connected devices.

vector <ofSerialDeviceInfo> deviceList = guiSerial.getDeviceList();

guiDeviceNames.clear();

if(deviceList.empty())
{
	guiDeviceNames.push_back(guiNoDeviceInfo);
}
else
{
	for(int i = 0; i < deviceList.size(); i++)
	{
		guiDeviceNames.push_back(deviceList[i].getDeviceName()); //Push back for proper memory allocation and avoiding garbage.
		guiComPorts.push_back(deviceList[i].getDeviceID()); 

		if(guiDeviceNames[i].find("Arduino") != string::npos){ guiCurrentDeviceIndex = i; }

		//**If we used a string you would simply set the string to "" before the for-loops starts,
		//then do myString = myString + "\0"; for compatibility with "ImGui::combo".
		//if(i == deviceList.size() - 1) myString = myString + "\0"; to end it.**
	}
}

//DEBUGGING.
//guiSerial.listDevices();

}

void guiConnectToDevice(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Connect to selected guiSerial device.

if(guiSerial.isInitialized() == false)
{
	guiCurrentModeBusy == false;
	guiCurrentModeStillBusy = false;

	int currentBaud = stoi(guiBaudRates[guiCurrentBaudIndex]); //Convert selected baud from string to int.
	guiSerial.setup(guiComPorts[guiCurrentDeviceIndex], currentBaud); //Connect to device if it is not connected.
	
	guiSerial.flush(true, true); //Clear the incoming and outgoing guiSerial buffers.
	guiSerial.flush(true, true);
}
else
{
	guiCurrentModeBusy == false;
	guiCurrentModeStillBusy = false;

	guiSerial.writeByte(guiCloseSerialConnectionMessage); //Arduino doesn't detect closing guiSerial connection using below method, so send message.
	guiSerial.close(); //Disconnect from device if it is connected.

	//Note: If you pull out the guiSerial cable, the arduino will detect this as guiSerial connection being lost and turn off power to pins?
	//hence stopping all activities.
	//However the arduino cannot detect when the connection closed using guiSerial.close()l, hence a message is sent to tell the arduino
	//to end guiSerial connection and hence stop all activities. 
	//Such activities may be to turn off heaters, extruder, etc and auto-calibration and all trajectory actions.
}

}
