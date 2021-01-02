#ifndef _EDIT_CONN_H_
#define _EDIT_CONN_H_

#include "Actions/Action.h"
#include "Components\Connection.h"

class EditConnection : public Action
{
private:
	int IndexClicked;
	int Cx1, Cx2, Cy1, Cy2;
public:

	EditConnection(ApplicationManager *pApp, ActionType type);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

	~EditConnection(void);
};

#endif