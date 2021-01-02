#ifndef _SWITCH_H
#define _SWITCH_H

/*
Class SWITCH
-----------
- a switch is a component with one output pin and no input pins
*/

#include"Components\OutputPin.h"
#include"Components\Component.h"
#include"CMUgraphicsLib\CMUgraphics.h"
class SWITCH:public Component
{
protected:
	OutputPin s_OutputPin;	//The Switch output pin
	window *pWind;  //Pointer to class window (Added by KHAIRY)
	bool Set;
public:
	SWITCH(const GraphicsInfo &r_GfxInfo,int r_FanOut=1);
	SWITCH(int r_FanOut = 1);
	virtual void Draw(Output* pOut);	//Draws a switch
	virtual void DrawHi(Output* pOut);
	virtual void setSEL(); // Sets the selection variable to true
	virtual void deSEL(); // Resets the selection variable to false
	virtual int GetOutPinStatus(); //returns status of outputpin if LED, return -1
	virtual void Operate();	//Calculates the output according to the user input
	virtual void Save(ofstream &output_f); //Save SWITCH 
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s); //set status of Inputpin # n, to be used by connection class.
	virtual void Load(ifstream & output_f, Output*pOut); //Load Components
	virtual Component* Copy();
	OutputPin getOutiPin();
	virtual InputPin *getInpPin();
	virtual OutputPin* getOutPin();
	bool isSet();
	void setSwitchStatus();
	void setOutputPinStatus(STATUS s);
	void ResetSwitch();

};
#endif

