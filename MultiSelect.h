#ifndef _MSELECT_H_
#define _MSELECT_H_

#include"Actions\Action.h"
#include "Components\Component.h"

class MultiSelect : public Action {
private:
	static int iX, iY;
	int* IndexCmp; //The index of the component which is selected.
public:
	MultiSelect(ApplicationManager *pApp, ActionType type);
	virtual ~MultiSelect(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif // !_MSELECT_H_
