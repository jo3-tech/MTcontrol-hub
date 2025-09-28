// Copyright (C) 2017 - 2018 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//HEADER FILE
//=======================================================================================================================================

#include "logoMenu.h"

//GLOBAL VARIABLES & CONSTANTS
//=======================================================================================================================================

//Menu Control
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const char* logoMenuName = "";
const ImVec2 logoMenuPos = {255, 540};
const ImVec2 logoMenuSize = {265, 115};

//Toolbar and Tool Control
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//No toolbars, only tools.

//Logos - company and software
//----------------------------

const char* logoToolName = "Logos";

ofImage companyLogo;	//Common variable defintion. 
string companyLogoFilePath = "logos/company logo.png";
ofImage softwareLogo;	//Common variable defintion. 
string softwareLogoFilePath = "logos/software logo.png";
ofImage softwareIcon;	//Common variable defintion. 
string softwareIconFilePath = "logos/software icon.png";

float companyLogoScaleFactor = 0.23;
float softwareLogoScaleFactor = 0.14;
float iconScaleFactor = 0.12;

ImVec2 logoPos;

//FUNCTION IMPLEMENTATIONS
//=======================================================================================================================================

//Main Window
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void logoMenu(){
//---------------------------------------------------------------------------------------------------------------------------------------

ImGui::SetNextWindowPos(logoMenuPos);
ImGui::SetNextWindowSize(logoMenuSize);
//ImGui::Begin(logoMenuName, NULL, ImGuiWindowFlags_NoTitleBar); //Show logo menu window.
ImGui::Begin(logoMenuName, NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

	logoPos = ImGui::GetCursorScreenPos();

ImGui::End(); //End of ImGui::Begin(logoMenuName,...);

} //End of void logoMenu()

//Toolbars
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//N/A

//Tools
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//N/A

//Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void loadLogo(){
//---------------------------------------------------------------------------------------------------------------------------------------

companyLogo.load(companyLogoFilePath);
softwareLogo.load(softwareLogoFilePath);
softwareIcon.load(softwareIconFilePath);

} //End of void loadLogo()

void displayLogo(){
//---------------------------------------------------------------------------------------------------------------------------------------

float softwareIconWidth = softwareIcon.getWidth()*iconScaleFactor;

float softwareIconHeight = softwareIcon.getHeight()*iconScaleFactor;

float softwareLogoWidth = softwareLogo.getWidth()*softwareLogoScaleFactor;

float softwareLogoHeight = softwareLogo.getHeight()*softwareLogoScaleFactor;

float companyLogoWidth = companyLogo.getWidth()*companyLogoScaleFactor;

float companyLogoHeight = companyLogo.getHeight()*companyLogoScaleFactor;

softwareIcon.draw(logoPos.x + 14, logoPos.y, softwareIconWidth, softwareIconHeight);

softwareLogo.draw(logoPos.x + 14 + softwareIconWidth + 10, logoPos.y + 10, softwareLogoWidth, softwareLogoHeight);

companyLogo.draw(logoPos.x, logoPos.y + softwareLogoHeight + 40, companyLogoWidth, companyLogoHeight);

} //End of void displayLogo()