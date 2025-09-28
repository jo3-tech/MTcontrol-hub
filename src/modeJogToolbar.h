// Copyright (C) 2017 - 2018 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//PREPROCESSOR DIRECTIVES/INCLUDE GAURDS
//=======================================================================================================================================

#pragma once

//LIBRARIES
//=======================================================================================================================================

#include "common.h"

//FUNCTION PROTOTYPE DEFINITIONS
//=======================================================================================================================================

//Toolbar
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void jogToolbar();

//Tools
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Robot jog tools
//---------------

void jogKeyboardInput(bool keyPressed, int key);

void selectJointKeyboardInput(bool keyPressed, int jointToSelect, unsigned char toolMessage[]);

void selectDirectionKeyboardInput(bool keyPressed, bool &directionKeyHeld, unsigned char toolMessage[]);

void calibrateTool();

void selectJogSpeedTool();

void selectJointTool(int jointToSelect, char* toolName, ImVec2 toolPos, unsigned char toolMessage[]);

void selectDirectionTool(bool &directionToolHeld, char* toolName, ImVec2 toolPos, unsigned char toolMessage[]);

void recordPoseTool();

//Robot-tools jog tools
//---------------------

//Gripper

void gripperMoveTool();

void gripperDirectionTool();

//Extruder

void extruderOnHotTool();

void extruderOnColdTool();

void extruderToggleTool();

void extruderDirectionTool();

//Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void resetJogParameters();