// Copyright (C) 2017 - 2018 Joseph Morgridge
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

//General
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Graphical user interface (GUI)

extern const string programName;

extern const string programVersion;

extern string windowTitle;

extern int windowSizeX;
extern int windowSizeY;

extern int windowPosX;
extern int windowPosY;

extern ofColor windowColour;

extern ImColor menuWindowTitleColour;
extern ImColor menuWindowColour;
extern ImColor menuWindowColour2;
extern ImColor toolbarColour;
extern ImColor toolColour;
extern ImColor toolColour2;

extern ImColor menuWindowTitleActiveColour;
extern ImColor toolbarActiveColour;
extern ImColor toolActiveColour;

extern ofImage copyrightSymbol;

//Serial messages

const int generalToolMessageSize = 5;	//For M-codes, J-codes and any other codes.
//extern const int generalToolMessageSize;
//**extern guidelines don't work for array size so this is initialised here**
//It just means that the value will be duplicated in each file that includes it.
//Since it is only an int data type, it shouldn't have a huge impact on memory.
//This should preferably not be done for strings or other potentially large data types.

extern const char deviceReadyMessage;

//Info pop-ups

extern const char* programBusyToolBarName;
extern const char* programBusyInfo;
extern bool currentModeBusy;
extern bool displayBusyPopup;

//Settings Menu Variables
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern const int NoTool;
extern const int Pen;
extern const int Gripper;
extern const int Extruder;
extern int toolSelected;

//Connection Menu Variables
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern ofSerial serial;

extern const char* pleaseConnectSerialInfo;

//Mode Menu Variables
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern int MODE_MENU;
extern const int Jog;
extern const int Gcode_Sender;

//Jog toolbar variables

//N/A

//G-code sender toolbar variables

extern ofBuffer inFileBuffer;
extern string inFilePath;
extern bool inFilePathLoaded;

extern string inFileInfo;

//Logo Menu Variables
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern ofImage companyLogo;
extern ofImage softwareLogo;
extern ofImage softwareIcon;

//FUNCTION PROTOTYPE DEFINITIONS
//=======================================================================================================================================

//General
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Graphical user interface (GUI)
//------------------------------

void generalGuiStyleSettings();

bool Combo(const char* label, int* currIndex, std::vector<std::string>& values);

void loadSymbols();

//Info pop-ups
//------------

void infoPopupToolBar(const char* toolBarName, const char* toolBarInfo, bool &displayPopupFlag);

//File system
//-----------

//Load existing file using system dialogue

void loadFileTool(string &inFileInfo, string &filePath, bool &filePathLoaded, ofBuffer &inFileBuffer, char* toolName, ImVec2 toolPos);

//Load existing file from known directory

void loadFile(string &inFileInfo, string &inFilePath, bool &filePathLoaded, ofBuffer &inFileBuffer, string &inFilePathSource);

//Create new file

bool createFileTool(string &outFileInfo, string &outFilePath, bool &outFilePathLoaded, char* toolName, ImVec2 toolPos);
