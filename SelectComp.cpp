#include "SelectComp.h"
#include "ApplicationManager.h"


SelectComp::SelectComp(ApplicationManager *pApp, ActionType type) :Action(pApp, type)
{
}


SelectComp::~SelectComp()
{

}

void SelectComp::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMsg("Select: Click on the gate to be selected.");
	Input *pIn = pManager->GetInput();
	pIn->GetPointClicked(Cx, Cy);
}

void SelectComp::Execute()
{
	Output* pOut = pManager->GetOutput();

	//Gets the index of the clicked component
	CompIndex = pManager->WhichCompClicked();


	if (CompIndex != -1 && !pManager->getCompList()[CompIndex]->isSelected())
	{
		int CountSelected = pManager->CountSelected();
		int *Comps_Selected = pManager->WhichCompSelected();
		if (CountSelected == 1)
		{
			pManager->getCompList()[Comps_Selected[CountSelected - 1]]->deSEL();
		}
		pManager->getCompList()[CompIndex]->setSEL();
		pManager->getCompList()[CompIndex]->CancelClick();
		pOut->PrintMsg("Select: Done.");
		pManager->CreateAction(this);
		pManager->getUndoedActions()->EmptyStack();
	}
	else
	{
		return;
	}
}

void SelectComp::Undo()
{
	pManager->getCompList()[CompIndex]->deSEL();
}

void SelectComp::Redo()
{
	pManager->getCompList()[CompIndex]->setSEL();
}

//int SelectComp::iX = 0;
//int SelectComp::iY = 0;