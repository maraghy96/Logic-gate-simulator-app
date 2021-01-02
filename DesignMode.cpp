#include "DesignMode.h"
#include "ApplicationManager.h"

DesignMode::DesignMode(ApplicationManager * pApp, ActionType type) :Action(pApp, type)
{
}

DesignMode::~DesignMode()
{
}

void DesignMode::ReadActionParameters()
{
}

void DesignMode::Execute()
{
	pManager->GetOutput()->ClearToolbarArea();
	pManager->GetOutput()->CreateDesignToolBar();
}

void DesignMode::Undo()
{
}

void DesignMode::Redo()
{
}
