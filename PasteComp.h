#pragma once
#ifndef _PASTE_COMP_H
#define _PASTE_COMP_H

#include"Actions\Action.h"
#include"Defs.H"

class Component;
enum ActionType;
class CopyComp;
enum clicktype;
class PasteComp : public Action
{
private:
	int Deletions[200];
	int DeletionsCount;
	Component*undos[20];
	int UndosCount;
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int _Cx, _Cy;
	clicktype Ctype;
	int ComponentIndex;
	GraphicsInfo GfxOld;  //Old graphics info of Component
	GraphicsInfo GfxNew;  //New graphics info of Component
	ActionType CutOrCopy; //Last Action Type
	Component *Cmpnt; //The component where the action takes place
public:
	PasteComp(ApplicationManager *pApp, ActionType type);
	virtual ~PasteComp(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};
#endif