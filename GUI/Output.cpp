#include "Output.h"
#include "../Components/Component.h"
#include"../Components/Connection.h"
#include "../ApplicationManager.h"
Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode

							//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = BLUE;
	UI.BkGrndColor = WHITE;

	MenuItemImages = new string[ITM_DSN_CNT];
	MenuItems();
	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	ChangeTitle("Programming Techniques Project - 23");

	CreateDesignToolBar();	//Create the design toolbar
	CreateStatusBar();		//Create Status bar


}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

void Output::MenuItems()
{
	MenuItemImages[ITM_AND2] = "Images\\Menu\\Menu_AND2.jpg";
	MenuItemImages[ITM_OR2] = "Images\\Menu\\Menu_OR2.jpg";
	MenuItemImages[ITM_INV] = "Images\\Menu\\Menu_INV.jpg";
	MenuItemImages[ITM_OR3] = "Images\\Menu\\Menu_OR3.jpg";
	MenuItemImages[ITM_AND3] = "Images\\Menu\\Menu_AND3.jpg";
	MenuItemImages[ITM_NOR2] = "Images\\Menu\\Menu_NOR2.jpg";
	MenuItemImages[ITM_NAND2] = "Images\\Menu\\Menu_NAND2.jpg";
	MenuItemImages[ITM_NOR3] = "Images\\Menu\\Menu_NOR3.jpg";
	MenuItemImages[ITM_NAND3] = "Images\\Menu\\Menu_NAND3.jpg";
	MenuItemImages[ITM_XOR2] = "Images\\Menu\\Menu_XOR2.jpg";
	MenuItemImages[ITM_XNOR2] = "Images\\Menu\\Menu_XNOR2.jpg";
	MenuItemImages[ITM_XOR3] = "Images\\Menu\\Menu_XOR3.jpg";
	MenuItemImages[ITM_XNOR3] = "Images\\Menu\\Menu_XNOR3.jpg";
	MenuItemImages[ITM_BUFF] = "Images\\Menu\\Menu_BUFF.jpg";
	MenuItemImages[ITM_LED] = "Images\\Menu\\Menu_LED.jpg";
	MenuItemImages[ITM_SWITCH] = "Images\\Menu\\Menu_SWITCH.jpg";
	MenuItemImages[ITM_CONNECTION] = "Images\\Menu\\Menu_CONNECTION.jpg";
	MenuItemImages[ITM_SIM] = "Images\\Menu\\Menu_SIM.jpg";
	MenuItemImages[ITM_LOAD] = "Images\\Menu\\Menu_LOAD.jpg";
	MenuItemImages[ITM_SAVE] = "Images\\Menu\\Menu_SAVE.jpg";
	MenuItemImages[ITM_COPY] = "Images\\Menu\\Menu_COPY.jpg";
	MenuItemImages[ITM_CUT] = "Images\\Menu\\Menu_CUT.jpg";
	MenuItemImages[ITM_PASTE] = "Images\\Menu\\Menu_PASTE.jpg";
	MenuItemImages[ITM_MOVE] = "Images\\Menu\\Menu_MOVE.jpg";
	MenuItemImages[ITM_DEL] = "Images\\Menu\\Menu_DEL.jpg";
	MenuItemImages[ITM_CLEAR] = "Images\\Menu\\Menu_CLEAR.jpg";
	MenuItemImages[ITM_REDO] = "Images\\Menu\\Menu_REDO.jpg";
	MenuItemImages[ITM_UNDO] = "Images\\Menu\\Menu_UNDO.jpg";
	MenuItemImages[ITM_LABEL] = "Images\\Menu\\Menu_LABEL.jpg";
	MenuItemImages[ITM_SEL] = "Images\\Menu\\Menu_SEL.jpg";
	MenuItemImages[ITM_MULTIS] = "Images\\Menu\\Menu_MULTISEL.jpg";
	MenuItemImages[ITM_DESEL] = "Images\\Menu\\Menu_DESEL.jpg";
	MenuItemImages[ITM_DEMULTISEL] = "Images\\Menu\\Menu_DEMULTISEL.jpg";
	MenuItemImages[ITM_EXIT] = "Images\\Menu\\Menu_Exit.jpg";
}

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}

