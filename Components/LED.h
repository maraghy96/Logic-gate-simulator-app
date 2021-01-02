#ifndef _LED_H
#define _LED_H

/*
Class LED
-----------
- an LED is a component with no output pin and 1 input pin
*/
#include"Component.h"
#include"InputPin.h"
class LED :public Component
{
protected:
	InputPin m_InputPin; //input pin of the gate
	bool Taken;
public:
	LED(const GraphicsInfo &r_GfxInfo); //Default Constructor 
	LED();
	virtual void Draw(Output* pOut);	//Draws an LED
	virtual void setSEL(); // Sets the selection variable to true
	virtual void deSEL();
	void DrawHi(Output * pOut, bool HIGH);
	void DrawHi(Output * pOut);
	// Resets the selection variable to false
	virtual void Operate();	//Calculates the output according to the user input
	virtual void Save(ofstream &output_f); //Save LED
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s); //set status of Inputpin # n, to be used by connection class.
	virtual int GetOutPinStatus(); //returns status of outputpin if LED, return -1
	virtual int getNoInp();
	virtual void Load(ifstream & output_f, Output*pOut); //Load Components
	virtual Component* Copy();
	virtual InputPin getInpiPin();
	virtual InputPin *getInpPin();
	virtual OutputPin* getOutPin();
	void Take();
	bool isTaken();
	void ResetLed();
};
#endif
