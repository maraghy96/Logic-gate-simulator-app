#include "SimMode.h"
#include "ApplicationManager.h"

SimMode::SimMode(ApplicationManager * pApp, ActionType type):Action(pApp,type)
{
}

SimMode::~SimMode()
{
}

void SimMode::ReadActionParameters()
{
}

void SimMode::Execute()
{
	pManager->GetOutput()->ClearToolbarArea();
	pManager->GetOutput()->CreateSimulationToolBar();
}

void SimMode::Undo()
{
}

void SimMode::Redo()
{
}
