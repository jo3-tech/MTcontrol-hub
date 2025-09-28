// Copyright (C) 2017 - 2020 Joseph Morgridge
//
// Licensed under GNU General Public License v3.0 (GPLv3) License.
// See the LICENSE file in the project root for full license details.

//HEADER FILE
//=======================================================================================================================================

#include "guiTesting.h"

//GLOBAL VARIABLES & CONSTANTS
//=======================================================================================================================================

string guiTestImage1FilePath = "logos/software logo.png";

GLuint guiTestImage1GlId;

ImTextureID guiTestImage1Id;


//FUNCTION IMPLEMENTATIONS
//=======================================================================================================================================

void guiLoadTestImages(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Load test images.

guiTestImage1GlId = guiGuiObject.loadTexture(guiTestImage1FilePath);

guiTestImage1Id = (ImTextureID)(uintptr_t)guiTestImage1GlId;
//OR
//guiTestImage1Id = (void*)(uintptr_t)guiTestImage1GlId;

}

void guiTestingImgui(){
//---------------------------------------------------------------------------------------------------------------------------------------

//Display test menu(s).
//Before testing anything, check if it is sufficiently demonstrated in the ImGui Demo by uncommenting ImGui::ShowDemoWindow();
//in the ofApp::draw() function.

/*
//ImGui::Begin("Test Menu 1", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
ImGui::Begin("Test Menu 1");

	ImGui::BeginChild("Test Child Window within tab bar");

		ImGui::BeginTabBar("Test Tabs", ImGuiTabBarFlags_rbtNoTooltip); 

		//NOTE: PLACING A CHILD WINDOWS WITHIN TAB BARS CAUSE DISPLAY ISSUES

			if(ImGui::BeginTabItem("Test Tab 1"))
			{
				//NOTE: YOU CAN'T PLACE CHILD WINDOWS WITHIN TAB ITEMS
				ImGui::Text("Test Tab 1 content here");
				if(ImGui::Button("Test button within tab 1")){ }

				ImGui::EndTabItem();
			}

			if(ImGui::BeginTabItem("Test Tab 2"))
			{
				ImGui::Text("Test Tab 2 content here");
				ImGui::EndTabItem();
			}		
	
		ImGui::EndTabBar();

	ImGui::EndChild(); //End of ImGui::BeginChild("Test Child Window within tab bar");

ImGui::End(); //End of ImGui::Begin("Test Menu 1");
//*/

//*
static bool radio1Active = false;

ImGui::Begin("Test Menu 2");

//ImGui::SetNextWindowSizeConstraints(ImVec2(200,15), ImVec2(1000,20));

	ImGui::BeginChild("Test Child Window");
	
	if(ImGui::ListBoxHeader("List", {150, 50}))
	{
		ImGui::Selectable("Test Selectable 1");
		//ImGui::NewLine();
		ImGui::Selectable("Test Selectable 2");
		//ImGui::NewLine();
		ImGui::ListBoxFooter();
	}	

	//NOTE: The ImGui developer doesn't like the "Columns" implementation and will likely replace it with a new "Tables" API in Q2 2020.
	ImGui::Columns(2);	//Start columns		//Column 1 row 1
	ImGui::Selectable("Test Selectable 3");	
	ImGui::NextColumn();					//Column 2 row 1
	ImGui::NextColumn();					//Column 1 row 2
	ImGui::Selectable("Test Selectable 4");	
	ImGui::NextColumn();					//Column 2 row 2
	ImGui::Selectable("Test Selectable 5");
	ImGui::Columns(1);	//End columns

	if(ImGui::RadioButton("Test Radio 1", radio1Active)){ radio1Active = !radio1Active; }

	ImGui::SameLine(0, 50);

	if(ImGui::RadioButton("Test Radio 1", radio1Active)){ radio1Active = !radio1Active; }

	ImGui::Selectable("Test Selectable 3", false, 0, {100, 0});

		ImGui::ArrowButton("Test Arrow", ImGuiDir_Left);

		ImGui::Image(guiTestImage1Id, ImVec2(100, 100));
		ImGui::ImageButton(guiTestImage1Id, ImVec2(100, 100));

		ImGui::ProgressBar(0.25);

		//ImGui::Spacing();
		//ImGui::Separator();
		//ImGui::SameLine(); ImGui::SameLine(0, 10);
		//ImGui::NewLine();	
		ImGui::NewLine();	

	ImGui::EndChild(); //End of ImGui::BeginChild("Test Child Window");

ImGui::End(); //End of ImGui::Begin("Test Menu 2");
//*/
}

namespace testNameSpace
{

int x = 5;

int testFunctionForNameSpace(){

return testNameSpace::x;

}

}