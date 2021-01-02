#pragma once
#ifndef _SIMULATE_H
#define _SIMULATE_H
#include"Actions\Action.h"
#include"Components\Component.h"
#include"Defs.H"
class SimulateCircuit : public Action
{
private:
	int Cx, Cy;
	//ofstream myTruthTable; //txt file for the truth table entries
public:
	SimulateCircuit(ApplicationManager *pApp, ActionType type);
	virtual ~SimulateCircuit(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	void Execute2();

	bool CheckPrevious(Component * Comp);

	//Simulating the circuit to create truth table
	void Simulate(STATUS **InputCombinations, int NumInputs,STATUS **&Outputs,int NumOutputs);
	void OperateComp(Component *Comp);
	virtual void Undo();
	virtual void Redo();
};
#endif