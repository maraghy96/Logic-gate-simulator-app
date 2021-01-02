//#include "Input.h"
#include "Output.h"
#include <sstream>
#include <cmath>

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

void Input::WaitMouseClick(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);
}

string Input::GetString(Output *pOut)
{
	///TODO: Implement this Function
	//Read a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" should be also supported
	//User should see what he is typing at the status bar
	int Subscript = 0, Cursor = 0, iX, iY, iWidth, iHeight;
	char Character;
	keytype kType;
	clicktype cType;
	char MyCursor = '_';
	cType = pWind->WaitMouseClick(iX, iY);
	string Sentence;
	if (cType == LEFT_CLICK)
	{
		pOut->PrintMsg("");
		pWind->FlushKeyQueue();
		kType = pWind->WaitKeyPress(Character);
		while ((int)Character != (int)'\r')
		{
			if ((int)Character != 8 && (int)Character != 27 && (int)Character != 4 && (int)Character != 6 && Cursor == Subscript)
			{
				pWind->GetStringSize(iWidth, iHeight, Sentence);
				if (iWidth < (pWind->GetWidth() - 100))
				{
					Sentence += Character;
				}
				Subscript = Sentence.size();
				Cursor = Subscript;
				pOut->PrintMsg(Sentence);
			}
			else if ((int)Character != 8 && (int)Character != 27 && Cursor != Subscript && (int)Character != 4 && (int)Character != 6)
			{

				pWind->GetStringSize(iWidth, iHeight, Sentence);
				if (iWidth < (pWind->GetWidth() - 100))
				{
					Sentence.insert(Cursor, 1, Character);
				}
				Cursor++;
				Subscript = Sentence.size();
				pOut->PrintMsg(Sentence);
			}
			else if (Subscript != 0 && Cursor != 0 && (int)Character == 8 && (int)Character != 27)
			{
				Sentence.erase(Cursor - 1, 1);
				Cursor--;
				Subscript = Sentence.size();
				pOut->PrintMsg(Sentence);
			}
			else if ((int)Character == 27)
			{
				pOut->ClearStatusBar();
				break;
			}
			kType = pWind->WaitKeyPress(Character);
			while ((int)Character == 4)
			{
				Cursor--;
				if (Cursor < 0)
				{
					kType = pWind->WaitKeyPress(Character);
					Cursor = 0;
					break;
				}
				kType = pWind->WaitKeyPress(Character);
			}
			while ((int)Character == 6)
			{
				Cursor++;
				if (Cursor > Subscript)
				{
					kType = pWind->WaitKeyPress(Character);
					Cursor = Subscript;
					break;
				}
				kType = pWind->WaitKeyPress(Character);
			}
		}
	}
	return Sentence;
}

//Overloading of getString
string Input::GetString(Output *pOut, string Sentence)
{
	///TODO: Implement this Function
	//Read a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" should be also supported
	//User should see what he is typing at the status bar
	int Subscript = Sentence.size(), Cursor = Subscript, iWidth, iHeight;
	char Character;
	keytype kType;
	pOut->PrintMsg(Sentence);
	pWind->FlushKeyQueue();
	kType = pWind->WaitKeyPress(Character);
	while ((int)Character != (int)'\r')
	{
		if ((int)Character != 8 && (int)Character != 27 && (int)Character != 4 && (int)Character != 6 && Cursor == Subscript)
		{
			pWind->GetStringSize(iWidth, iHeight, Sentence);
			if (iWidth < (pWind->GetWidth() - 100))
			{
				Sentence += Character;
			}
			Subscript = Sentence.size();
			Cursor = Subscript;
			pOut->PrintMsg(Sentence);
		}
		else if ((int)Character != 8 && (int)Character != 27 && Cursor != Subscript && (int)Character != 4 && (int)Character != 6)
		{

			pWind->GetStringSize(iWidth, iHeight, Sentence);
			if (iWidth < (pWind->GetWidth() - 100))
			{
				Sentence.insert(Cursor, 1, Character);
			}
			Cursor++;
			Subscript = Sentence.size();
			pOut->PrintMsg(Sentence);
		}
		else if (Subscript != 0 && Cursor != 0 && (int)Character == 8 && (int)Character != 27)
		{
			Sentence.erase(Cursor - 1, 1);
			Cursor--;
			Subscript = Sentence.size();
			pOut->PrintMsg(Sentence);
		}
		else if ((int)Character == 27)
		{
			pOut->ClearStatusBar();
			break;
		}
		kType = pWind->WaitKeyPress(Character);
		while ((int)Character == 4)
		{
			Cursor--;
			if (Cursor < 0)
			{
				kType = pWind->WaitKeyPress(Character);
				Cursor = 0;
				break;
			}
			kType = pWind->WaitKeyPress(Character);
		}
		while ((int)Character == 6)
		{
			Cursor++;
			if (Cursor > Subscript)
			{
				kType = pWind->WaitKeyPress(Character);
				Cursor = Subscript;
				break;
			}
			kType = pWind->WaitKeyPress(Character);
		}
	}
	return Sentence;
}


//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction(int x,int y) const
{
	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_AND2: return ADD_AND_GATE_2;
			case ITM_OR2: return ADD_OR_GATE_2;
			case ITM_INV: return ADD_INV;
			case ITM_AND3: return ADD_AND_GATE_3;
			case ITM_OR3: return ADD_OR_GATE_3;
			case ITM_NAND2: return ADD_NAND_GATE_2;
			case ITM_NOR2: return ADD_NOR_GATE_2;
			case ITM_NAND3: return ADD_NAND_GATE_3;
			case ITM_NOR3: return ADD_NOR_GATE_3;
			case ITM_XOR2: return ADD_XOR_GATE_2;
			case ITM_XNOR2: return ADD_XNOR_GATE_2;
			case ITM_XOR3: return ADD_XOR_GATE_3;
			case ITM_XNOR3: return ADD_XNOR_GATE_3;
			case ITM_BUFF: return ADD_Buff;
			case ITM_CONNECTION: return ADD_CONNECTION;
			case ITM_LED: return ADD_LED;
			case ITM_SWITCH: return ADD_Switch;
			case ITM_SIM: return SIM_MODE;
			case ITM_LOAD: return LOAD;
			case ITM_SAVE: return SAVE;
			case ITM_COPY: return COPY;
			case ITM_CUT: return CUT;
			case ITM_PASTE: return PASTE;
			case ITM_MOVE: return MOVE;
			case ITM_DEL: return DEL;
			case ITM_CLEAR: return CLEAR;
			case ITM_REDO: return REDO;
			case ITM_UNDO: return UNDO;
			case ITM_LABEL: return LABEL;
			case ITM_SEL: return SEL;
			case ITM_MULTIS: return MULTISELECT;
			case ITM_DESEL: return DESEL;
			case ITM_DEMULTISEL: return DEMULTISEL;
			case ITM_EXIT: return EXIT;

			default: return DSN_TOOL;	//A click on empty place in design toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DSN_TOOL;	//user want to select/unselect a statement in the flowchart
		}

		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
	else	//Application is in Simulation mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_TRUTH: return Create_TruthTable;
			case ITM_SWITCH_DSN: return DSN_MODE;
			//case ITM_VALID: return IF_VALID;
			case ITM_PROB: return PROB;
			case ITM_SIMU: return SIMU;

			default: return SIM_TOOL;	//A click on empty place in desgin toolbar
			}
		}
		//This should be changed after creating the compelete simulation bar - DONE
		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return SEL;	//user want to select/unselect a statement in the flowchart
		}

		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
}



Input::~Input()
{
}