window* Output::getWindow() {
	return pWind;
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
						// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(17, BOLD, ROMAN, "Times New Roman");
	pWind->SetPen(BLACK);
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ClearToolbarArea() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
	pWind->SetPen(BLACK, 1);
	pWind->SetBrush(BLACK);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight, FRAME);
}
void Output::setBuff(bool sel) const
{
	if (sel) {
		pWind->SetBuffering(true);
		CreateDesignToolBar();
		CreateStatusBar();
	}
	else {
		pWind->SetBuffering(false);
	}
}

void Output::setBuffering(bool sel) const
{
	if (sel) {
		pWind->SetBuffering(true);
		CreateDesignToolBar();
		CreateStatusBar();
	}
	else {
		pWind->SetBuffering(false);
	}
}
void Output::FlushMouseQueue()
{
	pWind->FlushMouseQueue();
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void Output::ClearDrawingArea() const
{
	pWind->SetPen(BLACK, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);

}
void Output::ClearComponent(GraphicsInfo GInfo) const
{
	pWind->SetBrush(WHITE);
	pWind->SetPen(WHITE);
	pWind->SetPen(WHITE);
	pWind->DrawRectangle(GInfo.x1, GInfo.y1, GInfo.x2, GInfo.y2);
}
void Output::EraseLabel(string Label, GraphicsInfo GInfo)
{
	int cx = (GInfo.x1 + GInfo.x2) / 2;
	int cy = (GInfo.y1 + GInfo.y2) / 2;

	pWind->SetFont(13, PLAIN | ITALICIZED, BY_NAME, "Arial");

	pWind->SetPen(WHITE);

	pWind->DrawString(cx - 10, (cy - 30), Label);
	pWind->DrawString(cx - 10, (cy - 30), Label);
	pWind->DrawString(cx - 10, (cy - 30), Label);
	pWind->DrawString(cx - 10, (cy - 30), Label);
	pWind->DrawString(cx - 10, (cy - 30), Label);
	pWind->DrawString(cx - 10, (cy - 30), Label);
	pWind->DrawString(cx - 10, (cy - 30), Label);
	pWind->DrawString(cx - 10, (cy - 30), Label);
	pWind->DrawString(cx - 10, (cy - 30), Label);
	pWind->DrawString(cx - 10, (cy - 30), Label);
	pWind->DrawString(cx - 10, (cy - 30), Label);
	pWind->DrawString(cx - 10, (cy - 30), Label);
	pWind->DrawString(cx - 10, (cy - 30), Label);
	pWind->DrawString(cx - 10, (cy - 30), Label);
	pWind->DrawString(cx - 10, (cy - 30), Label);
}
void Output::DrawLabel(string Label, GraphicsInfo GInfo)
{
	int cx = (GInfo.x1 + GInfo.x2) / 2;
	int cy = (GInfo.y1 + GInfo.y2) / 2;

	pWind->SetFont(13, PLAIN | ITALICIZED, BY_NAME, "Arial");

	pWind->SetPen(BLACK);

	pWind->DrawString(cx - 10, (cy - 40), Label);
	pWind->DrawString(cx - 10, (cy - 40), Label);
	pWind->DrawString(cx - 10, (cy - 40), Label);
	pWind->DrawString(cx - 10, (cy - 40), Label);
	pWind->DrawString(cx - 10, (cy - 40), Label);
	pWind->DrawString(cx - 10, (cy - 40), Label);
	pWind->DrawString(cx - 10, (cy - 40), Label);
	pWind->DrawString(cx - 10, (cy - 40), Label);
	pWind->DrawString(cx - 10, (cy - 40), Label);
	pWind->DrawString(cx - 10, (cy - 40), Label);
	pWind->DrawString(cx - 10, (cy - 40), Label);
	pWind->DrawString(cx - 10, (cy - 40), Label);
	pWind->DrawString(cx - 10, (cy - 40), Label);
	pWind->DrawString(cx - 10, (cy - 40), Label);

}
void Output::DrawCircleF(GraphicsInfo r_GfxInfo, int ClickedIndx) const
{
	if (ClickedIndx == -1) {
		pWind->SetPen(BLACK, 2);
		pWind->SetBrush(BLACK);
		pWind->DrawCircle(r_GfxInfo.x1, r_GfxInfo.y1, 3, FILLED);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode

							//You can draw the tool bar icons in any way you want.

							//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_AND2] = "Images\\Menu\\Menu_AND2.jpg";
	MenuItemImages[ITM_OR2] = "Images\\Menu\\Menu_OR2.jpg";
	MenuItemImages[ITM_INV] = "Images\\Menu\\Menu_INV.jpg";
	MenuItemImages[ITM_OR3] = "Images\\Menu\\Menu_OR3.jpg";
	MenuItemImages[ITM_AND3] = "Images\\Menu\\Menu_AND3.jpg";
	MenuItemImages[ITM_NOR2] = "Images\\Menu\\Menu_NOR2.jpg";
	MenuItemImages[ITM_NAND2] = "Images\\Menu\\Menu_NAND2.jpg";
	MenuItemImages[ITM_NOR3] = "Images\\Menu\\Menu_NOR3.jpg";
	MenuItemImages[ITM_NAND3] = "Images\\Menu\\Menu_NAND3.jpg";
	MenuItemImages[ITM_XOR2] = "Images\\Menu\\Menu_XOR2.jpg";
	MenuItemImages[ITM_XNOR2] = "Images\\Menu\\Menu_XNOR2.jpg";
	MenuItemImages[ITM_XOR3] = "Images\\Menu\\Menu_XOR3.jpg";
	MenuItemImages[ITM_XNOR3] = "Images\\Menu\\Menu_XNOR3.jpg";
	MenuItemImages[ITM_BUFF] = "Images\\Menu\\Menu_BUFF.jpg";
	MenuItemImages[ITM_LED] = "Images\\Menu\\Menu_LED.jpg";
	MenuItemImages[ITM_SWITCH] = "Images\\Menu\\Menu_SWITCH.jpg";
	MenuItemImages[ITM_CONNECTION] = "Images\\Menu\\Menu_CONNECTION.jpg";
	MenuItemImages[ITM_SIM] = "Images\\Menu\\Menu_SIM.jpg";
	MenuItemImages[ITM_LOAD] = "Images\\Menu\\Menu_LOAD.jpg";
	MenuItemImages[ITM_SAVE] = "Images\\Menu\\Menu_SAVE.jpg";
	MenuItemImages[ITM_COPY] = "Images\\Menu\\Menu_COPY.jpg";
	MenuItemImages[ITM_CUT] = "Images\\Menu\\Menu_CUT.jpg";
	MenuItemImages[ITM_PASTE] = "Images\\Menu\\Menu_PASTE.jpg";
	MenuItemImages[ITM_MOVE] = "Images\\Menu\\Menu_MOVE.jpg";
	MenuItemImages[ITM_DEL] = "Images\\Menu\\Menu_DEL.jpg";
	MenuItemImages[ITM_CLEAR] = "Images\\Menu\\Menu_CLEAR.jpg";
	MenuItemImages[ITM_REDO] = "Images\\Menu\\Menu_REDO.jpg";
	MenuItemImages[ITM_UNDO] = "Images\\Menu\\Menu_UNDO.jpg";
	MenuItemImages[ITM_LABEL] = "Images\\Menu\\Menu_LABEL.jpg";
	MenuItemImages[ITM_SEL] = "Images\\Menu\\Menu_SEL.jpg";
	MenuItemImages[ITM_MULTIS] = "Images\\Menu\\Menu_MULTISEL.jpg";
	MenuItemImages[ITM_DESEL] = "Images\\Menu\\Menu_DESEL.jpg";
	MenuItemImages[ITM_DEMULTISEL] = "Images\\Menu\\Menu_DEMULTISEL.jpg";
	MenuItemImages[ITM_EXIT] = "Images\\Menu\\Menu_Exit.jpg";

	//TODO: Prepare image for each menu item and add it to the list - DONE

	//Draw menu item one image at a time
	for (int i = 0; i < ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(BLACK, 1);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;	//Simulation Mode

								//You can draw the tool bar icons in any way you want.

								//First prepare List of images for each menu item
	string SimItemImages[ITM_SIM_CNT];
	SimItemImages[ITM_TRUTH] = "Images\\Menu\\Menu_TRUTH.jpg";
	SimItemImages[ITM_VALID] = "Images\\Menu\\Menu_VALID.jpg";
	SimItemImages[ITM_PROB] = "Images\\Menu\\Menu_PROB.jpg";
	SimItemImages[ITM_SIMU] = "Images\\Menu\\Menu_SIMU.jpg";
	SimItemImages[ITM_SWITCH_DSN] = "Images\\Menu\\Menu_DSN.jpg";

	//TODO: Prepare image for each menu item and add it to the list - DONE

	//Draw menu item one image at a time
	for (int i = 0; i < ITM_SIM_CNT; i++)
		pWind->DrawImage(SimItemImages[i], i*UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	//pWind->SetPen(WHITE, 3);
	//pWind->DrawLine(0, 0, UI.width, 0);
	pWind->SetPen(BLACK, 1);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)


}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_OR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_OR2.jpg";

	//Draw OR2 Gate at Gfx_Info (2nd corner)
	//Set the Image Width & Height by OR2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.OR2_Width, UI.OR2_Height);
}

void Output::DrawINV(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_INV_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_INV.jpg";

	//Draw INVERTER Gate at Gfx_Info (3rd Corner)
	//Set the Image Width & Height by INV Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.INV_Width, UI.INV_Height);
}

void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND3.jpg";

	//Draw AND3 Gate at Gfx_Info (4th Corner)
	//Set the Image Width & Height by AND3 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND3_Width, UI.AND3_Height);
}

void Output::DrawOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_OR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_OR3.jpg";

	//Draw OR3 Gate at Gfx_Info (5th Corner)
	//Set the Image Width & Height by OR3 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.OR3_Width, UI.OR3_Height);
}

