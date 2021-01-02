#pragma once
#ifndef _COPY_H
#define _COPY_H

#include"Actions\Action.h"

enum ActionType;
class CopyComp : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int* CompIndexFound;  //Array of index of selected components 
public:
	CopyComp(ApplicationManager *pApp, ActionType type);

	virtual ~CopyComp(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();

	virtual void Redo();
};
#endif