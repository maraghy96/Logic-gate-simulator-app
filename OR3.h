#ifndef _OR3_H
#define _OR3_H

/*
Class OR3
-----------
represent the 3-input OR gate
*/

#include "Components\Gate.h"

class OR3 :public Gate
{
public:
	OR3(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	OR3(int r_FanOut = AND2_FANOUT);
	virtual void Operate();	//Calculates the output of the OR3 gate
	virtual void Draw(Output* pOut);	//Draws 3-input gate
	virtual void DrawHi(Output* pOut);
	virtual void setSEL(); // Sets the selection variable to true
	virtual void deSEL(); // Resets the selection variable to false
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	virtual void Save(ofstream &output_f); //Save OR3 Gate
	OutputPin * getOutPin();
	InputPin *getInpPin();
	virtual void Load(ifstream & output_f, Output*pOut); //Load Components
	virtual Component* Copy();
	int getNoInp();
};
#endif
