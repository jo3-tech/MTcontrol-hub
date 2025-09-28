// Copyright (C) 2017 - 2018 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//HEADER FILE
//=======================================================================================================================================

#include "common.h"

//GLOBAL VARIABLES & CONSTANTS
//=======================================================================================================================================

//General
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Graphical user interface (GUI)

const string programName = "ncHub ";

const string programVersion = "0.0.0 ";

string windowTitle = programName + programVersion;

int windowSizeX = 780;
int windowSizeY = 670;

int windowPosX = 10;
int windowPosY = 10;

ofColor windowColour(50); //Grey.
//ofColor windowColour(255,255,255); 

ImColor menuWindowTitleColour = {51, 56, 68, 255}; //Common variable defintion. Grey, translucent.
ImColor menuWindowColour = {0, 0, 0, 179};         //Common variable defintion. Black, translucent.
ImColor menuWindowColour2 = {51, 56, 68, 148};     //Common variable defintion. Grey, translucent.
ImColor toolbarColour = {119, 196, 211, 100};	   //Common variable defintion. Grey, translucent.
ImColor toolColour = {119, 196, 211, 100};	       //Common variable defintion. Grey, translucent.
ImColor toolColour2 = {0, 0, 0, 100};		       //Common variable defintion. Black, translucent.

ImColor menuWindowTitleActiveColour = {209, 0, 0, 199}; //Common variable defintion. Red, translucent.
ImColor toolbarActiveColour = {209, 0, 0, 199};    //Common variable defintion. Red, translucent.
ImColor toolActiveColour = {209, 0, 0, 199};	   //Common variable defintion. Red, translucent.

ofImage copyrightSymbol;	//Common variable defintion. 
string copyrightSymbolFilePath = "symbols/copyright symbol.png";

//Serial messages

//const int generalToolMessageSize = 5;	//Common variable defintion. For M-codes, J-codes and any other codes.
//**extern guidelines don't work for array size so this is initialised in the header file**
//See notes in header file for more info.

const char deviceReadyMessage = '>';

//Info pop-ups

const char* programBusyToolBarName = "Program Busy";
const char* programBusyInfo = "Please stop the current operation \nOR wait for it to complete.\nClick anywhere to close popup.";
bool currentModeBusy = false;
bool displayBusyPopup = false;

//FUNCTION IMPLEMENTATIONS
//=======================================================================================================================================

//General
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Graphical user interface (GUI)
//------------------------------

void generalGuiStyleSettings(){
//---------------------------------------------------------------------------------------------------------------------------------------

//NOTE: THIS FUNCTION MUST BE PLACED JUST AFTER SOFTWARE_GUI.start() AND JUST BEFORE SOFTWARE_GUI.end();

static bool pushed = false;
static int styleColourCount = 0;

if(pushed == false)
{
	//NOTE: Other colours can be changed but there is currently no intention to change the defaults.
	//See enum ImGuiCol_ in imgui.h for options.

	ImGui::PushStyleColor(ImGuiCol_TitleBg, menuWindowTitleColour);				styleColourCount++;
	ImGui::PushStyleColor(ImGuiCol_WindowBg, menuWindowColour);					styleColourCount++;
	ImGui::PushStyleColor(ImGuiCol_PopupBg, menuWindowColour);					styleColourCount++;
	ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, menuWindowColour2);			styleColourCount++;
	//Note: toolbar colours are changed at the point of calling the toolbar since I've used buttons for toolbars.
	ImGui::PushStyleColor(ImGuiCol_Button, toolColour);							styleColourCount++;
	ImGui::PushStyleColor(ImGuiCol_SliderGrab, toolColour);						styleColourCount++;		//Slider handle
	ImGui::PushStyleColor(ImGuiCol_FrameBg, toolColour2);						styleColourCount++;		//Checkox, radio button, plot, slider, text input.

	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, menuWindowTitleActiveColour);	styleColourCount++;
	//Note: toolbar active colours are changed at the point of calling the toolbar since I've used buttons for toolbars.
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, toolActiveColour);			styleColourCount++;
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, toolActiveColour);				styleColourCount++;
	//Note: The above button active is for when the button is clicked, since there is no option for when the button is selected,
	//this is done at the point of calling the tool.
	ImGui::PushStyleColor(ImGuiCol_Header, toolActiveColour);					styleColourCount++;		//Menu bar items
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, toolActiveColour);			styleColourCount++;
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, toolActiveColour);				styleColourCount++;
	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, toolActiveColour);			styleColourCount++;
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, toolActiveColour);			styleColourCount++;
	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, toolActiveColour);			styleColourCount++;
	ImGui::PushStyleColor(ImGuiCol_CheckMark, toolActiveColour);				styleColourCount++;		//Check mark
	ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabHovered, toolActiveColour);		styleColourCount++;		//Scroll handle
	ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabActive, toolActiveColour);		styleColourCount++;

	pushed = true;

}
else
{
	ImGui::PopStyleColor(styleColourCount);

	styleColourCount = 0;

	pushed = false;

}

} //End of void generalGuiStyleSettings()

static auto vector_getter = [](void* vec, int idx, const char** out_text){
//---------------------------------------------------------------------------------------------------------------------------------------
auto& vector = *static_cast<std::vector<std::string>*>(vec);
if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
*out_text = vector.at(idx).c_str();
return true;

};

