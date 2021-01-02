#include "OperateSWTCH.h"
#include "ApplicationManager.h"


OperateSWITCH::OperateSWITCH(ApplicationManager *pApp, ActionType type) :Action(pApp, type)
{
}


OperateSWITCH::~OperateSWITCH()
{

}

void OperateSWITCH::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMsg("Select: Click on the gate to be selected.");
	Input *pIn = pManager->GetInput();
	pIn->GetPointClicked(Cx, Cy);
}

void OperateSWITCH::Execute()
{
	Output* pOut = pManager->GetOutput();

	//Gets the index of the clicked component
	CompIndex = pManager->WhichCompClicked();


	if (CompIndex != -1)
	{
		pManager->getCompList()[CompIndex]->Operate();
		pManager->getCompList()[CompIndex]->CancelClick();
		pManager->getCompList()[CompIndex]->DrawHi(pManager->GetOutput());
		Node* newNode = new Node;
		newNode->ActionExecuted = this;
		pManager->getOperationStack()->Push(newNode);
	}
	else
	{
		return;
	}
}

void OperateSWITCH::Undo()
{
}

void OperateSWITCH::Redo()
{
}

//int SelectComp::iX = 0;
//int SelectComp::iY = 0;