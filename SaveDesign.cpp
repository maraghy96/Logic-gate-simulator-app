#include "SaveDesign.h"
#include "ApplicationManager.h"


SaveDesign::SaveDesign(ApplicationManager *pApp, ActionType type):Action(pApp,type)
{
}


SaveDesign::~SaveDesign()
{
}

void SaveDesign::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Save Design");

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void SaveDesign::Execute()
{
	ofstream Output_F;
	ReadActionParameters();
	Output_F.open("Design.txt", ios::out);
	pManager->Save(Output_F);
}

void SaveDesign::Undo() {

}

void SaveDesign::Redo() {

}
