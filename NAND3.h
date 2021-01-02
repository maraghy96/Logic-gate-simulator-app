#pragma once
#ifndef _NAND3_H
#define _NAND3_H

/*
Class NAND3
-----------
represent the 3-input NAND gate
*/

#include"Components\Gate.h"

class NAND3 :public Gate
{
public:
	NAND3(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	NAND3(int r_FanOut = AND2_FANOUT);

	virtual void Operate();	//Calculates the output of the 3 input NAND gate
	virtual void Draw(Output* pOut);	//Draws 3-input gate
	virtual void DrawHi(Output* pOut);
	virtual void setSEL(); // Sets the selection variable to true
	virtual void deSEL(); // Resets the selection variable to false
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	virtual void Save(ofstream &output_f); //Save NAND3 Gate
	virtual int getNoInp();
	OutputPin * getOutPin();
	InputPin *getInpPin();
	virtual void Load(ifstream & output_f, Output*pOut); //Load Components
	virtual Component* Copy();

};
#endif
