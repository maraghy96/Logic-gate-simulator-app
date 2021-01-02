#ifndef _SAVE_DESIGN_H
#define _SAVE_DESIGN_H

#include"Actions\Action.h"
#include <fstream>

class SaveDesign : public Action
{
public:
	SaveDesign(ApplicationManager *pApp, ActionType type);
	virtual ~SaveDesign(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif