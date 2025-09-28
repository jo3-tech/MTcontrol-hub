// Copyright (C) 2017 - 2020 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//HEADER FILE
//=======================================================================================================================================

#include "guiCommon.h"

//GLOBAL VARIABLES & CONSTANTS
//=======================================================================================================================================

//Program Version Information
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const string guiProgramName = "MTcontrol-hub ";

const string guiProgramVersion = "0.1.0 ";

const char* guiSecondaryName = "MTcontrol-hub ";

//General Graphical User Interface (GUI)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//GUI Object
//++++++++++

ofxImGui::Gui guiGuiObject; //GUI object.

//Main Window
//+++++++++++

string guiWindowTitle = guiProgramName + guiProgramVersion;

int guiWindowSizeX = 585;
int guiWindowSizeY = 590;

int guiWindowPosX = 10;
int guiWindowPosY = 10;

//Sub Window
//++++++++++

float guiSubWindowSizeX = 42;   //*guiScaleFactor.
float guiSubWindowSizeY = 38.2; // "

float guiSubWindowPosX = 20;
float guiSubWindowPosY = 20;

//Colours
//+++++++

ofColor guiWindowColour(50); //Grey.

//TESTING.
//ofColor guiWindowColour(175,10,10); 

ofColor guiMenuWindowTitleColour = { 50, 55, 70, 255 }; //Grey, opaque.
ofColor guiMenuWindowColour = { 0, 0, 0, 255 };		 //Black opaque.
ofColor guiMenuWindowColour2 = {35, 40, 45, 255 };		 //Grey, opaque.
ofColor guiToolbarColour = { 60, 90, 100, 255 };		 //Grey, opaque.
ofColor guiToolColour = { 60, 90, 100, 255 };			 //Grey, opaque.
ofColor guiToolColour2 = {35, 40, 45, 255 };		     //Grey, opaque.

ofColor guiMenuWindowTitleActiveColour = {175, 10, 10, 255 }; //Red, opaque.
ofColor guiToolbarActiveColour = {175, 10, 10, 255 };		   //Red, opaque.
ofColor guiToolActiveColour = {175, 10, 10, 255 };			   //Red, opaque.

ofColor guiMenuHeaderTextColour = {255, 10, 10, 255};		   //Red, opaque.

//Window/Drawing Styles
//+++++++++++++++++++++

float guiMenuWindowCornerRadius = 6.0;
float guiToolCornerRadius = 2.0;
ImVec2 guiMenuWindowMinSize = {1, 1}; //Minium size of menu windows - Note; setting this to 0 will cause en error.

//Graphics
//++++++++

ofImage guiCopyrightSymbol;	
string guiCopyrightSymbolFilePath = "symbols/copyright symbol.png";

ofImage guiCompanyLogo;
string guiCompanyLogoFilePath = "logos/company logo.png";

ofImage guiSoftwareLogo;
string guiSoftwareLogoFilePath = "logos/software logo.png";

ofImage guiSoftwareIcon;
string guiSoftwareIconFilePath = "logos/software icon.png";

//Scaling and Spacing
//+++++++++++++++++++

float guiScaleFactor = 13.0; //Scale factor for specifying sizes and spacing. 
							 //This will be updated within the program to use the size (height in pixels) of the font. 
							 //(Default font size was 13 during development with version 1.75 of ImGui.) 

const float guiMenuSpacingY = 0.2; //*guiScaleFactor.

//Control Flags/Indicator Variables
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//General
//+++++++

bool guiCurrentModeBusy = false;	  //Most widely used busy state - for any active action that wants to prevent other actions from occurring. 
bool guiCurrentModeStillBusy = false; //Mainly used when an active action allows other actions to occur but still wants to prevent the window from changing.
bool guiDisplayBusyPopup = false;

const char guiCancelActionMessage = '{';

//Jog
//+++

bool guiReEntryIntoJog = false;

//G-Code Sender
//+++++++++++++

const char guiDeviceReadyMessage = '>';

bool guiInFilePathLoaded = false;

//Info Menu
//+++++++++

bool guiVersionInfoObtained = false;

bool guiListenForRobotParameters = false;

//Serial Messages
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//const int guiGeneralToolMessageSize = 5;	//Common variable defintion. For M-codes, J-codes and any other codes.
//**extern guidelines don't work for array size so this is initialised in the header file**
//See notes in header file for more info.

