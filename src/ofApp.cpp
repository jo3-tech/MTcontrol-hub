// Copyright (C) 2017 - 2020 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//LIBRARIES
//=======================================================================================================================================

//openFrameworks Extensions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "ofApp.h"

//FUNCTIONS
//=======================================================================================================================================

//Setup Function
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ofApp::setup(){
//---------------------------------------------------------------------------------------------------------------------------------------

//DEBUGGING.
//cout << "...\n...Setup Start...\n..." << endl;

ofSetFrameRate(0);

//TESTING.
//ofSetVerticalSync(false);
//ofGetWindowPtr()->setVerticalSync( false );

guiGeneralGuiSetup(); //General GUI Settings. 

guiGuiObject.setup(); //Setup GUI object.

guiGeneralGuiStyleSettings(); //Set up GUI colours and theme/style.

guiScanDevices();

//TESTING.
//guiLoadTestImages();
//cout << "output of testFunctionForNameSpace = " << endl;
//cout << testNameSpace::testFunctionForNameSpace() << endl;

//DEBUGGING.
//cout << "...\n...Setup End...\n..." << endl;

}

//Update Function
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ofApp::update(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Not currently used. May be used for robot functions if the robot controller is merged with this.

}

//Draw Function
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ofApp::draw(){
//---------------------------------------------------------------------------------------------------------------------------------------

guiGuiObject.begin(); //Begin GUI creation - required call at the start of draw().

//TESTING.
//Uncomment this to display the demo gui showing all ImGUi's capabilities.
//ImGui::ShowDemoWindow();

//TESTING.
//Uncomment this to interactively test new drawing and colour styles, fonts and scale factors, etc.
//ImGui::ShowStyleEditor();

//TESTING.
//Uncomment this to display a colour button where you can change the rgb colours.
//static float col1[3] = { 1.0f,0.0f,0.2f };
//ImGui::ColorEdit3("color 1", col1);	

//TESTING.
//Uncomment these for general GUI testing.
//guiTestingImgui();

guiGetGuiScaleFactor();

guiGetLogoMenuPos(); //Part of Logo Menu.

ImGui::SetNextWindowPos(ImVec2(guiSubWindowPosX, guiSubWindowPosY));

ImGui::SetNextWindowSize(ImVec2(guiSubWindowSizeX*guiScaleFactor, guiSubWindowSizeY*guiScaleFactor));

ImGuiWindowFlags guiMainWindowFlags = ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;

ImGui::Begin(guiSecondaryName, NULL, guiMainWindowFlags);

guiSettingsMenuBar();

guiConnectionMenu();

guiModeMenu();

ImGui::End();

//DEFERRED. guiInfoMenu.
//guiInfoMenu();

guiLogoMenu();

//DEBUGGING.
//cout << "guiCurrentModeBusy = " << endl;
//cout << guiCurrentModeBusy << endl;
//cout << "guiCurrentModeStillBusy = " << endl;
//cout << guiCurrentModeStillBusy << endl;

guiInfoPopupToolBar(guiProgramBusyToolBarName, guiProgramBusyInfo, guiDisplayBusyPopup);

guiGuiObject.end(); //End ofxImGui GUI creation - required call at the end of draw().

//NOTE
//----
//The following are called after the GUI ends so that it displays on top of the GUI windows.

guiDisplayLogo(); //Part of Logo Menu.

guiDisplayAboutGraphics(); //Part of Settings Menu.

}

//Other Functions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ofApp::keyPressed(int key){
//---------------------------------------------------------------------------------------------------------------------------------------

//DEBUGGING.
//cout << "key pressed" << endl;
//cout << key << endl;

guiJogKeyboardInput(true, key);

/*TESTING.
if(key == OF_KEY_ESC){
	//Add an escape button press action if required
	//NOTE: You must put "ofSetEscapeQuitsApp(false);" in setup 
	//to prevent the program from quitting automatically when escape is pressed
}
//*/

}

void ofApp::keyReleased(int key){
//---------------------------------------------------------------------------------------------------------------------------------------

guiJogKeyboardInput(false, key);

}

void ofApp::mouseMoved(int x, int y){
//---------------------------------------------------------------------------------------------------------------------------------------

}

void ofApp::mouseDragged(int x, int y, int button){
//---------------------------------------------------------------------------------------------------------------------------------------

}

void ofApp::mousePressed(int x, int y, int button){
//---------------------------------------------------------------------------------------------------------------------------------------

}

void ofApp::mouseReleased(int x, int y, int button){
//---------------------------------------------------------------------------------------------------------------------------------------

}

void ofApp::mouseEntered(int x, int y){
//---------------------------------------------------------------------------------------------------------------------------------------

}

void ofApp::mouseExited(int x, int y){
//---------------------------------------------------------------------------------------------------------------------------------------

}

void ofApp::windowResized(int w, int h){
//---------------------------------------------------------------------------------------------------------------------------------------

}

void ofApp::gotMessage(ofMessage msg) {
//---------------------------------------------------------------------------------------------------------------------------------------

}

void ofApp::dragEvent(ofDragInfo dragInfo){
//---------------------------------------------------------------------------------------------------------------------------------------

}
