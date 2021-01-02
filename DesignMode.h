#ifndef _DES_H_
#define _DES_H_
#include"Actions\Action.h"

class DesignMode : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
public:
	DesignMode(ApplicationManager *pApp, ActionType type);
	virtual ~DesignMode(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif