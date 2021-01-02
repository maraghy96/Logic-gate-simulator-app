#pragma once
#ifndef _EDIT_H
#define _EDIT_H

#include"ApplicationManager.h"
#include <fstream>

class EditComp : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int CompIndex; //index of the component where label is assigned
	string CompLabel;

public:
	EditComp(ApplicationManager *pApp, ActionType type);
	virtual ~EditComp(void);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#endif