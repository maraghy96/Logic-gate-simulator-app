#include "REDO.h"
#include "ApplicationManager.h"


REDOAction::REDOAction(ApplicationManager *pApp, ActionType type) :Action(pApp,type)
{
}


REDOAction::~REDOAction()
{
}

void REDOAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Action Redoed");

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void REDOAction::Execute()
{
	ReadActionParameters();
	int ComponentsDeletedCount = pManager->getCompDeleted();
	if (ComponentsDeletedCount == 0 && (pManager->getUndoedActions()->StackTop()!=NULL && pManager->getUndoedActions()->StackTop()->ActionExecuted->getActionType()!=LABEL &&  pManager->getUndoedActions()->StackTop()->ActionExecuted->getActionType() != CUT && pManager->getCopyCutIndex()->StackTop()!=NULL))
	{
		return;
	}
	pManager->RedoTheAction();
}

void REDOAction::Undo()
{

}

void REDOAction::Redo()
{

}
