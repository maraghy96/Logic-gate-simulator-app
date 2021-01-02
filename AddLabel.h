#pragma once
#ifndef _Add_LABEL_H
#define _Add_LABEL_H

#include"ApplicationManager.h"
#include <fstream>

class AddLabel : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int CompIndex; //index of the component where label is assigned
	string CompLabel;  //Original Label
	string CompLabelEdited; //Edited Label

public:
	AddLabel(ApplicationManager *pApp, ActionType type);
	virtual ~AddLabel(void);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#endif