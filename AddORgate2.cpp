#include "AddORgate2.h"
#include"ApplicationManager.h"
AddORgate2::AddORgate2(ApplicationManager *pApp, ActionType type) :Action(pApp,type)
{
}

AddORgate2::~AddORgate2(void)
{
}

void AddORgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();

	//Wait for User Input
	Ctype = pOut->getWindow()->WaitMouseClick(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddORgate2::Execute()
{
	//Get a Pointer to the Output Interface
	Output* pOut = pManager->GetOutput();

	//Print Action Message
	pOut->PrintMsg("2-Input OR Gate: Click to add the gate");

	//Get Center point of the Gate
	ReadActionParameters();

	//Cancel the action
	if (Ctype == RIGHT_CLICK)
	{
		return;
	}

	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	//Checking overlapping
	pManager->OverlappingComp(Cx, Cy);

	GraphicsInfo GInfo; //Gfx info to be used to construct the OR2 gate
	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;

	OR2 *pA = new OR2(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
	pManager->CreateAction(this);
	pManager->getUndoedActions()->EmptyStack();
}

void AddORgate2::Undo()
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

void AddORgate2::Redo()
{
	pManager->RedoComponent();
}

