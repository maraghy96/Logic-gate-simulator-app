#include "AddSwitch.h"
#include"ApplicationManager.h"

AddSwitch::AddSwitch(ApplicationManager *pApp, ActionType type) :Action(pApp,type)
{
}

AddSwitch::~AddSwitch(void)
{
}

void AddSwitch::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();

	//Wait for User Input
	Ctype = pOut->getWindow()->WaitMouseClick(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddSwitch::Execute()
{
	//Get a Pointer to the Output Interface
	Output* pOut = pManager->GetOutput();

	//Print Action Message
	pOut->PrintMsg(" Click to add a switch");

	//Get Center point of the Gate
	ReadActionParameters();

	//Cancel the action
	if (Ctype == RIGHT_CLICK)
	{
		return;
	}

	//Calculate the rectangle Corners
	int Len = UI.SWITCH_Width;
	int Wdth = UI.SWITCH_Height;

	//Checking overlapping
	pManager->OverlappingComp(Cx, Cy);

	GraphicsInfo GInfo; //Gfx info to be used to construct the Switch
	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;

	SWITCH *pA = new SWITCH(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
	pManager->CreateAction(this);
	pManager->getUndoedActions()->EmptyStack();
}

void AddSwitch::Undo()
{
	//Get a Pointer to the Output Interface
	Output* pOut = pManager->GetOutput();

	//Getting location of the gate
	GraphicsInfo GInfo = pManager->getCompList()[pManager->getCompCount() - 1]->getGfxInfo();

	//Erasing the gate
	pOut->ClearComponent(GInfo);

	//Remove the component from the components list
	pManager->DeleteComponent();
}

void AddSwitch::Redo()
{
	pManager->RedoComponent();
}

