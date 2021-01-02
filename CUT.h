#pragma once
#ifndef _CUT_H
#define _CUT_H

#include"Actions\Action.h"

enum ActionType;

class CutComp : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int _Cx, _Cy; //new center of the gate
	int* CompIndexFound;  //Array of index of selected components 
	GraphicsInfo GfxOld;  //Old graphics info of Component
	GraphicsInfo GfxNew;  //New graphics info of Component

public:
	CutComp(ApplicationManager *pApp, ActionType type);
	virtual ~CutComp(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};
#endif