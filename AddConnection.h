#ifndef _ADD_CONN_H_
#define _ADD_CONN_H_

#include "Actions/Action.h"
#include "Components\Connection.h"

class AddConnection : public Action
{
private:
	int SrcGate;
	int Cx1, Cx2, Cy1, Cy2, Cx3, Cx4;
public:

	AddConnection(ApplicationManager *pApp, ActionType type);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

	~AddConnection(void);
};

#endif