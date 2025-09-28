// Copyright (C) 2017 - 2020 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//HEADER FILE
//=======================================================================================================================================

#include "ofMain.h"

//LIBRARIES
//=======================================================================================================================================

#include "ofApp.h"

//FUNCTIONS
//=======================================================================================================================================

int main(){
//---------------------------------------------------------------------------------------------------------------------------------------

//This kicks off the running of my app.	Can be OF_WINDOW or OF_FULLSCREEN.

//TESTING.
//ofSetupOpenGL(guiWindowSizeX, guiWindowSizeY, OF_WINDOW); //Setup the GL context - old method?

ofGLFWWindowSettings guiSettings;

//TESTING.
//guiSettings.setSize(guiWindowSizeX, guiWindowSizeY); //The ofSetWindowShape(...) method takes priority.

guiSettings.resizable = false;

ofCreateWindow(guiSettings); //New method.

ofRunApp(new ofApp());

}