//Info Pop-Ups
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const char* guiProgramBusyToolBarName = "Program Busy";

const char* guiProgramBusyInfo = "Please stop the current operation \nOR wait for it to complete.\nClick anywhere to close popup.";

//Settings Menu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const int rbtNoTool = 0;
const int rbtPen = 1;
const int rbtGripper = 2;
const int rbtExtruder = 3;
int rbtToolSelected = rbtNoTool;

//Connection Menu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

ofSerial guiSerial; //serial object.

//Mode Menu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int guiModeMenuToolbarId = 1;
const int guiJogToolbarId = 1;
const int guiGcSenderToolbarId = 2;

//G-code Sender Toolbar
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

ofBuffer guiInFileBuffer; //Buffer to store input file data.
string guiInFilePath;

string guiInFileInfo = "No file loaded.";

//Info Menu
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//DEFERRED. guiInfoMenu.
//unsigned char guiRequestRobotParametersMessage[guiGeneralToolMessageSize] = {'M', '4', '0', '8', '\n'};

//FUNCTION IMPLEMENTATIONS
//=======================================================================================================================================

//General Graphical User Interface (GUI)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiGeneralGuiSetup(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Set general GUI settings.

//FreeConsole(); //Surpress the terminal/output window.

ofSetWindowTitle(guiWindowTitle);

ofSetWindowShape(guiWindowSizeX, guiWindowSizeY);

//TESTING.
//ofSetWindowPosition(guiWindowPosX, guiWindowPosY);

ofSetEscapeQuitsApp(false);	//Prevent the program from quitting automatically when "ESC" key is pressed.

guiLoadGraphics();

}

void guiGeneralGuiStyleSettings(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Set general GUI colours and "theme"/"style".

//Main window colour
//------------------

ofBackground(guiWindowColour);

ImGuiStyle& guiStyle = ImGui::GetStyle(); //Get the default style settings.

//General colours
//---------------

//NOTE: Other colours can be changed but there is currently no intention to change the defaults.
//See struct ImGuiStyle and enum ImGuiCol_ in imgui.h for options.
	
guiStyle.Colors[ImGuiCol_TitleBg] = guiMenuWindowTitleColour; //Menu items.
guiStyle.Colors[ImGuiCol_WindowBg] = guiMenuWindowColour;
guiStyle.Colors[ImGuiCol_PopupBg] =	guiMenuWindowColour;
guiStyle.Colors[ImGuiCol_ChildBg] =	guiMenuWindowColour2;
//Note: toolbar colours are changed at the point of calling the toolbar since I've used buttons for toolbars.
guiStyle.Colors[ImGuiCol_Button] = guiToolColour;
guiStyle.Colors[ImGuiCol_SliderGrab] = guiToolColour; //Slider handle.
guiStyle.Colors[ImGuiCol_FrameBg] = guiToolColour2; //Background of checkox, radio button, plot, slider, text input.

guiStyle.Colors[ImGuiCol_TitleBgActive] = guiMenuWindowTitleActiveColour;	
//Note: toolbar active colours are changed at the point of calling the toolbar since I've used buttons for toolbars,
//and there is no "latch" for buttons hence not built in option like "ImGuiCol_buttonActive".
guiStyle.Colors[ImGuiCol_ButtonHovered] = guiToolActiveColour;			
guiStyle.Colors[ImGuiCol_ButtonActive] = guiToolActiveColour;				
//Note: The above button active is for when the button is clicked, since there is no option for when the button is
//selected/latched, hence this is done at the point of calling the tool.
guiStyle.Colors[ImGuiCol_Header] = guiToolbarActiveColour; //Menu bar items.
guiStyle.Colors[ImGuiCol_HeaderHovered] = guiToolbarActiveColour;	
guiStyle.Colors[ImGuiCol_HeaderActive] = guiToolbarActiveColour;				
guiStyle.Colors[ImGuiCol_SliderGrabActive] = guiToolActiveColour;			
guiStyle.Colors[ImGuiCol_FrameBgHovered] = guiToolActiveColour;		
guiStyle.Colors[ImGuiCol_FrameBgActive] = guiToolColour2;
guiStyle.Colors[ImGuiCol_CheckMark] = guiToolActiveColour; //Check mark.
guiStyle.Colors[ImGuiCol_ScrollbarGrabHovered] = guiToolActiveColour; //Scroll handle.
guiStyle.Colors[ImGuiCol_ScrollbarGrabActive] = guiToolActiveColour;		

guiStyle.Colors[ImGuiCol_Separator] = guiMenuWindowTitleActiveColour;

//Window/drawing Styles
//---------------------

//NOTE: Other window styles are change using ImGuiWindowFlags_, etc. when displaying the window.
//See struct ImGuiStyle and enum ImGuiStyleVar_ in imgui.h for options.

guiStyle.WindowRounding = guiMenuWindowCornerRadius;
guiStyle.WindowMinSize = guiMenuWindowMinSize;
guiStyle.FrameRounding = guiToolCornerRadius;
guiStyle.GrabRounding = guiToolCornerRadius;

//TESTING.
//guiStyle.WindowPadding = {0, 0};
//guiStyle.ItemSpacing = {0, 0};
//guiStyle.ItemInnerSpacing = {0, 0};
//guiStyle.FrameBorderSize = 0;
//guiStyle.FramePadding = {0, 0};
//guiStyle.WindowBorderSize = 1.0;
//guiStyle.ChildBorderSize = 0;

//Other
//-----

//TESTING.
//ImGui::GetIO().MouseDrawCursor = false; //Prevent ImGui from drawing it's own mouse cursor. This is already false by default?

} //End of void guiGeneralGuiStyleSettings()

