// Copyright (C) 2017 - 2020 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//PREPROCESSOR DIRECTIVES/INCLUDE GAURDS
//=======================================================================================================================================

#pragma once

//LIBRARIES
//=======================================================================================================================================

#include "guiCommon.h"

//FUNCTION PROTOTYPE DEFINITIONS
//=======================================================================================================================================

//Toolbar
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiJogToolbar();

//Tools
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Robot Jog Tools
//+++++++++++++++

void guiJogKeyboardInput(bool keyPressed, int key);

void guiSelectJointKeyboardInput(bool keyPressed, int jointToSelect, unsigned char toolMessage[]);

void guiSelectDirectionKeyboardInput(bool keyPressed, bool &directionKeyHeld, unsigned char toolMessage[]);

void guiCalibrateTool();

void guiGoHomeTool();

void guiSelectJogSpeedTool();

void guiSelectJointTool(int jointToSelect, char* toolName, unsigned char toolMessage[]);

//TESTING.
//void guiSelectDirectionTool(bool &directionToolHeld, char* toolName, unsigned char toolMessage[]);

void guiSelectDirectionTool(bool &directionToolHeld, char* toolName, ImGuiDir_ arrowType, unsigned char toolMessage[]);

void guiCreateFileTool();

void guiRecordPoseTool();

void guiPlaybackTool();

//Gripper Jog Tools
//+++++++++++++++++

void guiGripperMoveTool();

void guiGripperDirectionTool();

//Extruder Jog Tools
//++++++++++++++++++

void guiExtruderOnHotTool();

void guiExtruderOnColdTool();

void guiExtruderToggleTool();

void guiExtruderDirectionTool();

//Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiResetJogParameters();
