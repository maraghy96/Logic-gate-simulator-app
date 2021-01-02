#pragma once
#ifndef _REDO_ACTION_H
#define _REDO_ACTION_H

#include"Actions\Action.h"

class REDOAction : public Action
{
public:
	REDOAction(ApplicationManager *pApp, ActionType type);
	virtual ~REDOAction(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};
#endif