void guiLoadGraphics(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Load GUI symbols and logos/icons.

guiCopyrightSymbol.load(guiCopyrightSymbolFilePath);

guiCompanyLogo.load(guiCompanyLogoFilePath);
guiSoftwareLogo.load(guiSoftwareLogoFilePath);
guiSoftwareIcon.load(guiSoftwareIconFilePath);

}

void guiGetGuiScaleFactor(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Get GUI scale factor.

guiScaleFactor = ImGui::GetFontSize(); //Current default = 13.

//**Notes on scaling.**
//If scaling is to be applied for say a mobile phone app for example, then ideally the font size will be changed according to say
//the window size (use ofGetWindowHeight() or ofGetWindowWidth() or ofGetWindowSize() NOT ImGui::GetWindowSize).
//Since the values in the program are already scaled according to the font size they will also scale accordingly.
//According to ImGui demo
//"the _correct_ way of scaling your UI is currently to reload your font at the designed size, rebuild the font atlas (ImFontAtlas), 
//and call style.ScaleAllSizes() on a reference ImGuiStyle structure."

//DEBUGGING.
//cout << "Font size (height in pixels) = " << ImGui::GetFontSize() << endl;

}

void guiGeneralGuiHorizontalSpacing(float spacing){
//---------------------------------------------------------------------------------------------------------------------------------------

//Create horizontal space in the GUI.
//This is used for vertical spacing as there is no ImGui function for this spacing similar to ImGui::Sameline(float spacing_in_pixels) 
//for horizontal spacing.

//TESTING.
//ImGui::SameLine();
//ImGui::Dummy(ImVec2(spacing, 0.0)); //This works with the exception that the ImGui::Sameline() function adds a little space before and after.
//ImGui::SameLine();

ImGui::SameLine(0, spacing*guiScaleFactor);

}

void guiGeneralGuiVerticalSpacing(float spacing){
//---------------------------------------------------------------------------------------------------------------------------------------

//Create vertical space in the GUI.
//This is used for vertical spacing as there is no ImGui function for this spacing similar to ImGui::Sameline(float spacing_in_pixels) 
//for horizontal spacing.

//TESTING.
//for(int i = 1; i <= spacing; i++){ ImGui::Spacing(); } //Spacing() function doesn't give an option to set the spacing amount.

//By default the next item is drawn on a new line so no need to force it here.
ImGui::Dummy(ImVec2(0.0, spacing*guiScaleFactor));

//TESTING.
//ImGui::Dummy(ImVec2(0.0, 0.0)); //This forces a new line with 0 spacing.

//TESTING.
//ImGui::NewLine(); //This forces a new line but appears to have an unknown default vertical spacing.

ImGui::Spacing(); //This forces a new line with 0 spacing. If this changes in future, the dummy option above can be used.

}

void guiMenuHeaderTitle(const char* title, bool showSeparator){
//---------------------------------------------------------------------------------------------------------------------------------------

//Create menu header title.

ImGui::TextColored(guiMenuHeaderTextColour, title);
if(showSeparator == true){ ImGui::Separator(); }

}