void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NAND2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NAND2.jpg";

	//Draw NAND2 Gate at Gfx_Info (6th Corner)
	//Set the Image Width & Height by NAND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.NAND2_Width, UI.NAND2_Height);
}

void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR2.jpg";

	//Draw NOR2 Gate at Gfx_Info (7th Corner)
	//Set the Image Width & Height by NOR2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.NOR2_Width, UI.NOR2_Height);
}

void Output::DrawNAND3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NAND3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NAND3.jpg";

	//Draw NAND3 Gate at Gfx_Info (8th Corner)
	//Set the Image Width & Height by NAND3 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.NAND3_Width, UI.NAND3_Height);
}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR3.jpg";

	//Draw NOR3 Gate at Gfx_Info (9th Corner)
	//Set the Image Width & Height by NOR3 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.NOR3_Width, UI.NOR3_Height);
}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR2.jpg";

	//Draw XOR2 Gate at Gfx_Info (10th Corner)
	//Set the Image Width & Height by XOR2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.XOR2_Width, UI.XOR2_Height);
}

void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XNOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XNOR2.jpg";

	//Draw XNOR2 Gate at Gfx_Info (11th Corner)
	//Set the Image Width & Height by XNOR2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.XNOR2_Width, UI.XNOR2_Height);
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR3.jpg";

	//Draw XOR3 Gate at Gfx_Info (12th Corner)
	//Set the Image Width & Height by XOR3 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.XOR3_Width, UI.XOR3_Height);
}

