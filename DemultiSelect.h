#ifndef _DMSELECT_H_
#define _DMSELECT_H_

#include"Actions\Action.h"
#include "Components\Component.h"

class DemultiSelect : public Action {
private:
	static int iX, iY;
	int* IndexCmp; //The index of the component which is selected.
public:
	DemultiSelect(ApplicationManager *pApp, ActionType type);
	virtual ~DemultiSelect(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif // !_DMSELECT_H_
