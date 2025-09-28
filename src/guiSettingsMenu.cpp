// Copyright (C) 2017 - 2020 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//HEADER FILE
//=======================================================================================================================================

#include "guiSettingsMenu.h"

//GLOBAL VARIABLES & CONSTANTS
//=======================================================================================================================================

//Menu/Menu Bar
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Settings
//++++++++

const char* guiSettingsMenuName = "Settings";

//Menu Bar Items (Toolbars), Tools and Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Robot Arm Tool Selection
//++++++++++++++++++++++++

const int guiToolSelectToolsMessageSize = guiGeneralToolMessageSize;

const char* guiToolSelectToolbarName = "Select Tool";

const char* guiNoToolSelectToolName = "No Tool";
unsigned char guiNoToolSelectToolMessage[guiToolSelectToolsMessageSize] = {'J', '0', '0', '0', '\n'};
const char* guiPenSelectToolName = "Pen";
unsigned char guiPenSelectToolMessage[guiToolSelectToolsMessageSize] = {'J', '0', '2', '1', '\n'};
const char* guiGripperSelectToolName = "Gripper";
unsigned char guiGripperSelectToolMessage[guiToolSelectToolsMessageSize] = {'J', '0', '3', '1', '\n'};
const char* guiExtruderSelectToolName = "Extruder";
unsigned char guiExtruderSelectToolMessage[guiToolSelectToolsMessageSize] = {'J', '0', '4', '1', '\n'};

//Help
//++++

const char* guiHelpToolbarName = "Help";

const char* guiAboutToolName = "About MTcontrol-hub";
const char* guiCloseAboutToolName = "Close";
const char* guiOpenAboutLicenseToolName = "License";
string guiAboutLicenseFilePath = "License.txt";

bool guiDisplayAboutPopup;

string guiAboutInfo = "\n           MTcontrol-hub"
				      "\n           Version " + guiProgramVersion +
				      "\n           Copyright   2018 MORGRITECH"
				      "\n";

float guiAboutIconScaleFactor = 0.007;       //*guiScaleFactor.
float guiCopyrightSymbolScalFactor = 0.0045; // "

ImVec2 guiAboutGraphicsPos;

const char* guiSoftwareWebPageToolName = "Online tutorials"; //Link to the ncHub sub-page on morgritech.com
string guiSoftwareWebPageUrl = "http://morgritech.com/nchub";

const char* guiCompanyWebPageToolName = "morgritech.com"; //Link to morgritech.com.
string guiCompanyWebPageUrl = "http://morgritech.com";	

//FUNCTION IMPLEMENTATIONS
//=======================================================================================================================================

//Menu/Menu Bar
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiSettingsMenuBar(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display settings menu/menu bar.

if(ImGui::BeginMenuBar()) //This is only true if the ImGuiWindowFlags_MenuBar is set in the main window.
{
	//Menu Bar Items (Toolbars)
	//-------------------------

	guiToolSelectToolbar();

	guiHelpToolbar();

ImGui::EndMenuBar(); //This must be placed here as it must only be called if BeginMenuBar() returned true.
}

}

//Menu Bar Items (Toolbars)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiToolSelectToolbar(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool-select menu bar item (toolbar) and tools.

if(ImGui::BeginMenu(guiToolSelectToolbarName))	//Show tool selection toolbar.
{
	//Tools
	//-----

	guiToolSelectTool(guiNoToolSelectToolName, guiNoToolSelectToolMessage, rbtNoTool);		 //Show "no tool" tool select tool.
	guiToolSelectTool(guiPenSelectToolName, guiPenSelectToolMessage, rbtPen);				 //Show pen tool select tool.
	guiToolSelectTool(guiGripperSelectToolName, guiGripperSelectToolMessage, rbtGripper);	 //Show gripper tool select tool.
	guiToolSelectTool(guiExtruderSelectToolName, guiExtruderSelectToolMessage, rbtExtruder); //Show extruder tool select tool.

	ImGui::EndMenu();
}

}

