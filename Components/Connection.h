#pragma once
#include"Component.h"
#include "InputPin.h"
#include "OutputPin.h"
#include "LED.h"
#include "../Actions/Action.h"
#include "Gate.h"

class Connection : public Component
{
	Component*	SrcCmpnt;	//Connection source component
	Component*	DstCmpnt;	//Connection Destination component
	OutputPin* SrcPin;	//The Source pin of this connection (an output pin of certain Component)
	InputPin* DstPin;	//The Destination pin of this connection (an input pin of certain Component)
	int SrcCompID;
	int DstCompID;
	int DestPinNum; //The pin number of the destination
	ApplicationManager * pApp;
	int **CrnrArr; //For selection and deselection , array of corners made for nw..
	int **TempCrnrArr;
	int NumCorners;
public:
	int getDestPinNum();
	void setDestPinNum(int iDst);
	int getCrnrCount();
	int getSrcCompID()const;
	int getDstCompID()const;
	virtual InputPin *getInpPin();
	int ** getCrnrArr();
	Connection(const GraphicsInfo & r_GfxInfo, ApplicationManager * ipApp, Component *pS = NULL, int Pin = 0);
	Connection(ApplicationManager *ptr);
	~Connection();
	virtual void Operate();	//Calculates the output according to the inputs
	void setTempCrnrArr();
	void Draws(Output * pOut);
	int ** getTempCrnrArr();
	void DrawError(Output * pOut);
	virtual void Draw(Output* pOut);	//for each component to Draw itself
	virtual void DrawHi(Output *pOut);
	void setSourcePin(OutputPin *pSrcPin);
	void setDestPin(InputPin *pDstPin);
	void setSrcGate(Component*pSrcGate);
	void setDstGate(Component*pDistGate);
	void setCrnrArr(int **iCrnrArr);
	void setCrnrCount(int Count);
	virtual void setSEL();
	virtual void deSEL();
	OutputPin* getSourcePin();
	InputPin* getDestPin();
	Component* getSrcGate();
	Component* getDestGate();
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	virtual CompType GetCompType() const;   //returns type of the component
	virtual void Save(ofstream &output_f); //Save Buffer Gate
	virtual void Load(ifstream &output_f, Output* pOut); //Load Components
	virtual Component* Copy(); //A function that copies the component
	virtual OutputPin* getOutPin();

	void AdjustSrcDst(ConnectionCases cS, int Index1, int Index2, int DstPin, GraphicsInfo GInfo, int ConnectionIndx = -1);

	void AdjustCrnrArr(ConnectionCases cS, int ClickedIndx2, int & DistPin, int **& CrnrArr, int CrnrCount, window * pWind);
	void AdjstGrfxInfo();
};


