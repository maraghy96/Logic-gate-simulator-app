#include "DeSelectComp.h"
#include "ApplicationManager.h"


DeselectComp::DeselectComp(ApplicationManager *pApp, ActionType type) :Action(pApp, type)
{
}


DeselectComp::~DeselectComp()
{

}

void DeselectComp::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMsg("Deselect: Click on the gate to be deselected.");
	Input *pIn = pManager->GetInput();
	pIn->GetPointClicked(Cx, Cy);
}

void DeselectComp::Execute()
{
	Output* pOut = pManager->GetOutput();

	//Gets the index of the clicked component
	CompIndex = pManager->WhichCompClicked();
	if (CompIndex != -1 && pManager->getCompList()[CompIndex]->isSelected())
	{
		pManager->getCompList()[CompIndex]->deSEL();
		pManager->getCompList()[CompIndex]->CancelClick();
		pOut->PrintMsg("DeSelect: Done.");
		pManager->CreateAction(this);
		pManager->getUndoedActions()->EmptyStack();
	}
	else
	{
		return;
	}
}

void DeselectComp::Undo()
{
	pManager->getCompList()[CompIndex]->setSEL();
}

void DeselectComp::Redo()
{
	pManager->getCompList()[CompIndex]->deSEL();
}
