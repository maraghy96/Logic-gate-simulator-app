#pragma once
#ifndef _Load_Act_H
#define _Load_Act_H

#include"Actions\Action.h"
#include <fstream>
#include<istream>

class Component;

class LoadDesign : public Action
{
public:
	LoadDesign(ApplicationManager *pApp, ActionType type);
	virtual ~LoadDesign(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif