#pragma once
#ifndef _DEL_H
#define _DEL_H

#include"Actions\Action.h"
#include "Components\Connection.h"
#include"ApplicationManager.h"
enum ActionType;
class DELo : public Action
{
	int deletions[200];
	Component** CompList;
	int deletionsCount;
	Component * undos[200];
	int dos;
	int redos[200];
	int rdos;
	int undosC[222];
	int dels;
	int delsc;
public:
	DELo(ApplicationManager *pApp, ActionType type);
	~DELo(void);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();

};
#endif





#pragma once
