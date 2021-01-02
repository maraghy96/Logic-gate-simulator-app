#pragma once
#ifndef OUTPUT_H
#define OUTPUT_H

#include "..\Defs.h"
#include "Input.h"

class Component;
class ApplicationManager;

enum ConnectionCases {
	SWTGATE,
	GATEGATE,
	GATELED,
	AIRGATE,
	rSWTGATE,
	rGATEGATE,
	rGATELED,
	rAITGATE
};

class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;
	string* MenuItemImages;	//Pointer to the Graphics Window
public:
	Output(); // Performs the Window Initialization
	Input* CreateInput() const; //creates a pointer to the Input object
	void ChangeTitle(string Title) const;

	void CreateDesignToolBar() const;	//Tool bar of the design mode
	void CreateSimulationToolBar() const;//Tool bar of the simulation mode
	void CreateStatusBar() const;	//Create Status bar
	void ClearStatusBar() const;		//Clears the status bar
	void ClearDrawingArea() const;	//Clears the drawing area
	void ClearComponent(GraphicsInfo GInfo)const; //Clears a component from the drawing area
	void EraseLabel(string Label, GraphicsInfo GInfo); //Erases label of the component
	void DrawLabel(string Label, GraphicsInfo GInfo); //Draws label of the component
	void DrawCircleF(GraphicsInfo r_GfxInfo, int ClickedIndx)const;

	void MenuItems();
	window* CreateWind(int wd, int h, int x, int y) const; //Creates user interface window

	window * getWindow();

	// Draws 2-input AND gate
	void DrawAND2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	// Draws 2-input OR gate
	void DrawOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	// Draws INVERTER gate
	void DrawINV(GraphicsInfo r_GfxInfo, bool selected = false) const;
	// Draws 3-input AND gate
	void DrawAND3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	// Draws 3-input OR gate
	void DrawOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	// Draws 2-input NAND gate
	void DrawNAND2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	// Draws 2-input NOR gate
	void DrawNOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	// Draws 3-input NAND gate
	void DrawNAND3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	// Draws 3-input NOR gate
	void DrawNOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	// Draws 2-input XOR gate
	void DrawXOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	// Draws 2-input XNOR gate
	void DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	// Draws 3-input XOR gate
	void DrawXOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	// Draws 3-input XNOR gate
	void DrawXNOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	// Draws Buffer
	void DrawBUFF(GraphicsInfo r_GfxInfo, bool selected = false) const;
	// Draws LED
	void DrawLED(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawLEDSIMU(GraphicsInfo r_GfxInfo, bool HIGH=false) const;
	// Draws SWITCH
	void DrawSWITCH(GraphicsInfo r_GfxInfo, bool selected = false) const;

	void DrawSWITCHSIM(GraphicsInfo r_GfxInfo, bool selected=false) const;

	void DrawConnection(GraphicsInfo r_GfxInfo, int ClickedIndx, int **& CrnrArr, int & CrnrCount, bool iDragging, ApplicationManager * ipApp, int& DistPin, int ConnIndx=-1, bool selected=false) const;

	///TODO: Make similar functions for drawing all other gates, switch, and LED, .. etc - DONE

	void PrintMsg(string msg) const;	//Print a message on Status bar

	void ClearToolbarArea() const;

	void setBuff(bool sel) const;

	void setBuffering(bool sel) const;

	void FlushMouseQueue();

	~Output();
};

#endif

