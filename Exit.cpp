#include "Exit.h"
#include "ApplicationManager.h"


Exit::Exit(ApplicationManager *pApp, ActionType type) :Action(pApp, type)
{
}

void Exit::ReadActionParameters()
{
}

void Exit::Execute()
{
}

void Exit::Undo()
{
}

void Exit::Redo()
{
}

Exit::~Exit()
{
}
