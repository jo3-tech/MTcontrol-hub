// Copyright (C) 2017 - 2018 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//HEADER FILE
//=======================================================================================================================================

#include "connectionMenu.h"

//GLOBAL VARIABLES & CONSTANTS
//=======================================================================================================================================

//Menu Control
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const char* connectionMenuName = "Connection";
const ImVec2 connectionMenuPos = {20, 15};

//Toolbar and Tool Control
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//No toolbars, only tools.

ofSerial serial;					//Common variable definition. Serial object.

//Scan
//----

const char* scanDevicesToolName = "Scan for Devices";
ImVec2 scanDevicesToolSize = {120, 20};

const char* pleaseConnectSerialInfo = "Please Connect to the Robot First";	//Common variable definition.

//Port
//----

const char* portToolName = ":Port"; //Port drop-down name.
ImVec2 portToolSize = {155, 20};
string noDeviceMessage = "No devices";
vector<string> deviceNames = { noDeviceMessage };			//Vector of strings to store serial device/port names.
									//We could actually use a simple string - see "Combo" and "scanDevices" methods for more info.
int currentDeviceIndex = 0;			//Current index of user-selected device/port from the device/port names.

//Baud
//----

const char* baudToolName = ":Baud";	//Baud drop-down name.
ImVec2 baudToolSize = {120, 20};
const int baud = 57600; //9600;		//(/s) Serial communication speed.
vector<string> baudRates = { "115200", "57600", "38400", "19200", "9600", "4800", "2400" };	//(/s) Serial communication speed.
int currentBaudIndex = 1;

//Connect
//-------

const char* connectToDeviceToolName = " Connect Device  ";
const char* disconnectFromDeviceToolName = "Disconnect Device";
ImVec2 connectToDeviceToolSize = {127, 20};

//FUNCTION IMPLEMENTATIONS
//=======================================================================================================================================

//Main Window
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void connectionMenu(){
//---------------------------------------------------------------------------------------------------------------------------------------

ImGui::SetNextWindowPos(connectionMenuPos);
//ImGui::Begin(connectionMenuName);	//Show connection menu window.
ImGui::Begin(connectionMenuName, NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings);

	//Tools
	//-----

	//Scan

	scanTool();

	//Port

	ImGui::SameLine();	//Show the next tool on the same line.
	portTool();

	//Baud

	ImGui::SameLine();	//Show the next tool on the same line.
	baudTool();

	//Connect

	ImGui::SameLine();	//Show the next tool on the same line.
	connectTool();

ImGui::End(); //End of ImGui::Begin(connectionMenuName,...);

} //End of void connectionMenu()

//Toolbars
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//N/A

//Tools
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void scanTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

ImGui::BeginChild(scanDevicesToolName, scanDevicesToolSize);	//Show the next tool within a sub-window.
		
	if(ImGui::Button(scanDevicesToolName))					//Show button to scan devices.
	{
		scanDevices();
	}

ImGui::EndChild(); //End of ImGui::BeginChild(scanDevicesToolName,...);

} //End of void scanTool()

void portTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

ImGui::BeginChild(portToolName, portToolSize);

	Combo(portToolName, &currentDeviceIndex, deviceNames);	//Show drop-down list of user-selectable devices/ports.

ImGui::EndChild(); //End of ImGui::BeginChild(portToolName...);

} //End of void portTool()

void baudTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

ImGui::BeginChild(baudToolName, baudToolSize);

	Combo(baudToolName, &currentBaudIndex, baudRates);	//Show drop-down list of user-selectable baud rates.

ImGui::EndChild();	//End of ImGui::BeginChild(baudToolName,...);

} //End of void baudTool()

void connectTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

ImGui::BeginChild(connectToDeviceToolName, connectToDeviceToolSize);

		if(serial.isInitialized() ==  false)
		{
			if(ImGui::Button(connectToDeviceToolName))		//Show button to scan devices.
			{
				connectToDevice();
			}
		}
		else
		{
			if(ImGui::Button(disconnectFromDeviceToolName))	//Show button to scan devices.
			{
				connectToDevice();
			}
		}

ImGui::EndChild();	//End of ImGui::BeginChild(connectToDeviceName,...);

} //End of void connectTool()

//Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void scanDevices(){
//---------------------------------------------------------------------------------------------------------------------------------------

vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();

deviceNames.clear();

if(deviceList.empty())
{
	deviceNames.push_back(noDeviceMessage);
}
else
{
	for(int i = 0; i < deviceList.size(); i++)
	{
		deviceNames.push_back(deviceList[i].getDeviceName()); //Push back for proper memory allocation and avoiding garbage.
		//If we used a string you would simply set the string to "" before the for-loops starts,
		//then do myString = myString + "\0"; for compatibility with "ImGui::combo".
		//if(i == deviceList.size() - 1) myString = myString + "\0"; to end it.
	}
}
//serial.listDevices();

} //End of void scanDevices()

void connectToDevice(){
//---------------------------------------------------------------------------------------------------------------------------------------

if(serial.isInitialized() == false)
{
	int currentBaud = stoi(baudRates[currentBaudIndex]);		//Convert selected baud from string to int.
	serial.setup(deviceNames[currentDeviceIndex], currentBaud); //Connect to device if it is not connected.
}
else
{
	serial.close();		//Disconnect from device if it is connected.
	//**NEED TO SEND MESSAGES TO TURN EVERYTHING OFF BEFORE DISCONNECTING; 
	//HEATERS, EXTRUDER ETC**
}

} //End of void connectToDevice()
