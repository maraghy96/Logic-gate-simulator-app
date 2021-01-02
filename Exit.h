#ifndef _EXIT_H_
#define _EXIT_H_

#include "Actions/Action.h"
#include "Components\Connection.h"

class Exit : public Action
{
public:

	Exit(ApplicationManager *pApp, ActionType type);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

	~Exit(void);
};

#endif