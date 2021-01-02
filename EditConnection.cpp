#include "editConnection.h"
#include "ApplicationManager.h"

EditConnection::EditConnection(ApplicationManager * pApp, ActionType type) :Action(pApp, type)
{
	PrevCrnrArr = new int*[6];
	for (int i = 0; i < 6; i++) {
		PrevCrnrArr[i] = new int[2];
	}
}

void EditConnection::ReadActionParameters()
{
	int xCoord, yCoord; GraphicsInfo GInfo;

	pManager->GetOutput()->PrintMsg("Edit connection: Please select a specific connection you want to edit.");
	pManager->GetInput()->GetPointClicked(xCoord, yCoord);
	GInfo.x1 = xCoord; GInfo.y1 = yCoord;

	IndexClicked = pManager->ClickedIndx(GInfo);

	if (IndexClicked == -1 || pManager->getCompList()[IndexClicked]->GetCompType() != iCONNECTION) {
		pManager->GetOutput()->PrintMsg("Edit connection: You didn't select a Connection.");
	}
}

void EditConnection::Execute()
{
	ReadActionParameters();
	GraphicsInfo GInfo;
	if (IndexClicked == -1 || pManager->getCompList()[IndexClicked]->GetCompType() != iCONNECTION) {
		pManager->GetOutput()->PrintMsg("Edit connection: You didn't select a Connection.");
		return;
	}
	SrcGate = ((Connection*)(pManager->getCompList()[IndexClicked]))->getSrcGate();
	DstGate = ((Connection*)(pManager->getCompList()[IndexClicked]))->getDestGate();
	OutPin = ((Connection*)(pManager->getCompList()[IndexClicked]))->getSourcePin();
	InPin = ((Connection*)(pManager->getCompList()[IndexClicked]))->getDestPin();
	GInfoz.x1 = ((Connection*)(pManager->getCompList()[IndexClicked]))->getGfxInfo().x1, GInfoz.y1 = ((Connection*)(pManager->getCompList()[IndexClicked]))->getGfxInfo().y1;
	GInfoz.x2 = ((Connection*)(pManager->getCompList()[IndexClicked]))->getGfxInfo().x2, GInfoz.y2 = ((Connection*)(pManager->getCompList()[IndexClicked]))->getGfxInfo().y2;
	int **CrnrArr = new int*[6]; int CrnrCount;
	for (int i = 0; i < 6; i++) {
		CrnrArr[i] = new int[2];
	}
	CrnrArr = ((Connection*)(pManager->getCompList()[IndexClicked]))->getCrnrArr();
	for (int i = 0; i < 6; i++) {
		PrevCrnrArr[i][1] = ((Connection*)(pManager->getCompList()[IndexClicked]))->getCrnrArr()[i][1];
		PrevCrnrArr[i][0] = ((Connection*)(pManager->getCompList()[IndexClicked]))->getCrnrArr()[i][0];
	}
	((Connection*)(pManager->getCompList()[IndexClicked]))->setSEL();
	((Connection*)(pManager->getCompList()[IndexClicked]))->Draw(pManager->GetOutput());
	((Connection*)(pManager->getCompList()[IndexClicked]))->setDstGate(NULL);
	((Connection*)(pManager->getCompList()[IndexClicked]))->setDestPin(NULL);
	((Connection*)(pManager->getCompList()[IndexClicked]))->getSrcGate()->getOutPin()->DisconnectFrom(((Connection*)(pManager->getCompList()[IndexClicked])));
	((Connection*)(pManager->getCompList()[IndexClicked]))->setSrcGate(NULL);
	((Connection*)(pManager->getCompList()[IndexClicked]))->setSourcePin(NULL);
	pManager->GetOutput()->PrintMsg("Edit connection: Start drawing the new connection.");

	int iXn, iYn;
	while (pManager->GetOutput()->getWindow()->GetButtonState(LEFT_BUTTON, iXn, iYn) == BUTTON_UP || !(Cy1 > 82 && Cy1 < 578 && Cx1 > 22 && Cx1 < 1760)) {
		pManager->GetOutput()->getWindow()->GetMouseCoord(Cx1, Cy1);
	}

	GInfo.x1 = Cx1; GInfo.y1 = Cy1;
	bool iDragging = false;
	int ClickedIndex = pManager->ClickedIndx(GInfo);
	int iDst;
	pManager->GetOutput()->DrawConnection(GInfo, ClickedIndex, CrnrArr, CrnrCount, iDragging, pManager, iDst, IndexClicked);
	((Connection*)(pManager->getCompList()[IndexClicked]))->setDestPinNum(iDst);
	((Connection*)(pManager->getCompList()[IndexClicked]))->deSEL();
	bool Check = false;
	Check = pManager->CheckErrorConnection(((Connection*)(pManager->getCompList()[IndexClicked])), IndexClicked);
	if (!Check) {
		pManager->GetOutput()->PrintMsg("Edit connection: Done.");
		((Connection*)(pManager->getCompList()[IndexClicked]))->AdjstGrfxInfo();
		((Connection*)(pManager->getCompList()[IndexClicked]))->setTempCrnrArr();
		pManager->CreateAction(this);
		pManager->getUndoedActions()->EmptyStack();
	}
	else {
		((Connection*)(pManager->getCompList()[IndexClicked]))->setDstGate(DstGate);
		((Connection*)(pManager->getCompList()[IndexClicked]))->setDestPin(InPin);
		((Connection*)(pManager->getCompList()[IndexClicked]))->setSrcGate(SrcGate);
		((Connection*)(pManager->getCompList()[IndexClicked]))->setSourcePin(OutPin);
		((Connection*)(pManager->getCompList()[IndexClicked]))->getSrcGate()->getOutPin()->ConnectTo(((Connection*)(pManager->getCompList()[IndexClicked])));
		((Connection*)(pManager->getCompList()[IndexClicked]))->setCrnrArr(((Connection*)(pManager->getCompList()[IndexClicked]))->getTempCrnrArr());
	}
	pManager->GetOutput()->ClearDrawingArea();
}

