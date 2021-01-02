#include "COPY.h"
#include "ApplicationManager.h"



CopyComp::CopyComp(ApplicationManager *pApp, ActionType type) :Action(pApp, type)
{
}


CopyComp::~CopyComp()
{
}

void CopyComp::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void CopyComp::Execute()
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
		CopiedCompNode->Comp = pManager->getCompList()[CompIndexFound[0]]->Copy();
		CopiedCompNode->ActType = Act_Type;
		pManager->getCopyCutIndex()->Push(CopiedCompNode);
	}
	else
	{
		return;
	}
}

void CopyComp::Undo()
{
}

void CopyComp::Redo()
{
}
