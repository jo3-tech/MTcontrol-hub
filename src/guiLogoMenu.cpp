// Copyright (C) 2017 - 2020 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//HEADER FILE
//=======================================================================================================================================

#include "guiLogoMenu.h"

//GLOBAL VARIABLES & CONSTANTS
//=======================================================================================================================================

//Menu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Logo
//++++

const char* guiLogoMenuName = " "; //NOTE; ImGui::Begin(...) doesn't accept an empty string "".
float guiLogoMenuPosX;
float guiLogoMenuPosY;

//Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Logos - company and software
//++++++++++++++++++++++++++++

float guiCompanyLogoScaleFactor = 0.015; //*guiScaleFactor.
float guiSoftwareLogoScaleFactor = 0.02; // "

ImVec2 guiLogoPos;

//FUNCTION IMPLEMENTATIONS
//=======================================================================================================================================

//Menu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiLogoMenu(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display logo menu.

ImGui::SetNextWindowPos(ImVec2(guiLogoMenuPosX, guiLogoMenuPosY));

ImGui::SetNextWindowSize(ImVec2(guiSubWindowSizeX*guiScaleFactor, 4*guiScaleFactor));

ImGui::Begin(guiLogoMenuName, NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	guiLogoPos = ImGui::GetCursorScreenPos();

	//NOTE: guiDisplayLogo() cannot be called here because it uses core openFrameworks methods and hence needs to be called when
	//ofxImGui GUI ends.

ImGui::End();

}

//Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiGetLogoMenuPos(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Get the position for the logo menu based on the scaled values of the sub window.

guiLogoMenuPosX = guiSubWindowPosX;

guiLogoMenuPosY = guiSubWindowPosY + guiSubWindowSizeY*guiScaleFactor + 0.2*guiScaleFactor;

}

void guiDisplayLogo(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display logos.

float guiSoftwareLogoWidth = guiSoftwareLogo.getWidth()*guiSoftwareLogoScaleFactor*guiScaleFactor;

float guiSoftwareLogoHeight = guiSoftwareLogo.getHeight()*guiSoftwareLogoScaleFactor*guiScaleFactor;

float guiCompanyLogoWidth = guiCompanyLogo.getWidth()*guiCompanyLogoScaleFactor*guiScaleFactor;

float guiCompanyLogoHeight = guiCompanyLogo.getHeight()*guiCompanyLogoScaleFactor*guiScaleFactor;

guiSoftwareLogo.draw(guiLogoPos.x, guiLogoPos.y, guiSoftwareLogoWidth, guiSoftwareLogoHeight);

guiCompanyLogo.draw(guiLogoPos.x + guiSoftwareLogoWidth + 8.5*guiScaleFactor, guiLogoPos.y + 1.5*guiScaleFactor, guiCompanyLogoWidth, guiCompanyLogoHeight);

}