void EditConnection::Undo()
{
	Component*SrcGates= ((Connection*)(pManager->getCompList()[IndexClicked]))->getSrcGate();
	Component*DstGates= ((Connection*)(pManager->getCompList()[IndexClicked]))->getDestGate();
	InputPin*Inp = ((Connection*)(pManager->getCompList()[IndexClicked]))->getInpPin();
	OutputPin*Outs= ((Connection*)(pManager->getCompList()[IndexClicked]))->getSourcePin();
	GraphicsInfo GInfos;
	GInfos.x1 = ((Connection*)(pManager->getCompList()[IndexClicked]))->getGfxInfo().x1, GInfos.y1 = ((Connection*)(pManager->getCompList()[IndexClicked]))->getGfxInfo().y1;
	GInfos.x2 = ((Connection*)(pManager->getCompList()[IndexClicked]))->getGfxInfo().x2, GInfos.y2 = ((Connection*)(pManager->getCompList()[IndexClicked]))->getGfxInfo().y2;
	int ** Crnrs = new int*[6];
	for (int i = 0; i < 6; i++) {
		Crnrs[i] = new int[2];
	}
	for (int i = 0; i < 6; i++) {
		Crnrs[i][1] = ((Connection*)(pManager->getCompList()[IndexClicked]))->getCrnrArr()[i][1];
		Crnrs[i][0] = ((Connection*)(pManager->getCompList()[IndexClicked]))->getCrnrArr()[i][0];
	}
	((Connection*)(pManager->getCompList()[IndexClicked]))->getSrcGate()->getOutPin()->DisconnectFrom(((Connection*)(pManager->getCompList()[IndexClicked])));
	((Connection*)(pManager->getCompList()[IndexClicked]))->setDstGate(DstGate);
	((Connection*)(pManager->getCompList()[IndexClicked]))->setDestPin(InPin);
	((Connection*)(pManager->getCompList()[IndexClicked]))->setSrcGate(SrcGate);
	((Connection*)(pManager->getCompList()[IndexClicked]))->setSourcePin(OutPin);
	((Connection*)(pManager->getCompList()[IndexClicked]))->getSrcGate()->getOutPin()->ConnectTo(((Connection*)(pManager->getCompList()[IndexClicked])));
	((Connection*)(pManager->getCompList()[IndexClicked]))->setCrnrArr(PrevCrnrArr);
	((Connection*)(pManager->getCompList()[IndexClicked]))->setGfxInfo(GInfoz);
	for (int i = 0; i < 6; i++) {
		PrevCrnrArr[i][1] = Crnrs[i][1];
		PrevCrnrArr[i][0] = Crnrs[i][0];
	}
	SrcGate = SrcGates;
	DstGate = DstGates;
	InPin = Inp;
	OutPin = Outs;
	GInfoz.x1 = GInfos.x1, GInfoz.y1 = GInfos.y1;
	GInfoz.x2 = GInfos.x2, GInfoz.y2 = GInfos.y2;
	for (int i = 0; i < 6; i++) {
		delete Crnrs[i];
	}
	delete[]Crnrs;
	pManager->GetOutput()->ClearDrawingArea();
}