void guiHelpToolbar(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display help menu bar item (toolbar).

if(ImGui::BeginMenu(guiHelpToolbarName)) //Show help toolbar.
{
	//Tools
	//-----

	guiAboutTool();

	guiSoftwareWebPageTool();

	guiCompanyWebPageTool();

	ImGui::EndMenu();
}

//Popups
//------

guiAboutPopUp(); //This needs to be placed at this level to work properly.

}

//Tools
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiToolSelectTool(const char* toolName, unsigned char toolMessage[], int tool){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to select robot tool.

if(ImGui::MenuItem(toolName, NULL, rbtToolSelected == tool)) //Show "xxxx" tool-select tool.
{
	guiSerial.writeBytes(&toolMessage[0], guiToolSelectToolsMessageSize);
	rbtToolSelected = tool;
}

}

void guiAboutTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to show information about program/application.

if(ImGui::MenuItem(guiAboutToolName)) //Show about tool.
{
	guiDisplayAboutPopup = true;
}

}

void guiSoftwareWebPageTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to launch program/application web page.

if(ImGui::MenuItem(guiSoftwareWebPageToolName)) //Show software web page tool.
{
	ofLaunchBrowser(guiSoftwareWebPageUrl);
}

}

void guiCompanyWebPageTool(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display tool to launch company website.

if(ImGui::MenuItem(guiCompanyWebPageToolName))	//Show company web page tool.
{
	ofLaunchBrowser(guiCompanyWebPageUrl);
}

}

//Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiAboutPopUp(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display "about program/application" popup.
//NOTE: This must be implemented exactly as it is below otherwise it doesn't behave properly.
//Placement of this function within the program is also important. It shouldn't be placed within
//more than 1 or 2 if-statements and definitely not within the if-statment for a button or within
//a menu bar or it won't work.. even if you remove the "if(displayPopupFlag == true)" from here.

if(guiDisplayAboutPopup == true)
{
	ImGui::OpenPopup(guiAboutToolName); //Open the popup.
}

if(ImGui::BeginPopupModal(guiAboutToolName, &guiDisplayAboutPopup, ImGuiWindowFlags_AlwaysAutoResize)) //Start writing to the popup only if it has been opened.
{
	guiAboutGraphicsPos = ImGui::GetCursorScreenPos();

	const char* tempAboutInfo = guiAboutInfo.c_str();

	ImGui::Text(tempAboutInfo);

	if(ImGui::Button(guiOpenAboutLicenseToolName)){ string filePath = ofToDataPath(guiAboutLicenseFilePath, false); system(filePath.c_str()); }

	if(ImGui::Button(guiCloseAboutToolName)){ guiDisplayAboutPopup = false; ImGui::CloseCurrentPopup(); }
	
	//TESTING.
	//if(ImGui::IsMouseClicked(0)){ guiDisplayAboutPopup = false; ImGui::CloseCurrentPopup(); }

	ImGui::EndPopup(); //This must be placed here as it must only be called if BeginPopUpModal(...) returned true.
}

} //End of void guiAboutPopUp()

void guiDisplayAboutGraphics(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display icons/logos.

if(guiDisplayAboutPopup == true)
{
	float guiSoftwareIconWidth = guiSoftwareIcon.getWidth()*guiAboutIconScaleFactor*guiScaleFactor;

	float guiSoftwareIconHeight = guiSoftwareIcon.getHeight()*guiAboutIconScaleFactor*guiScaleFactor;

	float guiCopyrightSymbolWidth = guiCopyrightSymbol.getWidth()*guiCopyrightSymbolScalFactor*guiScaleFactor;

	float guiCopyrightSymbolHeight = guiCopyrightSymbol.getHeight()*guiCopyrightSymbolScalFactor*guiScaleFactor;

	guiSoftwareIcon.draw(guiAboutGraphicsPos.x, guiAboutGraphicsPos.y, guiSoftwareIconWidth, guiSoftwareIconHeight);

	guiCopyrightSymbol.draw(guiAboutGraphicsPos.x + 11*guiScaleFactor, guiAboutGraphicsPos.y + 3*guiScaleFactor, guiCopyrightSymbolWidth, guiCopyrightSymbolHeight);
}

}
