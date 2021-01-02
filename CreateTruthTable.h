#pragma once
#ifndef _Create_Truth_Table_H
#define _Create_Truth_Table_H

#include"Actions/Action.h"
#include"SimulateCircuit.h"
#include "Defs.H"

class CreateTruthTable : public Action
{
private:
	int NumInputs; //Number of the inputs in the design
	int NumOutputs; //Number of the outputs in the design
	STATUS **InputCombinations; //2D Array of the all possible combinations
	STATUS **Outputs;  //2D Array of the outputs
	ofstream myTruthTable; //txt file for the truth table entries
	window *pWind;
	int Cx, Cy;
public:
	CreateTruthTable(ApplicationManager *pApp, ActionType type);
	virtual ~CreateTruthTable(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};
#endif