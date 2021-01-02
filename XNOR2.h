#ifndef _XNOR2_H
#define _XNOR2_H

/*
Class XNOR2
-----------
represent the 2-input XNOR gate
*/

#include "Components\Gate.h"

class XNOR2 :public Gate
{
public:
	XNOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	XNOR2(int r_FanOut = AND2_FANOUT);
	virtual void Operate();	//Calculates the output of the XNOR gate
	virtual void Draw(Output* pOut);	//Draws 2-input gate
	virtual void DrawHi(Output* pOut);
	virtual void setSEL(); // Sets the selection variable to true
	virtual void deSEL(); // Resets the selection variable to false
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	virtual void Save(ofstream &output_f); //Save XNOR2 Gate 
	virtual int getNoInp();
	OutputPin * getOutPin();
	InputPin *getInpPin();
	virtual void Load(ifstream & output_f, Output*pOut); //Load Components
	virtual Component* Copy();


};
#endif