bool Combo(const char* label, int* currIndex, std::vector<std::string>& values){
//---------------------------------------------------------------------------------------------------------------------------------------
//If we use a string for the values instead, we wont even need this function
//or the vector_getter but we will need a function to decode the "\0" separated
//string in order to retrieve the item which was pressed via the item index.
if (values.empty()) { return false; }
return ImGui::Combo(label, currIndex, vector_getter,
    static_cast<void*>(&values), values.size());
} //End of bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)

void loadSymbols(){
//---------------------------------------------------------------------------------------------------------------------------------------

copyrightSymbol.load(copyrightSymbolFilePath);

} //End of void loadSymbols()

//Info pop-ups
//------------

void infoPopupToolBar(const char* toolBarName, const char* toolBarInfo, bool &displayPopupFlag){
//---------------------------------------------------------------------------------------------------------------------------------------

//NOTE: This must be implemented exactly as it is below otherwise it doesn't behave properly.
//Placement of this function within the program is also important. It shouldn't be placed within
//more than 1 or 2 if-statements and definitely not within the if-statment for a button or within
//a menu bar or it won't work.. even if you remove the "if(displayPopupFlag == true)" from here.

if(displayPopupFlag == true)
{
	ImGui::OpenPopup(toolBarName);
}

//if(ImGui::BeginPopup(toolBarName))
if(ImGui::BeginPopupModal(toolBarName, NULL, ImGuiWindowFlags_AlwaysAutoResize))
{
	ImGui::Text(toolBarInfo);

	//if (ImGui::Button("Close")){ ImGui::CloseCurrentPopup(); }

	if(ImGui::IsMouseClicked(0)){ ImGui::CloseCurrentPopup(); }

	displayPopupFlag = false;

	ImGui::EndPopup();
}

} //End of void infoPopupToolBar(const char* toolBarName, const char* toolBarInfo, bool &displayPopupFlag)

//File system
//-----------

void loadFileTool(string &inFileInfo, string &inFilePath, bool &filePathLoaded, ofBuffer &inFileBuffer, char* toolName, ImVec2 toolPos){
//---------------------------------------------------------------------------------------------------------------------------------------
//Load a file from a directory via a system dialogue

//*
ImGui::SetCursorPos(toolPos);
if(ImGui::Button(toolName))
{
	ofFileDialogResult result = ofSystemLoadDialog("Load File");
	if(result.bSuccess)
	{
		inFilePath = result.getPath();
		inFileBuffer = ofBufferFromFile(inFilePath); //Create ofBuffer from file.
		if(inFileBuffer.size() == 0)
		{
			inFileInfo = "File empty, invalid, or corrupted.";
			inFileBuffer.clear();
			filePathLoaded = false;
		}
		else
		{
			inFileInfo = inFilePath.substr(inFilePath.find_last_of("\\/") + 1 );	//Get the file name from the file path.
			filePathLoaded = true;
		}
	}
}//End of if(ImGui::Button(toolName))

//*/

} //End of void loadFileTool(string &inFileInfo, string &inFilePath, bool &filePathLoaded, ofBuffer &inFileBuffer, char* toolName, ImVec2 toolPos)

void loadFile(string &inFileInfo, string &inFilePath, bool &filePathLoaded, ofBuffer &inFileBuffer, string &inFilePathSource){
//---------------------------------------------------------------------------------------------------------------------------------------
//Load a file from a known directory/source

//*
inFilePath = inFilePathSource;
inFileBuffer = ofBufferFromFile(inFilePath); //Create ofBuffer from file.
if(inFileBuffer.size() == 0)
{
	inFileInfo = "File empty, invalid, or corrupted.";
	inFileBuffer.clear();
	filePathLoaded = false;
}
else
{
	inFileInfo = inFilePath.substr(inFilePath.find_last_of("\\/") + 1 );	//Get the file name from the file path.
	filePathLoaded = true;
}

//*/

} //End of void loadFile(string &inFileInfo, string &inFilePath, bool &filePathLoaded, ofBuffer &inFileBuffer, string &inFilePathSource)

bool createFileTool(string &outFileInfo, string &outFilePath, bool &outFilePathLoaded, char* toolName, ImVec2 toolPos){
//---------------------------------------------------------------------------------------------------------------------------------------
//*
ImGui::SetCursorPos(toolPos);
if(ImGui::Button(toolName))
{
	ofFileDialogResult result = ofSystemSaveDialog("Record.txt","Create File");
	if(result.bSuccess)
	{
		outFilePath = result.getPath();
		if(ofFile::doesFileExist(outFilePath) == false)
		{
			outFilePath = result.getPath() + ".txt";
			ofFile outFile(outFilePath, ofFile::WriteOnly); //Create the file at the user selected path.
		}
		outFileInfo = outFilePath.substr(outFilePath.find_last_of("\\/") + 1 );	//Get the file name from the file path.
		outFilePathLoaded = true;

		//outFileBuffer = ofBufferFromFile(outFilePath); //Create ofBuffer from file. This will allow continued recording from the end of a previously recorded file.
		//NOT INCLUDING THIS FUNCTIONALITY FOR NOW... THIS CAN BE DONE MANUALLY BY SIMPLY COMBINING THE DATA FROM TWO RECORDED FILES.
		
		return true; //Indicate file was created successfully.
	}

}//End of if(ImGui::Button(toolName))

return false;

//*/

} //End of bool createFileTool(string &outFileInfo, string &outFilePath, bool &outFilePathLoaded, char* toolName, ImVec2 toolPos)

