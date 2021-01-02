#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	MODE AppMode;		//Application Mode (design or simulation)

	static const int	width = 1785, height = 650,	//Window width and height
		wx = 0, wy = 0,			//Window starting coordinates
		StatusBarHeight = 50,	//Status Bar Height
		ToolBarHeight = 60,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		ToolItemWidth = 40;		//Width of each item in toolbar menu

	color DrawColor;		//Drawing color
	color SelectColor;		//Highlighting color
	color ConnColor;		//Connector color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Back ground color


							//This should be calculated accurately because it will be used later to create connections between gates
							//For now, we will assume that rect width = 50 and height = 50
	static const int	AND2_Width = 40,
		AND2_Height = 40;
	static const int    OR2_Width = 40,
		OR2_Height = 40;
	static const int    INV_Width = 40,
		INV_Height = 40;
	static const int    AND3_Width = 40,
		AND3_Height = 40;
	static const int    OR3_Width = 40,
		OR3_Height = 40;
	static const int    NAND2_Width = 40,
		NAND2_Height = 40;
	static const int    NOR2_Width = 40,
		NOR2_Height = 40;
	static const int    NAND3_Width = 40,
		NAND3_Height = 40;
	static const int    NOR3_Width = 40,
		NOR3_Height = 40;
	static const int    XOR2_Width = 40,
		XOR2_Height = 40;
	static const int    XNOR2_Width = 40,
		XNOR2_Height = 40;
	static const int    XOR3_Width = 40,
		XOR3_Height = 40;
	static const int    XNOR3_Width = 40,
		XNOR3_Height = 40;
	static const int    BUFF_Width = 40,
		BUFF_Height = 40;
	static const int    LED_Width = 20,
		LED_Height = 20;
	static const int    SWITCH_Width = 20,
		SWITCH_Height = 20;
	static const int    CONNECTION_Width = 40,
		CONNECTION_Height = 40;

}UI;	//create a single global object UI

#endif