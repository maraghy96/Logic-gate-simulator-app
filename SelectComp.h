#pragma once
#ifndef _SELECT_H_
#define _SELECT_H_

#include"Actions\Action.h"

class SelectComp : public Action
{
private:
	int Cx, Cy;
	int CompIndex; //The index of the component which is selected.
public:
	SelectComp(ApplicationManager *pApp, ActionType type);
	virtual ~SelectComp(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};
#endif // !_SELECT_H_
