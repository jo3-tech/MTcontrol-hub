// Copyright (C) 2017 - 2018 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//HEADER FILE
//=======================================================================================================================================

#include "modeMenu.h"

//GLOBAL VARIABLES & CONSTANTS
//=======================================================================================================================================

//Menu Control
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const char* modeMenuName = "Mode";
const ImVec2 modeMenuPos = {20, 80};
const ImVec2 modeMenuSize = {740, 450};

int MODE_MENU = 1;				//Common variable definitions. 
const int Jog = 1;			
const int Gcode_Sender = 2;

//Toolbar and Tool Control
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//See header and cpp files for each mode i.e. modeXyz.h, modeXyz.cpp
//Where Xyz is the name of the mode e.g. Jog, GcSender, etc.

//FUNCTION IMPLEMENTATIONS
//=======================================================================================================================================

//Main Window
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void modeMenu(){
//---------------------------------------------------------------------------------------------------------------------------------------

ImGui::SetNextWindowPos(modeMenuPos);
ImGui::SetNextWindowSize(modeMenuSize);
//ImGui::Begin(modeMenuName);	//Show mode menu window.
ImGui::Begin(modeMenuName, NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);

	//Program busy toolbar
	//--------------------

	infoPopupToolBar(programBusyToolBarName, programBusyInfo, displayBusyPopup);

	//Jog toolbar
	//-----------

	jogToolbar();

	//G-code sender toolbar
	//---------------------

	gcSenderToolbar();

ImGui::End(); //End of ImGui::Begin(modeMenuName,..)

}

//Toolbars
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//See notes in header file.

//Tools
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//See above.

//Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//See above.