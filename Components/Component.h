#pragma once
#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\GUI\Output.h"
#include "OutputPin.h"
#include "InputPin.h"
#include<fstream>
#include "..\Defs.h"

//Base class for classes Gate, Switch, and LED.
class Component
{
protected:
	string m_Label;
	CompType Type;
	Connection* AttachedConnection; //a pointer to the connection
	Component** Next; //Pointer to the next component
	int ID;
	Component**Previous; //Array of pointers to the previous components
	bool SEL;
	bool Operated; //Indication if a component is operated or not yet!
	bool Labelled;
	bool Clicked;
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component 
public:
	bool getSEL();
	int getID();
	static int ComponentsCount;
	Component(const GraphicsInfo &r_GfxInfo);
	Component **getPrevComp() const;
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;	//for each component to Draw itself
	virtual void DrawHi(Output* pOut) = 0;	//for each component to Draw itself HIGHLIGHTED!!!!!!!!!!!!!!!!!! Eh yad el enta 3mlo fo2 dah :P
	virtual void setSEL()=0; // Sets the selection variable to true
	virtual void deSEL()=0; // Resets the selection variable to false
	bool isSelected(); //Function to check if the gate is selected
	void setGfxInfo(GraphicsInfo Ginfo);  //Sets the GraphicsInfo of the component
	void setPos(int iX, int iY);//Changes the graphics info
	GraphicsInfo getGfxInfo();      //Returns the GraphicsInfo of the Component
	virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	int getID()const;  //This function returns the ID of the component
	Component** getNext()const; //This function returns a pointer to the next component
	void setNext(Component *Comp); //This function assigns a pointer to the next component
	bool setPrevious(Component *Comp);//This function assigns the previous component
	void resetPrevious(int index);//Set prev index
	void resetNext(int index);//Set next index
	virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1
	CompType GetCompType() const;   //returns type of the component
	void setCompType(CompType type);//Sets the component type
	void CancelOperation();//Resets all components
	void setOperated();
	virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.
	virtual void Save(ofstream &output_f)=0; //Save Components
	virtual void Load(ifstream & output_f, Output*pOut)=0; //Load Components
	virtual Component* Copy() = 0; //A function that copies the component
	void setConnection(Connection *Conn); //A function to set the connection pointer
	Connection* getConnection()const; //A function that returns the connection
	void setCompLabel(string sentence); //Add a label to a component
	virtual int getNoInp();
	bool isClicked()const;
	bool isOperated()const;
	void Click();
	void CancelClick();
	string getCompLabel() const;  //returns label of the component
	bool isLabelled();  // a function to detect if a component is labelled or not
	Component();	
	virtual OutputPin getOutiPin();
	virtual InputPin *getInpPin() = 0;
	virtual OutputPin * getOutPin() = 0;
	//Destructor must be virtual
	virtual ~Component();
};
#endif
