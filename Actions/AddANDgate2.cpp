#include "AddANDgate2.h"
#include "..\ApplicationManager.h"

AddANDgate2::AddANDgate2(ApplicationManager *pApp,ActionType type) :Action(pApp,type)
{
}

AddANDgate2::~AddANDgate2(void)
{
}

void AddANDgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();

	//Wait for User Input
	Ctype = pOut->getWindow()->WaitMouseClick(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();
}

void AddANDgate2::Execute()
{
	//Get a Pointer to the Output Interface
	Output* pOut = pManager->GetOutput();

	pOut->ClearStatusBar(); //Added newly

	pOut->PrintMsg("2-Input AND Gate: Click to add the gate");
	
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

	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	

	AND2 *pA = new AND2(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
	pManager->CreateAction(this);
	pManager->getUndoedActions()->EmptyStack();
}

void AddANDgate2::Execute(GraphicsInfo GInfo)
{
	//Get a Pointer to the Output Interface
	Output* pOut = pManager->GetOutput();

	pOut->ClearStatusBar(); //Added newly

	pOut->PrintMsg("2-Input AND Gate: Click to add the gate");
	AND2 *pA = new AND2(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
}

void AddANDgate2::Undo()
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

void AddANDgate2::Redo()
{
	pManager->RedoComponent();
}


