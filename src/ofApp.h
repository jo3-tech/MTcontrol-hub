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

#include "guiCommon.h"
#include "guiSettingsMenu.h"
#include "guiConnectionMenu.h"
#include "guiModeMenu.h"
#include "guiInfoMenu.h"
#include "guiLogoMenu.h"
#include "guiTesting.h"

//CLASSES
//=======================================================================================================================================

class ofApp : public ofBaseApp{
//---------------------------------------------------------------------------------------------------------------------------------------

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
