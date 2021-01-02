#pragma once
#ifndef _Operate_SWITCH_H
#define _Operate_SWITCH_H
#include"Actions\Action.h"

class OperateSWITCH : public Action
{
private:
	int Cx, Cy;
	int CompIndex; //The index of the component which is selected.
public:
	OperateSWITCH(ApplicationManager *pApp, ActionType type);
	virtual ~OperateSWITCH(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};
#endif // !_SELECT_H_
