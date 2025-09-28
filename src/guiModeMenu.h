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
#include "guiModeJogToolbar.h"
#include "guiModeGcSenderToolbar.h"

//FUNCTION PROTOTYPE DEFINITIONS
//=======================================================================================================================================

//Menu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiModeMenu();

//Toolbar Tabs
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiModeMenuToolbarTab(const int toolbarId, const char* toolbarName);

//Toolbars, Tool and Tool Actions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//See header and cpp files for each mode i.e. modeXyz.h, modeXyz.cpp
//Where Xyz is the name of the mode e.g. Jog, GcSender, etc.