void Output::DrawXNOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XNOR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XNOR3.jpg";

	//Draw XNOR3 Gate at Gfx_Info (13th Corner)
	//Set the Image Width & Height by XNOR3 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.XNOR3_Width, UI.XNOR3_Height);
}

void Output::DrawBUFF(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_BUFF_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_BUFF.jpg";

	//Draw Buffer Gate at Gfx_Info (14th Corner)
	//Set the Image Width & Height by BUFF Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.BUFF_Width, UI.BUFF_Height);
}

void Output::DrawLED(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_LED_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_LED.jpg";

	//Draw LED at Gfx_Info (15th Corner)
	//Set the Image Width & Height by LED Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.LED_Width, UI.LED_Height);
}

void Output::DrawLEDSIMU(GraphicsInfo r_GfxInfo, bool HIGH) const
{
	string GateImage;
	if (HIGH)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_LED_HIGH.jpg";
	else
		GateImage = "Images\\Gates\\Gate_LED.jpg";

	//Draw LED at Gfx_Info (15th Corner)
	//Set the Image Width & Height by LED Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.LED_Width, UI.LED_Height);
}

void Output::DrawSWITCH(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_SWITCH_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_SWITCH.jpg";

	//Draw SWITCH at Gfx_Info (16th Corner)
	//Set the Image Width & Height by SWITCH Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.SWITCH_Width, UI.SWITCH_Height);
}

