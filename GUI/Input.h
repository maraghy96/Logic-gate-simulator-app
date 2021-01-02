#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "UI_Info.h"

class Output;
class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window

public:
	Input(window*);
	void GetPointClicked(int &, int &);	//Get coordinate where user clicks
	void WaitMouseClick(int &, int &);
	string GetString(Output*);		//Returns a string entered by the user
	string GetString(Output *pOut, string Sentence); //returns a string edited by the user

	ActionType GetUserAction(int x, int y)const;
	~Input();
};