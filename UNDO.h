#pragma once
#ifndef _UNDO_ACTION__H
#define _UNDO_ACTION_H

#include"Actions\Action.h"

class UndoAction : public Action
{
public:
	UndoAction(ApplicationManager *pApp, ActionType type);
	virtual ~UndoAction(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};
#endif