void Output::DrawSWITCHSIM(GraphicsInfo r_GfxInfo, bool Status) const
{
	string GateImage;
	if (Status)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_SWITCH_HIGH.jpg";
	else
		GateImage = "Images\\Gates\\Gate_SWITCH.jpg";

	//Draw SWITCH at Gfx_Info (16th Corner)
	//Set the Image Width & Height by SWITCH Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.SWITCH_Width, UI.SWITCH_Height);
}

//TODO: Add similar functions to draw all components - DONE
//TODO: Add code to draw connection - DONE
void Output::DrawConnection(GraphicsInfo r_GfxInfo, int ClickedIndx, int **& CrnrArr, int & CrnrCount, bool iDragging, ApplicationManager *ipApp, int &DistPin, int ConnIndx, bool selected) const
{
	Component** CompList = ipApp->getCompList(); ConnectionCases cS;
	int CompSize = ipApp->getCompCount();
	setBuff(true);
	CrnrCount = 4;
	bool X;
	PrintMsg("Connection: Use dragging to connect the two gates.");
	int xStart = r_GfxInfo.x1, yStart = r_GfxInfo.y1; // Starting Coordinates of the line.
	int xAvg = r_GfxInfo.x1; // x Average will be needed while drawing.
	int xEndi = r_GfxInfo.x1, yEndi = r_GfxInfo.y1; // x and y next to previous values;
	int deltaX = 0, deltaY = 0; // The change in x and y with respect to the average x distance of xStart and xEnd.
	int xEnd = r_GfxInfo.x1, yEnd = r_GfxInfo.y1; // Ending Coordinates of the connection.
	char cKeyData = NO_KEYPRESS; // A variable for detecting the Escape press.
	for (int i = 0; i < 4; i++) {
		CrnrArr[i][0] = r_GfxInfo.x1;
		CrnrArr[i][1] = r_GfxInfo.y1;
	}
	ipApp->CheckDirectionConnection(cS, ClickedIndx, CrnrArr, r_GfxInfo, xAvg, DistPin, xStart, xEnd, xEndi, yEnd, yEndi, yStart, deltaX, deltaY);
	// Begining of dragging.
	while (pWind->GetKeyPress(cKeyData) != ESCAPE) {
		if (iDragging == false) {
			if (pWind->GetButtonState(LEFT_BUTTON, xEnd, yEnd) == BUTTON_DOWN) {
				if (xEnd != xEndi) {
					iDragging = true;
					deltaX = xEnd - xEndi;
				}
				else if (yEnd != yStart) {
					iDragging = true;
					deltaY = yEnd - yEndi;
				}
			}
		}

		if (iDragging) {
			if (pWind->GetButtonState(LEFT_BUTTON, xEnd, yEnd) == BUTTON_UP) {
				iDragging = false;
			}
			else if (yEnd > 82 && yEnd < 578 && xEnd > 22 && xEnd < 1760) {
				if (cS == SWTGATE || cS == GATEGATE || cS == GATELED || cS == AIRGATE) {
					if (xEnd != xEndi) {

						if (xEnd > xStart) {
							CrnrCount = 4;
							DrawCircleF(r_GfxInfo, ClickedIndx); // Drawing a small filled circle to indicate a branch.
							xAvg = (xStart + xEnd) / 2;
							pWind->SetPen(BLACK, 2);
							pWind->DrawLine(xStart, yStart, xAvg, yStart); CrnrArr[1][0] = xAvg; CrnrArr[1][1] = yStart;
							pWind->DrawLine(xAvg, yStart, xAvg, yEndi);  CrnrArr[2][0] = xAvg; CrnrArr[2][1] = yEndi;
							pWind->DrawLine(xAvg, yEndi, xEnd, yEndi);  CrnrArr[3][0] = xEnd; CrnrArr[3][1] = yEndi;
							xEndi = xEnd;
						}
						else if (xEnd < xStart) {
							if (xEnd < xEndi) {
								X = true;
								CrnrCount = 6;
								DrawCircleF(r_GfxInfo, ClickedIndx);
								xAvg = (xStart + xEnd) / 2;
								pWind->SetPen(BLACK, 2);
								pWind->DrawLine(xStart, yStart, xStart + 15, yStart); CrnrArr[1][0] = xStart + 15; CrnrArr[1][1] = yStart;
								pWind->DrawLine(xStart + 15, yStart, xStart + 15, yStart - 40);  CrnrArr[2][0] = xStart + 15; CrnrArr[2][1] = yStart - 40;
								pWind->DrawLine(xStart + 15, yStart - 40, xAvg, yStart - 40);  CrnrArr[3][0] = xAvg; CrnrArr[3][1] = yStart - 40;
								pWind->DrawLine(xAvg, yStart - 40, xAvg, yEndi);  CrnrArr[4][0] = xAvg; CrnrArr[4][1] = yEndi;
								pWind->DrawLine(xAvg, yEndi, xEnd, yEndi);  CrnrArr[5][0] = xEnd; CrnrArr[5][1] = yEndi;
								xEndi = xEnd;
								pWind->UpdateBuffer();
							}
							else if (xEnd > xEndi) {
								X = false;
								CrnrCount = 6;
								DrawCircleF(r_GfxInfo, ClickedIndx);
								pWind->SetPen(BLACK, 2);
								pWind->DrawLine(xStart, yStart, xStart + 15, yStart); CrnrArr[1][0] = xStart + 15; CrnrArr[1][1] = yStart;
								pWind->DrawLine(xStart + 15, yStart, xStart + 15, yStart - 40);  CrnrArr[2][0] = xStart + 15; CrnrArr[2][1] = yStart - 40;
								pWind->DrawLine(xStart + 15, yStart - 40, xEndi - 15, yStart - 40);  CrnrArr[3][0] = xEndi - 15; CrnrArr[3][1] = yStart - 40;
								pWind->DrawLine(xEndi - 15, yStart - 40, xEndi - 15, yEndi);  CrnrArr[4][0] = xEndi - 15; CrnrArr[4][1] = yEndi;
								pWind->DrawLine(xEndi - 15, yEndi, xEnd, yEndi);  CrnrArr[5][0] = xEnd; CrnrArr[5][1] = yEndi;
								xEndi = xEnd;
								pWind->UpdateBuffer();
							}
						}
					}
					pWind->GetButtonState(LEFT_BUTTON, xEnd, yEnd);
					if (yEnd > 82 && yEnd < 578 && xEnd > 22 && xEnd < 1760) {
						if (yEnd != yEndi) {
							if (xEnd > xStart && yEnd != yEndi) {
								CrnrCount = 4;
								DrawCircleF(r_GfxInfo, ClickedIndx);
								pWind->SetPen(BLACK, 2);
								pWind->DrawLine(xStart, yStart, xAvg, yStart); CrnrArr[1][0] = xAvg; CrnrArr[1][1] = yStart;
								pWind->DrawLine(xAvg, yStart, xAvg, yEnd); CrnrArr[2][0] = xAvg; CrnrArr[2][1] = yEnd;
								pWind->DrawLine(xAvg, yEnd, xEndi, yEnd); CrnrArr[3][0] = xEndi; CrnrArr[3][1] = yEnd;
								yEndi = yEnd;
							}
							else if (xEnd < xStart) {
								if (X) {
									CrnrCount = 6;
									DrawCircleF(r_GfxInfo, ClickedIndx);
									pWind->SetPen(BLACK, 2);
									xAvg = (xStart + xEnd) / 2;
									pWind->DrawLine(xStart, yStart, xStart + 15, yStart); CrnrArr[1][0] = xStart + 15; CrnrArr[1][1] = yStart;
									pWind->DrawLine(xStart + 15, yStart, xStart + 15, yStart - 40);  CrnrArr[2][0] = xStart + 15; CrnrArr[2][1] = yStart - 40;
									pWind->DrawLine(xStart + 15, yStart - 40, xAvg, yStart - 40);  CrnrArr[3][0] = xAvg; CrnrArr[3][1] = yStart - 40;
									pWind->DrawLine(xAvg, yStart - 40, xAvg, yEnd);  CrnrArr[4][0] = xAvg; CrnrArr[4][1] = yEnd;
									pWind->DrawLine(xAvg, yEnd, xEndi, yEnd);  CrnrArr[5][0] = xEndi; CrnrArr[5][1] = yEnd;
									yEndi = yEnd;
									pWind->UpdateBuffer();
								}
								else if (!X) {
									CrnrCount = 6;
									DrawCircleF(r_GfxInfo, ClickedIndx);
									pWind->SetPen(BLACK, 2);
									pWind->DrawLine(xStart, yStart, xStart + 15, yStart); CrnrArr[1][0] = xStart + 15; CrnrArr[1][1] = yStart;
									pWind->DrawLine(xStart + 15, yStart, xStart + 15, yStart - 40);  CrnrArr[2][0] = xStart + 15; CrnrArr[2][1] = yStart - 40;
									pWind->DrawLine(xStart + 15, yStart - 40, xEndi - 15, yStart - 40);  CrnrArr[3][0] = xEndi - 15; CrnrArr[3][1] = yStart - 40;
									pWind->DrawLine(xEndi - 15, yStart - 40, xEndi - 15, yEnd);  CrnrArr[4][0] = xEndi - 15; CrnrArr[4][1] = yEnd;
									pWind->DrawLine(xEndi - 15, yEnd, xEndi, yEnd);  CrnrArr[5][0] = xEndi; CrnrArr[5][1] = yEnd;
									yEndi = yEnd;
									pWind->UpdateBuffer();
								}
							}
						}
					}
				}
				else {
					if (xEnd != xEndi) {
						CrnrCount = 4;
						DrawCircleF(r_GfxInfo, ClickedIndx);
						xAvg = (xStart + xEnd) / 2;
						pWind->SetPen(BLACK, 2);
						pWind->DrawLine(xStart, yStart, xAvg, yStart); CrnrArr[1][0] = xAvg; CrnrArr[1][1] = yStart;
						pWind->DrawLine(xAvg, yStart, xAvg, yEndi);  CrnrArr[2][0] = xAvg; CrnrArr[2][1] = yEndi;
						pWind->DrawLine(xAvg, yEndi, xEnd, yEndi);  CrnrArr[3][0] = xEnd; CrnrArr[3][1] = yEndi;
						xEndi = xEnd;
					}
					pWind->GetButtonState(LEFT_BUTTON, xEnd, yEnd);
					if (yEnd > 82 && yEnd < 578 && xEnd > 22 && xEnd < 1760) {
						if (yEnd != yEndi) {
							CrnrCount = 4;
							if (yEnd > 82 && yEnd < 578 && xEnd > 22 && xEnd < 1760) {
								pWind->SetPen(BLACK, 2);
								pWind->DrawLine(xStart, yStart, xAvg, yStart); CrnrArr[1][0] = xAvg; CrnrArr[1][1] = yStart;
								pWind->DrawLine(xAvg, yStart, xAvg, yEnd); CrnrArr[2][0] = xAvg; CrnrArr[2][1] = yEnd;
								pWind->DrawLine(xAvg, yEnd, xEndi, yEnd); CrnrArr[3][0] = xEndi; CrnrArr[3][1] = yEnd;
								yEndi = yEnd;
							}
						}
					}
				}
			}
		}
		ipApp->UpdateIntra();
		pWind->UpdateBuffer();
	}

	int ClickedIndx2 = -1; // The source gate's Index which is passed by reference to indicate whether the user linked this connection to a distination gate or not. Initialized to -1 as start.
	GraphicsInfo GrfInfo; GrfInfo.x1 = xEndi; GrfInfo.y1 = yEndi;
	ClickedIndx2 = ipApp->ClickedIndxMove(GrfInfo);

	// This step is mainly to check the input pin the user has chosen. And directs the connection to it for more pleasant sketch. Also return the order of the pin, might be 1st or 2nd or the 3rd pin.
	if (ConnIndx == -1) {
		((Connection*)(ipApp->getCompList()[ipApp->getCompCount() - 1]))->AdjustCrnrArr(cS, ClickedIndx2, DistPin, CrnrArr, CrnrCount, pWind);
		((Connection*)(ipApp->getCompList()[ipApp->getCompCount() - 1]))->AdjustSrcDst(cS, ClickedIndx, ClickedIndx2, DistPin, GrfInfo);
	}
	else {
		((Connection*)(ipApp->getCompList()[ConnIndx]))->AdjustCrnrArr(cS, ClickedIndx2, DistPin, CrnrArr, CrnrCount, pWind);
		((Connection*)(ipApp->getCompList()[ConnIndx]))->AdjustSrcDst(cS, ClickedIndx, ClickedIndx2, DistPin, GrfInfo, ConnIndx);
	}
	setBuff(false);
}

//kdone 5-3-16 con everywhere from gate or no gate broken straight with add conn

Output::~Output()
{
	delete[]MenuItemImages;
	delete pWind;
}
