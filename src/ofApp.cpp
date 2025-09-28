// Copyright (C) 2017 - 2018 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//LIBRARIES
//=======================================================================================================================================

//openFrameworks Extensions
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "ofApp.h"

//GLOBAL VARIABLES & CONSTANTS
//=======================================================================================================================================

//General
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Graphical user interface (GUI)

ofxImGui::Gui SOFTWARE_GUI;

//Other
//All other variables and constants are defined and initalised in the relevant .h and .cpp files associated with this project.

//FUNCTIONS
//=======================================================================================================================================

//Setup Function
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ofApp::setup(){
//---------------------------------------------------------------------------------------------------------------------------------------
//cout << "...\n...Setup Start...\n..." << endl;

//cout << "...Setup GUI...\n" << endl;

FreeConsole();				 //Surpress the terminal/output window.

ofSetWindowTitle(windowTitle);

ofSetWindowShape(windowSizeX, windowSizeY);
//ofSetWindowPosition(windowPosX, windowPosY);

ofSetEscapeQuitsApp(false);		//Prevent the program from quitting automatically when "ESC" key is pressed.

loadLogo();

loadSymbols();

ofBackground(windowColour);	

SOFTWARE_GUI.setup();			//Setup ImGui GUI.

//ImGui::GetIO().MouseDrawCursor = false;	//Prevent ImGui from drawing it's own mouse cursor. Although this is already false by default?

//cout << "...Setup Serial Communications...\n" << endl;

scanDevices();

//cout << "...\n...Setup End...\n..." << endl;

} //End of void ofApp::setup()

//Update Function
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ofApp::update(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Not currently used.

} //End of void ofApp::update()

//Draw Function
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ofApp::draw(){
//---------------------------------------------------------------------------------------------------------------------------------------

SOFTWARE_GUI.begin();	//Begin ofxImGui GUI creation - required call at the start of draw().

//Uncomment the following to display the demo gui showing all ImGUi's capabilities.
//ImGui::ShowTestWindow();

//Uncomment this to interactively test new colour styles.
//However, generalGuiStyleSettings() at the start and end of the GUI must be commented out for this to work properly.
//ImGui::ShowStyleEditor();

//Uncomment the following to display a colour button where you can change the rgb colours.
//static float col1[3] = { 1.0f,0.0f,0.2f };
//ImGui::ColorEdit3("color 1", col1);	

//General GUI Style Settings - Start
//++++++++++++++++++++++++++++++++++

generalGuiStyleSettings(); //This pushes all the required style colours. This must be called again at the end of the GUI to pop the colours.

//Settings Menu
//+++++++++++++

settingsMenu();

//Connection Menu
//+++++++++++++++

connectionMenu();

//Mode Menu
//+++++++++

modeMenu();

//Logo Menu
//+++++++++

logoMenu();

//General GUI Style Settings - End
//++++++++++++++++++++++++++++++++

generalGuiStyleSettings(); //This pops all the style colours pushed at the start of the GUI.

SOFTWARE_GUI.end();		   //End ofxImGui GUI creation - required call at the end of draw().


displayLogo();			   //NOTE: This is called after the GUI ends so that it displays on top of the GUI windows.

displayAboutGraphics();	   //See above comments.

} //End of void ofApp::draw()

void ofApp::keyPressed(int key){
//---------------------------------------------------------------------------------------------------------------------------------------

//cout << "key pressed" << endl;
//cout << key << endl;

jogKeyboardInput(true, key);

/*
if(key == OF_KEY_ESC){
	//Add an escape button press action if required
	//NOTE: You must put "ofSetEscapeQuitsApp(false);" in setup 
	//to prevent the program from quitting automatically when escape is pressed
}
//*/

} //End of void ofApp::keyPressed(int key)

void ofApp::keyReleased(int key){
//---------------------------------------------------------------------------------------------------------------------------------------

jogKeyboardInput(false, key);

} //End of void ofApp::keyReleased(int key)

void ofApp::mouseMoved(int x, int y ){
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

void ofApp::gotMessage(ofMessage msg){
//---------------------------------------------------------------------------------------------------------------------------------------

}

void ofApp::dragEvent(ofDragInfo dragInfo){ 
//---------------------------------------------------------------------------------------------------------------------------------------

}

