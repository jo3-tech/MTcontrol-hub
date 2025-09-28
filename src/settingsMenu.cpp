// Copyright (C) 2017 - 2018 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//HEADER FILE
//=======================================================================================================================================

#include "settingsMenu.h"

//GLOBAL VARIABLES & CONSTANTS
//=======================================================================================================================================

//Menu Control
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const char* settingsMenuName = "Settings";
const ImVec2 settingsMenuPos = {610, 15};
const ImVec2 settingsMenuSize = {150, 55};

//Toolbar and Tool Control
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Robot arm tool selection
//------------------------

const int toolSelectToolsMessageSize = generalToolMessageSize;

const char* toolSelectToolbarName = "Select Tool";

const char* noToolSelectToolName = "No Tool";
unsigned char noToolSelectToolMessage[toolSelectToolsMessageSize] = {'J', '0', '0', '0', '\n'};
const char* penSelectToolName = "Pen";
unsigned char penSelectToolMessage[toolSelectToolsMessageSize] = {'J', '0', '2', '1', '\n'};
const char* gripperSelectToolName = "Gripper";
unsigned char gripperSelectToolMessage[toolSelectToolsMessageSize] = {'J', '0', '3', '1', '\n'};
const char* extruderSelectToolName = "Extruder";
unsigned char extruderSelectToolMessage[toolSelectToolsMessageSize] = {'J', '0', '4', '1', '\n'};

const int NoTool = 0;	//Common variable definitions.
const int Pen = 1;
const int Gripper = 2;
const int Extruder = 3;
int toolSelected = NoTool;

//Help
//----

const char* helpToolbarName = "Help";

const char* aboutToolName = "About ncHub";
const char* closeAboutToolName = "Close";
const char* openAboutLicenseToolName = "License";
string aboutLicenseFilePath = "License.txt";

bool displayAboutPopup;

string aboutInfo = "\n         Version " + programVersion + 
				   "\n         Copyright   2018 Joseph Morgridge"
				   "\n         Mogritech"
//				   "\n"
//				   "\n See License.txt contained in the main"
//				   "\n folder of the software for terms and"
//				   "\n conditions."
				   "\n";

float aboutLogoScaleFactor = 0.08;
float aboutIconScaleFactor = 0.12;
float copyrightSymbolScalFactor = 0.059;

ImVec2 aboutLogoPos;

const char* softwareWebPageToolName = "Online tutorials";	     //Link to the ncHub sub-page on mogritech.com
string softwareWebPageUrl = "http://mogritech.com/nchub";

const char* companyWebPageToolName = "mogritech.com";		     //Link to mogritech.com
string companyWebPageUrl = "http://mogritech.com";	

//FUNCTION IMPLEMENTATIONS
//=======================================================================================================================================

//Main Window and Menu Bar
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void settingsMenu(){
//---------------------------------------------------------------------------------------------------------------------------------------

ImGui::SetNextWindowPos(settingsMenuPos);
ImGui::SetNextWindowSize(settingsMenuSize);
//ImGui::Begin(settingsMenuName, NULL, ImGuiWindowFlags_MenuBar);	//Show settings menu window.
ImGui::Begin(settingsMenuName, NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);

	if(ImGui::BeginMenuBar())	//This is only true if the ImGuiWindowFlags_MenuBar is set as performed above.
	{
		//Menu's/menu bar items
		//----------------------

		//Robot arm tool selection

		toolSelectToolbar();

		//Help

		helpToolbar();

	ImGui::EndMenuBar();
	} //End of ImGui::BeginMenuBar()

ImGui::End(); //End of ImGui::Begin(settingsMenuName,..)

} //End of void settingsMenu()

//Menu's/Menu Bar Items
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void toolSelectToolbar(){
//---------------------------------------------------------------------------------------------------------------------------------------

if(ImGui::BeginMenu(toolSelectToolbarName))	//Show tool selection toolbar.
{
	//Menu items
	//----------

	//Robot arm tools

	toolSelectTool(noToolSelectToolName, noToolSelectToolMessage, NoTool);		 //Show "no tool" tool select tool.
	toolSelectTool(penSelectToolName, penSelectToolMessage, Pen);				 //Show pen tool select tool.
	toolSelectTool(gripperSelectToolName, gripperSelectToolMessage, Gripper);	 //Show gripper tool select tool.
	toolSelectTool(extruderSelectToolName, extruderSelectToolMessage, Extruder); //Show gripper tool select tool.

	//Program busy toolbar
	//--------------------

	if(serial.isInitialized() == false)
	{
		displayBusyPopup = true;
			
		infoPopupToolBar(programBusyToolBarName, pleaseConnectSerialInfo, displayBusyPopup);
		//ImGui::MenuItem(pleaseConnectSerialInfo);
	}
	else if(currentModeBusy == true)
	{
		displayBusyPopup = true;
		
		infoPopupToolBar(programBusyToolBarName, programBusyInfo, displayBusyPopup);
		//ImGui::MenuItem(programBusyInfo);
	}

ImGui::EndMenu();
} //End of ImGui::BeginMenu(toolSelectToolbarName,...)

} //End of void toolSelectToolbar()

