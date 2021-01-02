#ifndef _VALID_CONN_
#define _VALID_CONN_

#include "Actions/Action.h"
#include "Components\Connection.h"

class ValidateCircuit : public Action
{
private:
	bool Valid;
public:

	ValidateCircuit(ApplicationManager *pApp, ActionType type);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

	~ValidateCircuit(void);
};

#endif