static auto guiVectorGetter = [](void* vec, int idx, const char** out_text){
//---------------------------------------------------------------------------------------------------------------------------------------

//Get item in combo/drop down tool.
	
auto& vector = *static_cast<std::vector<std::string>*>(vec);
if(idx < 0 || idx >= static_cast<int>(vector.size())){ return false; }
*out_text = vector.at(idx).c_str();
return true;

};

bool guiCombo(const char* label, int* currIndex, std::vector<std::string>& values){
//---------------------------------------------------------------------------------------------------------------------------------------

//Create combo/drop down tool.

//**If we use a string for the values instead, we wont even need this function or the guiVectorGetter but we will need a function to 
//decode the "\0" separated string in order to retrieve the item which was pressed via the item index.**

if(values.empty()){ return false; }

return ImGui::Combo(label, currIndex, guiVectorGetter, static_cast<void*>(&values), values.size());

}

//Info Pop-Ups
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiInfoPopupToolBar(const char* toolBarName, const char* toolBarInfo, bool &displayPopupFlag){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display information pop-up toolbar.
//This must be implemented exactly as it is below otherwise it doesn't behave properly. Placement of this function within the 
//program is also important. It shouldn't be placed within more than 1 or 2 if-statements and definitely not within the if-statment 
//for a button or within a menu bar or it won't work.. even if you remove the "if(displayPopupFlag == true)" from here.

if(displayPopupFlag == true)
{
	ImGui::OpenPopup(toolBarName); //Open the popup.
}

if(ImGui::BeginPopupModal(toolBarName, NULL, ImGuiWindowFlags_AlwaysAutoResize)) //Start writing to the popup only if it has been opened.
{
	//TESTING.
	//cout << "I'm popping up" << endl;

	ImGui::Text(toolBarInfo);

	displayPopupFlag = false;

	//TESTING.
	//if(ImGui::Button("Close")){ ImGui::CloseCurrentPopup(); }

	if(ImGui::IsMouseClicked(0)){ ImGui::CloseCurrentPopup(); }

	ImGui::EndPopup(); //This must be placed here as it must only be called if BeginPopUpModal(...) returned true.
}

}

//File system
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool guiCreateFileViaDialogue(char* defaultOutFileInfo, string &outFileInfo, string &outFilePath){
//---------------------------------------------------------------------------------------------------------------------------------------

//Create file using system dialogue.

ofFileDialogResult result = ofSystemSaveDialog(defaultOutFileInfo, "Create File");
	
if(result.bSuccess)
{
	outFilePath = result.getPath();
	if(ofFile::doesFileExist(outFilePath) == false)
	{
		outFilePath = result.getPath() + ".txt";
		ofFile outFile(outFilePath, ofFile::WriteOnly); //Create the file at the user selected path.
	}
	outFileInfo = outFilePath.substr(outFilePath.find_last_of("\\/") + 1); //Get the file name from the file path.

	return true; //Indicate file was created successfully.
}

return false;

} //End of bool guiCreateFileViaDialogue(string &outFileInfo, string &outFilePath, bool &guiOutFilePathLoaded, char* toolName, ImVec2 toolPos)

void guiLoadFile(string &inFileInfo, string &inFilePath, ofBuffer &inFileBuffer){
//---------------------------------------------------------------------------------------------------------------------------------------

//Load a file from a known directory/source.

inFileBuffer = ofBufferFromFile(inFilePath); //Create ofBuffer from file.

if(inFileBuffer.size() == 0)
{
	inFileInfo = "File empty, invalid, or corrupted.";
	inFileBuffer.clear();
}
else
{
	inFileInfo = inFilePath.substr(inFilePath.find_last_of("\\/") + 1);	//Get the file name from the file path.
}

}

bool guiLoadFileViaDialogue(string &inFileInfo, string &inFilePath, ofBuffer &inFileBuffer){
//---------------------------------------------------------------------------------------------------------------------------------------

//Load a file using system dialogue.

	ofFileDialogResult result = ofSystemLoadDialog("Load File");
	
	if(result.bSuccess)
	{
		inFilePath = result.getPath();

		guiLoadFile(inFileInfo, inFilePath, inFileBuffer);

		return true; //Indicate file was loaded successfully.
	}

return false;

}
 
//Serial
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void guiSerialFlush(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Discard all current incoming serial communications wait until finished.

while(guiSerial.available() > 0)
{
  char c = guiSerial.readByte(); //Read a character/byte of data.
}

}
