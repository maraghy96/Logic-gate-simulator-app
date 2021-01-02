#pragma once
#ifndef _DESELECT_H_
#define _DESELECT_H_

#include"Actions\Action.h"

class DeselectComp : public Action
{
private:
	int Cx, Cy;
	int CompIndex; //The index of the component which is deselected.
public:
	DeselectComp(ApplicationManager *pApp, ActionType type);
	virtual ~DeselectComp(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};
#endif // !_DESELECT_H_
