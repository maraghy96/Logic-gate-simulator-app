#include "UNDO.h"
#include "ApplicationManager.h"


UndoAction::UndoAction(ApplicationManager *pApp, ActionType type) :Action(pApp, type)
{
}


UndoAction::~UndoAction()
{
}

void UndoAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Action Undoed");

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void UndoAction::Execute()
{
	ReadActionParameters();
	int ComponentsCount = pManager->getCompCount();
	if (ComponentsCount == 0  && Act_Type==UNDO && pManager->getActions()->StackTop()->ActionExecuted->getActionType()!=DEL)
	{
		return;
	}
	pManager->UndoTheAction();
}

void UndoAction::Undo()
{

}

void UndoAction::Redo()
{
	
}
