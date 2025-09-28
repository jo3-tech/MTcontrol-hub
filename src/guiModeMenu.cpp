// Copyright (C) 2017 - 2020 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//HEADER FILE
//=======================================================================================================================================

#include "guiModeMenu.h"

//GLOBAL VARIABLES & CONSTANTS
//=======================================================================================================================================

//Menu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Mode
//++++

const char* guiModeMenuName = "Mode";

//Toolbar, Tools and Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Jog
//+++

const char* guiJogToolbarName = "Jog (Manual Control)";
const char* guiGcSenderToolbarName = "G-Code Sender";

//See header and cpp files for each mode i.e. modeXyz.h, modeXyz.cpp
//Where Xyz is the name of the mode e.g. Jog, GcSender, etc.

//FUNCTION IMPLEMENTATIONS
//=======================================================================================================================================

//Menu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiModeMenu(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display mode menu.

guiGeneralGuiVerticalSpacing(guiMenuSpacingY);

guiMenuHeaderTitle(guiModeMenuName, false);

//Toolbars
//--------

guiModeMenuToolbarTab(guiJogToolbarId, guiJogToolbarName);

ImGui::SameLine(); //Show the next tool on the same line.
guiModeMenuToolbarTab(guiGcSenderToolbarId, guiGcSenderToolbarName);

ImGui::Separator();

guiJogToolbar();
guiGcSenderToolbar();

}

//Toolbar Tabs
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiModeMenuToolbarTab(const int toolbarId, const char* toolbarName){
//---------------------------------------------------------------------------------------------------------------------------------------

//Create a mode menu toolbar tab.

if(guiModeMenuToolbarId != toolbarId)
{
	ImGui::PushStyleColor(ImGuiCol_Button, guiToolbarColour);

	if(ImGui::Button(toolbarName)) //Show toolbar tab.
	{
		if(guiCurrentModeBusy == true || guiCurrentModeStillBusy == true)
		{
			guiDisplayBusyPopup = true;
		}
		else
		{
			guiDisplayBusyPopup = false;

			guiModeMenuToolbarId = toolbarId;
			
			if(toolbarId == guiJogToolbarId){ guiReEntryIntoJog = true; }
			if(toolbarId == guiGcSenderToolbarId){ guiSerial.flush(true, true); }
		}
	}

	ImGui::PopStyleColor();
}
else if(guiModeMenuToolbarId == toolbarId)
{
	ImGui::PushStyleColor(ImGuiCol_Button, guiToolbarActiveColour);
	ImGui::Button(toolbarName); //Show highlighted toolbar tab.
	ImGui::PopStyleColor();
}

}

//Toolbars, Tool and Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//See notes in header file.
