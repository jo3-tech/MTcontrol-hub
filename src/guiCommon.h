// Copyright (C) 2017 - 2020 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//PREPROCESSOR DIRECTIVES/INCLUDE GAURDS
//=======================================================================================================================================

#pragma once

//LIBRARIES
//=======================================================================================================================================

#include "ofMain.h"
#include "ofxImGui.h"

//GLOBAL VARIABLES & CONSTANTS
//=======================================================================================================================================

//Program Version Information
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern const string guiProgramName;

extern const string guiProgramVersion;

extern const char* guiSecondaryName;

//Graphical User Interface (GUI)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//GUI Object
//++++++++++

extern ofxImGui::Gui guiGuiObject; //GUI object.

//Main Window
//+++++++++++

extern int guiWindowSizeX;
extern int guiWindowSizeY;

//Sub Window
//++++++++++

extern float guiSubWindowSizeX;
extern float guiSubWindowSizeY;

extern float guiSubWindowPosX;
extern float guiSubWindowPosY;

//Colours
//+++++++

extern ofColor guiToolbarColour;
extern ofColor guiToolbarActiveColour;
extern ofColor guiToolActiveColour;

//Graphics
//++++++++

extern ofImage guiCopyrightSymbol;

extern ofImage guiCompanyLogo;
extern ofImage guiSoftwareLogo;
extern ofImage guiSoftwareIcon;

//Scaling and Spacing
//+++++++++++++++++++

extern float guiScaleFactor;

extern const float guiMenuSpacingY;

//Control Flags/Indicator Variables
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//General
//+++++++

extern bool guiCurrentModeBusy;
extern bool guiCurrentModeStillBusy;
extern bool guiDisplayBusyPopup;

extern const char guiCancelActionMessage;

//Jog
//+++

extern bool guiReEntryIntoJog;

//G-Code Sender
//+++++++++++++

extern const char guiDeviceReadyMessage;

extern bool guiInFilePathLoaded;

//Info Menu
//+++++++++

extern bool guiVersionInfoObtained;

extern bool guiListenForRobotParameters;

//Serial Messages
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const int guiGeneralToolMessageSize = 5; //For M-codes, J-codes and any other codes.
//extern const int guiGeneralToolMessageSize;
//**extern guidelines don't work for array size so this is initialised here**
//It just means that the value will be duplicated in each file that includes it.
//Since it is only an int data type, it shouldn't have a huge impact on memory.
//This should preferably not be done for strings or other potentially large data types.

//Info Pop-Ups
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern const char* guiProgramBusyToolBarName;
extern const char* guiProgramBusyInfo;

//Settings Menu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern const int rbtNoTool;
extern const int rbtPen;
extern const int rbtGripper;
extern const int rbtExtruder;
extern int rbtToolSelected;

//Connection Menu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern ofSerial guiSerial;

//Mode Menu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern int guiModeMenuToolbarId;
extern const int guiJogToolbarId;
extern const int guiGcSenderToolbarId;

//G-code Sender Toolbar
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern ofBuffer guiInFileBuffer;
extern string guiInFilePath;

extern string guiInFileInfo;

//Info Menu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//DEFERRED. guiInfoMenu.
//extern unsigned char guiRequestRobotParametersMessage[guiGeneralToolMessageSize];

//FUNCTION PROTOTYPE DEFINITIONS
//=======================================================================================================================================

//Graphical User Interface (GUI)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiGeneralGuiSetup();

void guiGeneralGuiStyleSettings();

void guiLoadGraphics();

void guiGetGuiScaleFactor();

void guiGeneralGuiHorizontalSpacing(float spacing);

void guiGeneralGuiVerticalSpacing(float spacing);

void guiMenuHeaderTitle(const char* title, bool showSeparator);

bool guiCombo(const char* label, int* currIndex, std::vector<std::string>& values);

//Info pop-ups
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiInfoPopupToolBar(const char* toolBarName, const char* toolBarInfo, bool &displayPopupFlag);

//File system
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool guiCreateFileViaDialogue(char* defaultFileName, string &outFileInfo, string &outFilePath);

void guiLoadFile(string &inFileInfo, string &inFilePath, ofBuffer &inFileBuffer);

bool guiLoadFileViaDialogue(string &inFileInfo, string &inFilePath, ofBuffer &inFileBuffer);

//Serial
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiSerialFlush();

