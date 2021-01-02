#include "ApplicationManager.h"
#include "CUT.h"



CutComp::CutComp(ApplicationManager *pApp, ActionType type) :Action(pApp, type)
{
}


CutComp::~CutComp()
{
}

void CutComp::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void CutComp::Execute()
{
	//Get a Pointer to the Output Interface
	Output* pOut = pManager->GetOutput();

	//Get the count of components selected
	int CountSelected = pManager->CountSelected();

	if (CountSelected == 1)
	{
		pOut->PrintMsg("Now you can paste the selected component");
		CompIndexFound = pManager->WhichCompSelected();
		NodePaste* CopiedCompNode = new NodePaste;
		CopiedCompNode->Comp = pManager->getCompList()[CompIndexFound[0]];
		CopiedCompNode->ActType = Act_Type;
		CopiedCompNode->CompIndex = CompIndexFound[0];
		pManager->getCopyCutIndex()->Push(CopiedCompNode);
	}
	else
	{
		return;
	}
}

void CutComp::Undo()
{
}

void CutComp::Redo()
{
}
