// Copyright (C) 2017 - 2018 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//HEADER FILE
//=======================================================================================================================================

#include "ofMain.h"

//LIBRARIES
//=======================================================================================================================================

#include "ofApp.h"
#include "../resource.h"	//To do this, type #include "../ and use the auto-complete pop-up to select the file resource.h
							//If that doesn't work and you get the "can't open file error or expected a file name, remove the
							//file from the solution and re-add it.
							//If that still doesn't work, just close it down, restart, and repeat the above.

//FUNCTIONS
//=======================================================================================================================================

//Notes
//-----

//Use main() during development so you can see the console window, debug mode must be set; 
//Change the solution configuration in the option next to the "Local WIndows Debugger" to "Debug". The next part should have been done automtically
//by changing the configuration setting but if not it can be done like so;
//Right click on your app name in solution explorer, then choose Properties > Linker > System > Subsystem and set it to �Console (/SUBSYSTEM:CONSOLE)�

//Use WinMain for the final/release version to disable the console window, release mode must be set
//Change the solution configuration in the option next to the "Local WIndows Debugger" to "Release". The next part should have been done automtically
//by changing the configuration setting but if not it can be done like so;
//Right click on your app name in solution explorer, then choose Properties > Linker > System > Subsystem and set it to �Windows (/SUBSYSTEM:WINDOWS)�


//int main( ){	
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
//---------------------------------------------------------------------------------------------------------------------------------------
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	//This adds a custom icon. NOTE: Comment this when using debug mode.
	HWND hwnd = ofGetWin32Window();
	HICON hMyIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MAIN_ICON));		//MAIN_ICON is found in the resource.h file
	SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hMyIcon);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
