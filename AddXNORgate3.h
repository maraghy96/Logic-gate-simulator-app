#ifndef _ADD_XNOR_GATE3_H
#define _ADD_XNOR_GATE3_H

#include"Actions\Action.h"
#include "XNOR3.h"

class AddXNORgate3 : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
public:
	AddXNORgate3(ApplicationManager *pApp , ActionType type);
	virtual ~AddXNORgate3(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif