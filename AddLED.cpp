#include "AddLED.h"
#include"ApplicationManager.h"

AddLED::AddLED(ApplicationManager *pApp, ActionType type) :Action(pApp,type)
{
}

AddLED::~AddLED(void)
{
}

void AddLED::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();

	//Wait for User Input
	Ctype = pOut->getWindow()->WaitMouseClick(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddLED::Execute()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();

	//Print Action Message
	pOut->PrintMsg(" Click to add an LED");

	//Get Center point of the Gate
	ReadActionParameters();

	//Cancel the action
	if (Ctype == RIGHT_CLICK)
	{
		return;
	}

	//Calculate the rectangle Corners
	int Len = UI.LED_Width;
	int Wdth = UI.LED_Height;

	//Checking overlapping
	pManager->OverlappingComp(Cx, Cy);

	GraphicsInfo GInfo; //Gfx info to be used to construct the LED 
	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;

	LED *pA = new LED(GInfo);
	pManager->AddComponent(pA);
	pManager->CreateAction(this);
	pManager->getUndoedActions()->EmptyStack();
}

void AddLED::Undo()
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

void AddLED::Redo()
{
	pManager->RedoComponent();
}