void helpToolbar(){
//---------------------------------------------------------------------------------------------------------------------------------------

if(ImGui::BeginMenu(helpToolbarName))	//Show help toolbar.
{
	//Menu items
	//----------

	//About tool

	aboutTool();

	//Software web page tool

	softwareWebPageTool();

	companyWebPageTool();

ImGui::EndMenu();
} //End of ImGui::BeginMenu(helpToolbarName,...)

//Popups
//------

aboutPopUp();

} //End of void helpToolbar()

//Menu Items
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void toolSelectTool(const char* toolName, unsigned char toolMessage[], int tool){
//---------------------------------------------------------------------------------------------------------------------------------------

if(ImGui::MenuItem(toolName, NULL, toolSelected == tool))	//Show "xxxx" tool-select tool.
{
	serial.writeBytes(&toolMessage[0], toolSelectToolsMessageSize);
	toolSelected = tool;
}

} //End of void toolSelectTool(const char* toolName, unsigned char toolMessage[], int tool)

void aboutTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

if(ImGui::MenuItem(aboutToolName))	//Show about tool.
{
	displayAboutPopup = true;
}

} //End of void aboutTool()

void softwareWebPageTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

if(ImGui::MenuItem(softwareWebPageToolName))	//Show software web page tool.
{
	ofLaunchBrowser(softwareWebPageUrl);
}

} //End of void softwareWebPageTool()

void companyWebPageTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

if(ImGui::MenuItem(companyWebPageToolName))	//Show company web page tool.
{
	ofLaunchBrowser(companyWebPageUrl);
}

} //End of void companyWebPageTool()

//Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void aboutPopUp(){
//---------------------------------------------------------------------------------------------------------------------------------------
//NOTE: This must be implemented exactly as it is below otherwise it doesn't behave properly.
//Placement of this function within the program is also important. It shouldn't be placed within
//more than 1 or 2 if-statements and definitely not within the if-statment for a button or within
//a menu bar or it won't work.. even if you remove the "if(displayPopupFlag == true)" from here.

if(displayAboutPopup == true)
{
	ImGui::OpenPopup(aboutToolName);
}

if(ImGui::BeginPopupModal(aboutToolName, &displayAboutPopup, ImGuiWindowFlags_AlwaysAutoResize))
{
	aboutLogoPos = ImGui::GetCursorScreenPos();

	const char* tempAboutInfo = aboutInfo.c_str();

	ImGui::Text(tempAboutInfo);

	if(ImGui::Button(openAboutLicenseToolName)){ string filePath = ofToDataPath(aboutLicenseFilePath, true); system(filePath.c_str()); }

	if(ImGui::Button(closeAboutToolName)){ displayAboutPopup = false; ImGui::CloseCurrentPopup(); }

	//if(ImGui::IsMouseClicked(0)){ displayAboutPopup = false; ImGui::CloseCurrentPopup(); }

	ImGui::EndPopup();
}

} //End of void aboutPopUp()

void displayAboutGraphics(){
//---------------------------------------------------------------------------------------------------------------------------------------

if(displayAboutPopup == true)
{
	float softwareIconWidth = softwareIcon.getWidth()*aboutIconScaleFactor;

	float softwareIconHeight = softwareIcon.getHeight()*aboutIconScaleFactor;

	float softwareLogoWidth = softwareLogo.getWidth()*aboutLogoScaleFactor;

	float softwareLogoHeight = softwareLogo.getHeight()*aboutLogoScaleFactor;

	float copyrightSymbolWidth = copyrightSymbol.getWidth()*copyrightSymbolScalFactor;

	float copyrightSymbolHeight = copyrightSymbol.getHeight()*copyrightSymbolScalFactor;

	softwareIcon.draw(aboutLogoPos.x, aboutLogoPos.y, softwareIconWidth, softwareIconHeight);

	softwareLogo.draw(aboutLogoPos.x + softwareIconWidth + 7, aboutLogoPos.y, softwareLogoWidth, softwareLogoHeight);

	copyrightSymbol.draw(aboutLogoPos.x + 128, aboutLogoPos.y + 26, copyrightSymbolWidth, copyrightSymbolHeight);

}

} //End of void displayAboutGraphics()