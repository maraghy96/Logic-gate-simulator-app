#include "editConnection.h"
#include "ApplicationManager.h"

EditConnection::EditConnection(ApplicationManager * pApp, ActionType type):Action(pApp,type)
{
}

void EditConnection::ReadActionParameters()
{
	Output *pOut = pManager->GetOutput();
	window *pWind = pOut->getWindow();
	Input *pIn = pManager->GetInput();
	Component** CompList = pManager->getCompList();
	int xCoord, yCoord, CompCount = pManager->getCompCount();
	GraphicsInfo GInfo;

	pOut->PrintMsg("Edit connection: Please select a specific connection you want to edit.");
	pIn->GetPointClicked(xCoord, yCoord);
	GInfo.x1 = xCoord; GInfo.y1 = yCoord;

	IndexClicked = pManager->ClickedIndx(CompList, CompCount, GInfo);
	if (IndexClicked == -1 || CompList[IndexClicked]->GetCompType() != iCONNECTION) {
		pOut->PrintMsg("Edit connection: You didn't select a Connection.");
	}
}

void EditConnection::Execute()
{
	ReadActionParameters();
	Output *pOut = pManager->GetOutput();
	Component** CompList = pManager->getCompList(); 
	int CompCount = pManager->getCompCount();
	GraphicsInfo GInfo;

	if (IndexClicked == -1) {
		return;
	}

	int **CrnrArr = new int*[6]; int CrnrCount;
	for (int i = 0; i < 6; i++) {
		CrnrArr[i] = new int[2];
	}
	CrnrArr = ((Connection*)CompList[IndexClicked])->getCrnrArr();
	
	CompList[IndexClicked]->setSEL();
	((Connection*)CompList[IndexClicked])->Draw(pOut);

	pOut->PrintMsg("Edit connection: Start drawing the new connection.");

	int iXn, iYn;
	while (pOut->getWindow()->GetButtonState(LEFT_BUTTON, iXn, iYn) == BUTTON_UP || !(Cy1 > 82 && Cy1 < 578 && Cx1 > 22 && Cx1 < 1760)){
		pOut->getWindow()->GetMouseCoord(Cx1, Cy1);
	}

	GInfo.x1 = Cx1; GInfo.y1 = Cy1;
	int DistPin;
	int ClickedIndex = pManager->ClickedIndx(CompList, CompCount, GInfo); int ClickedIndex2;
	pOut->DrawConnection(GInfo, CompList, CompCount, ClickedIndex, ClickedIndex2, CrnrArr, CrnrCount, DistPin, false, pManager);
	((Connection*)CompList[IndexClicked])->setCrnrCount(CrnrCount);
	((Connection*)CompList[IndexClicked])->setCrnrArr(CrnrArr);
	if (ClickedIndex != -1) {
		((Connection*)CompList[IndexClicked])->setSrcGate(CompList[ClickedIndex]);
		((Connection*)CompList[IndexClicked])->setSourcePin(((Gate*)CompList[ClickedIndex])->getOutPin());
	}
	else {
		((Connection*)CompList[IndexClicked])->setSrcGate(NULL);
		((Connection*)CompList[IndexClicked])->setSourcePin(NULL);
	}

	if (ClickedIndex2 != -1) {
		((Connection*)CompList[IndexClicked])->setDstGate(CompList[ClickedIndex2]);
		((Connection*)CompList[IndexClicked])->setDestPin(&((Gate*)CompList[ClickedIndex2])->getInpPin()[DistPin - 1]);
	}
	else {
		((Connection*)CompList[IndexClicked])->setDstGate(NULL);
		((Connection*)CompList[IndexClicked])->setDestPin(NULL);
	}
	((Connection*)CompList[IndexClicked])->deSEL();
	pOut->PrintMsg("Edit connection: Done.");
	pOut->ClearDrawingArea();
}

void EditConnection::Undo()
{
}

void EditConnection::Redo()
{
}

EditConnection::~EditConnection()
{
}