void EditConnection::Redo()
{
	Component*SrcGates = ((Connection*)(pManager->getCompList()[IndexClicked]))->getSrcGate();
	Component*DstGates = ((Connection*)(pManager->getCompList()[IndexClicked]))->getDestGate();
	InputPin*Inp = ((Connection*)(pManager->getCompList()[IndexClicked]))->getInpPin();
	OutputPin*Outs = ((Connection*)(pManager->getCompList()[IndexClicked]))->getSourcePin();
	GraphicsInfo GInfos;
	GInfos.x1 = ((Connection*)(pManager->getCompList()[IndexClicked]))->getGfxInfo().x1, GInfos.y1 = ((Connection*)(pManager->getCompList()[IndexClicked]))->getGfxInfo().y1;
	GInfos.x2 = ((Connection*)(pManager->getCompList()[IndexClicked]))->getGfxInfo().x2, GInfos.y2 = ((Connection*)(pManager->getCompList()[IndexClicked]))->getGfxInfo().y2;
	int ** Crnrs = new int*[6];
	for (int i = 0; i < 6; i++) {
		Crnrs[i] = new int[2];
	}
	for (int i = 0; i < 6; i++) {
		Crnrs[i][1] = ((Connection*)(pManager->getCompList()[IndexClicked]))->getCrnrArr()[i][1];
		Crnrs[i][0] = ((Connection*)(pManager->getCompList()[IndexClicked]))->getCrnrArr()[i][0];
	}
	((Connection*)(pManager->getCompList()[IndexClicked]))->getSrcGate()->getOutPin()->DisconnectFrom(((Connection*)(pManager->getCompList()[IndexClicked])));
	((Connection*)(pManager->getCompList()[IndexClicked]))->setDstGate(DstGate);
	((Connection*)(pManager->getCompList()[IndexClicked]))->setDestPin(InPin);
	((Connection*)(pManager->getCompList()[IndexClicked]))->setSrcGate(SrcGate);
	((Connection*)(pManager->getCompList()[IndexClicked]))->setSourcePin(OutPin);
	((Connection*)(pManager->getCompList()[IndexClicked]))->getSrcGate()->getOutPin()->ConnectTo(((Connection*)(pManager->getCompList()[IndexClicked])));
	((Connection*)(pManager->getCompList()[IndexClicked]))->setCrnrArr(PrevCrnrArr);
	((Connection*)(pManager->getCompList()[IndexClicked]))->setGfxInfo(GInfoz);
	for (int i = 0; i < 6; i++) {
		PrevCrnrArr[i][1] = Crnrs[i][1];
		PrevCrnrArr[i][0] = Crnrs[i][0];
	}
	SrcGate = SrcGates;
	DstGate = DstGates;
	InPin = Inp;
	OutPin = Outs;
	GInfoz.x1 = GInfos.x1, GInfoz.y1 = GInfos.y1;
	GInfoz.x2 = GInfos.x2, GInfoz.y2 = GInfos.y2;

	for (int i = 0; i < 6; i++) {
		delete Crnrs[i];
	}
	delete[]Crnrs;
	pManager->GetOutput()->ClearDrawingArea();
}

EditConnection::~EditConnection()
{
}
