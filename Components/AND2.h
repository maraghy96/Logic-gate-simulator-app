#ifndef _AND2_H
#define _AND2_H

/*
  Class AND2
  -----------
  represent the 2-input AND gate
*/

#include "Gate.h"


class AND2:public Gate
{
public:
	AND2(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	AND2(int r_FanOut=AND2_FANOUT);
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(Output* pOut);	//Draws 2-input gate
	virtual void DrawHi(Output* pOut);	//for each component to Draw itself
	virtual void setSEL(); // Sets the selection variable to true
	virtual void deSEL(); // Resets the selection variable to false
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	virtual void Save(ofstream &output_f); //Save AND2 Gate
	virtual void Load(ifstream & output_f, Output*pOut);
	virtual int getNoInp();
	virtual Component* Copy();
	OutputPin * getOutPin();
	InputPin *getInpPin();
};
#endif