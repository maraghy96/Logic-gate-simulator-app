#ifndef _MOVEACT_H_
#define _MOVEACT_H_

#include"Actions\Action.h"
#include"Defs.H"
class Component;
class window;
class Output;
struct GraphicsInfo;

class MoveAct : public Action
{
private:
	static int iX, iY, iXOld, iYOld; //New and Old coordinates.
	int IndexCmp; //The index of the component to be moved.
	bool Dragging;
	Component* MoveCmp; //Pointer to Component Being moved.
	GraphicsInfo DeltaOld;
	bool MultipleMove;
	int NumSelected;
	Component**MovedComps;
public:
	MoveAct(ApplicationManager *pApp, ActionType type);
	virtual ~MoveAct(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	void Drag(Component * iMoveComp, bool iDragging, window * pWind, ApplicationManager * ipManager, char cKeyData, Output * pOut);
	void Drag(Component**iMoveComps, int NumSelected, bool iDragging, window* pWind, ApplicationManager*ipManager, char cKeyData, Output*pOut);

	virtual void Undo();
	virtual void Redo();


};

#endif // !_MOVEACT_H_
