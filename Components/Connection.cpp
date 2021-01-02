#include "Connection.h"
#include "../ApplicationManager.h"


void Connection::setSourcePin(OutputPin *pSrcPin)
{
	SrcPin = pSrcPin;
}

OutputPin* Connection::getSourcePin()
{
	return SrcPin;
}


void Connection::setDestPin(InputPin *pDstPin)
{
	DstPin = pDstPin;
}

void Connection::setSrcGate(Component * pSrcGate)
{
	SrcCmpnt = pSrcGate;
}

void Connection::setDstGate(Component * pDistGate)
{
	DstCmpnt = pDistGate;
}

void Connection::setCrnrArr(int ** iCrnrArr)
{
	for (int i = 0; i < NumCorners; i++) {
		CrnrArr[i][0] = iCrnrArr[i][0];
		CrnrArr[i][1] = iCrnrArr[i][1];
	}
}

void Connection::setCrnrCount(int Count)
{
	NumCorners = Count;
}

InputPin* Connection::getDestPin()
{
	return DstPin;
}

Component * Connection::getSrcGate()
{
	return SrcCmpnt;
}

Component * Connection::getDestGate()
{
	return DstCmpnt;
}

int Connection::getDestPinNum()
{
	return DestPinNum;
}

void Connection::setDestPinNum(int iDst)
{
	DestPinNum = iDst;
}

int Connection::getCrnrCount() {
	return NumCorners;
}

int Connection::getSrcCompID() const
{
	return SrcCompID;
}

int Connection::getDstCompID() const
{
	return DstCompID;
}

InputPin * Connection::getInpPin()
{
	return nullptr;
}

int** Connection::getCrnrArr() {
	return CrnrArr;
}



Connection::Connection(const GraphicsInfo & r_GfxInfo, ApplicationManager * ipApp, Component * pS, int Pin)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	pApp = ipApp;
	SEL = false;
	SrcPin = NULL;
	DstPin = NULL;
	SrcCmpnt = pS;
	DstCmpnt = NULL;
	NumCorners = 0;
	Type = iCONNECTION;
	CrnrArr = new int*[8];
	TempCrnrArr = new int*[8];
	for (int i = 0; i < 8; i++) {
		CrnrArr[i] = new int[2];
		TempCrnrArr[i] = new int[2];
	}
}

Connection::Connection(ApplicationManager * ptr)
{
	SEL = false;
	Type = iCONNECTION;
	pApp = ptr;
}

Connection::~Connection() {
	for (int i = 0; i < 8; i++) {
		delete CrnrArr[i];
		delete TempCrnrArr[i];
	}
	delete[] TempCrnrArr;
	delete[] CrnrArr;
}

void Connection::Operate()
{
	//Status of connection destination pin = status of connection source pin
	DstPin->setStatus((STATUS)SrcPin->getStatus());
	Operated = true;

}

void Connection::setTempCrnrArr() {
	for (int i = 0; i < NumCorners; i++) {
		TempCrnrArr[i][0] = CrnrArr[i][0];
		TempCrnrArr[i][1] = CrnrArr[i][1];
	}
}

void Connection::Draws(Output* pOut)
{
	int ClickedIndx = pApp->ClickedIndx(m_GfxInfo);
	bool iDragging = false;
	pOut->DrawConnection(m_GfxInfo, ClickedIndx, CrnrArr, NumCorners, iDragging, pApp, DestPinNum);
	AdjstGrfxInfo();
	setTempCrnrArr();
	pOut->PrintMsg("Connection: Done.");
}

void Connection::AdjstGrfxInfo() {
	m_GfxInfo.x1 = CrnrArr[0][0];
	m_GfxInfo.y1 = CrnrArr[0][1] + 18;
	m_GfxInfo.x2 = CrnrArr[1][0];
	m_GfxInfo.y2 = CrnrArr[1][1] + 18;
}

int** Connection::getTempCrnrArr() {
	return TempCrnrArr;
}

void Connection::DrawError(Output * pOut)
{
	for (int i = 0; i < NumCorners - 1; i++) {
		if (NumCorners == 4 && i == 3) {
			continue;
		}
		if (i == 0) {
			Component*SrcCmp = SrcCmpnt;
			if (SrcCmpnt != NULL && CrnrArr[0][0] != SrcCmpnt->getGfxInfo().x2 && CrnrArr[0][1] != SrcCmpnt->getGfxInfo().y2 - 20) {
				pOut->getWindow()->SetPen(WHITE, 2);
				pOut->getWindow()->SetBrush(WHITE);
				pOut->getWindow()->DrawCircle(CrnrArr[i][0], CrnrArr[i][1], 3, FILLED);
				pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
			}
			else if (SrcCmp != NULL  && CrnrArr[0][0] == SrcCmpnt->getGfxInfo().x2 && CrnrArr[0][1] == SrcCmpnt->getGfxInfo().y2 - 20) {
				pOut->getWindow()->SetPen(WHITE, 2);
				pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
			}
			else {
				pOut->getWindow()->SetPen(WHITE, 2);
				pOut->getWindow()->SetBrush(WHITE);
				pOut->getWindow()->DrawCircle(CrnrArr[i][0], CrnrArr[i][1], 3, FILLED);
				pOut->getWindow()->SetPen(WHITE, 2);
				pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
			}
		}
		else {
			pOut->getWindow()->SetPen(WHITE, 2);
			pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
		}
	}
}

void Connection::Draw(Output* pOut)
{
	if (!SEL) {
		for (int i = 0; i < NumCorners - 1; i++) {
			if (NumCorners == 4 && i == 3) {
				continue;
			}
			if (i == 0) {
				Component*SrcCmp = SrcCmpnt;
				if ((SrcCmpnt != NULL && (CrnrArr[0][0] != SrcCmpnt->getGfxInfo().x2 && CrnrArr[0][0] != SrcCmpnt->getGfxInfo().x1))) {
					pOut->getWindow()->SetPen(BLACK, 2);
					pOut->getWindow()->SetBrush(BLACK);
					pOut->getWindow()->DrawCircle(CrnrArr[i][0], CrnrArr[i][1], 3, FILLED);
					pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
				}
				else if (SrcCmp != NULL  && CrnrArr[0][0] == SrcCmpnt->getGfxInfo().x2 && CrnrArr[0][1] == SrcCmpnt->getGfxInfo().y2 - 20) {
					pOut->getWindow()->SetPen(BLACK, 2);
					pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
				}
				else {
					pOut->getWindow()->SetPen(BLACK, 2);
					pOut->getWindow()->SetBrush(BLACK);
					pOut->getWindow()->DrawCircle(CrnrArr[i][0], CrnrArr[i][1], 3, FILLED);
					pOut->getWindow()->SetPen(BLACK, 2);
					pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
				}
			}
			else {
				pOut->getWindow()->SetPen(BLACK, 2);
				pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
			}
		}
	}
	else {
		for (int i = 0; i < NumCorners - 1; i++) {
			if (NumCorners == 4 && i == 3) {
				continue;
			}
			if (i == 0) {
				Component*SrcCmp = SrcCmpnt;
				if (SrcCmpnt != NULL && CrnrArr[0][0] != SrcCmpnt->getGfxInfo().x2 && CrnrArr[0][1] != SrcCmpnt->getGfxInfo().y2 - 20) {
					pOut->getWindow()->SetPen(BLUE, 2);
					pOut->getWindow()->SetBrush(BLUE);
					pOut->getWindow()->DrawCircle(CrnrArr[i][0], CrnrArr[i][1], 3, FILLED);
					pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
				}
				else if (SrcCmp != NULL  && CrnrArr[0][0] == SrcCmpnt->getGfxInfo().x2 && CrnrArr[0][1] == SrcCmpnt->getGfxInfo().y2 - 20) {
					pOut->getWindow()->SetPen(BLUE, 2);
					pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
				}
				else {
					pOut->getWindow()->SetPen(BLUE, 2);
					pOut->getWindow()->SetBrush(BLUE);
					pOut->getWindow()->DrawCircle(CrnrArr[i][0], CrnrArr[i][1], 3, FILLED);
					pOut->getWindow()->SetPen(BLUE, 2);
					pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
				}
			}
			else {
				pOut->getWindow()->SetPen(BLUE, 2);
				pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
			}
		}
	}
	pOut->DrawLabel(getCompLabel(), m_GfxInfo);
}

void Connection::DrawHi(Output * pOut)
{
	if (GetOutPinStatus() == HIGH) {
		for (int i = 0; i < NumCorners - 1; i++) {
			if (NumCorners == 4 && i == 3) {
				continue;
			}
			if (i == 0) {
				Component*SrcCmp = SrcCmpnt;
				if ((SrcCmpnt != NULL && (CrnrArr[0][0] != SrcCmpnt->getGfxInfo().x2 && CrnrArr[0][0] != SrcCmpnt->getGfxInfo().x1))) {
					pOut->getWindow()->SetPen(GREENYELLOW, 2);
					pOut->getWindow()->SetBrush(GREENYELLOW);
					pOut->getWindow()->DrawCircle(CrnrArr[i][0], CrnrArr[i][1], 3, FILLED);
					pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
				}
				else if (SrcCmp != NULL  && CrnrArr[0][0] == SrcCmpnt->getGfxInfo().x2 && CrnrArr[0][1] == SrcCmpnt->getGfxInfo().y2 - 20) {
					pOut->getWindow()->SetPen(GREENYELLOW, 2);
					pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
				}
				else {
					pOut->getWindow()->SetPen(GREENYELLOW, 2);
					pOut->getWindow()->SetBrush(GREENYELLOW);
					pOut->getWindow()->DrawCircle(CrnrArr[i][0], CrnrArr[i][1], 3, FILLED);
					pOut->getWindow()->SetPen(GREENYELLOW, 2);
					pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
				}
			}
			else {
				pOut->getWindow()->SetPen(GREENYELLOW, 2);
				pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
			}
		}
	}
	else
	{
		for (int i = 0; i < NumCorners - 1; i++) {
			if (NumCorners == 4 && i == 3) {
				continue;
			}
			if (i == 0) {
				Component*SrcCmp = SrcCmpnt;
				if (SrcCmpnt != NULL && CrnrArr[0][0] != SrcCmpnt->getGfxInfo().x2 && CrnrArr[0][1] != SrcCmpnt->getGfxInfo().y2 - 20) {
					pOut->getWindow()->SetPen(DARKGREEN, 2);
					pOut->getWindow()->SetBrush(DARKGREEN);
					pOut->getWindow()->DrawCircle(CrnrArr[i][0], CrnrArr[i][1], 3, FILLED);
					pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
				}
				else if (SrcCmp != NULL  && CrnrArr[0][0] == SrcCmpnt->getGfxInfo().x2 && CrnrArr[0][1] == SrcCmpnt->getGfxInfo().y2 - 20) {
					pOut->getWindow()->SetPen(DARKGREEN, 2);
					pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
				}
				else {
					pOut->getWindow()->SetPen(DARKGREEN, 2);
					pOut->getWindow()->SetBrush(DARKGREEN);
					pOut->getWindow()->DrawCircle(CrnrArr[i][0], CrnrArr[i][1], 3, FILLED);
					pOut->getWindow()->SetPen(DARKGREEN, 2);
					pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
				}
			}
			else {
				pOut->getWindow()->SetPen(DARKGREEN, 2);
				pOut->getWindow()->DrawLine(CrnrArr[i][0], CrnrArr[i][1], CrnrArr[i + 1][0], CrnrArr[i + 1][1]);
			}
		}
	}
	pOut->DrawLabel(getCompLabel(), m_GfxInfo);
}


int Connection::GetOutPinStatus()	//returns status of outputpin if LED, return -1
{
	return SrcPin->getStatus();
}

void Connection::setSEL() {
	SEL = true;
}

void Connection::deSEL() {
	SEL = false;
}


int Connection::GetInputPinStatus(int n)	//returns status of Inputpin # n if SWITCH, return -1
{
	return SrcPin->getStatus();	//n is ignored as connection has only one input pin (src pin)	
}

void Connection::setInputPinStatus(int n, STATUS s)
{
	SrcPin->setStatus(s);
}

CompType Connection::GetCompType() const
{
	return Type;
}

void Connection::Save(ofstream & output_f)
{
	output_f << Type << "\t" << SrcCmpnt->getID() << "\t" << DstCmpnt->getID() << "\t" << DestPinNum << "\t" << NumCorners << "\t";
	for (int i = 0; i < NumCorners; i++)
	{
		output_f << CrnrArr[i][0] << "\t" << CrnrArr[i][1] << "\t";
	}
	output_f << endl;
}

void Connection::Load(ifstream& output_f, Output* pOut)
{
	int SrcID, DestID;
	output_f >> SrcID >> DestID >> DestPinNum >> NumCorners;
	SrcCmpnt = pApp->getCompList()[pApp->IDForWhichComp(SrcID)];
	DstCmpnt = pApp->getCompList()[pApp->IDForWhichComp(DestID)];
	SrcPin = (SrcCmpnt)->getOutPin();
	DstPin = &(DstCmpnt)->getInpPin()[DestPinNum - 1];
	SrcCompID = SrcID;
	DstCompID = DestID;
	CrnrArr = new int*[NumCorners];
	TempCrnrArr = new int*[NumCorners];
	for (int i = 0; i < NumCorners; i++)
	{
		CrnrArr[i] = new int[2];
		TempCrnrArr[i] = new int[2];
		output_f >> CrnrArr[i][0] >> CrnrArr[i][1];
	}
	this->setTempCrnrArr();
	SrcPin->ConnectTo(this);

}

Component * Connection::Copy()
{
	return nullptr;
}

OutputPin *Connection::getOutPin()
{
	return nullptr;
}

void Connection::AdjustSrcDst(ConnectionCases cS, int Index1, int Index2, int DstPin, GraphicsInfo GInfo, int ConnectionIndx) {
	if (ConnectionIndx == -1) {
		if (Index1 != -1 && Index2 != -1) {
			if (cS == GATEGATE || cS == AIRGATE) {
				if (cS == GATEGATE) {
					((Connection*)pApp->getCompList()[pApp->getCompCount() - 1])->setSrcGate(pApp->getCompList()[Index1]);
					((Connection*)pApp->getCompList()[pApp->getCompCount() - 1])->setDstGate(pApp->getCompList()[Index2]);
					((Connection*)pApp->getCompList()[pApp->getCompCount() - 1])->setDestPin(&(pApp->getCompList()[Index2]->getInpPin()[DstPin - 1]));
					((Connection*)pApp->getCompList()[pApp->getCompCount() - 1])->setSourcePin(pApp->getCompList()[Index1]->getOutPin());
					pApp->getCompList()[Index1]->getOutPin()->ConnectTo((Connection*)pApp->getCompList()[pApp->getCompCount() - 1]);
				}
				else {
					((Connection*)pApp->getCompList()[pApp->getCompCount() - 1])->setSrcGate(((Connection*)pApp->getCompList()[Index1])->getSrcGate());
					((Connection*)pApp->getCompList()[pApp->getCompCount() - 1])->setDstGate(pApp->getCompList()[Index2]);
					((Connection*)pApp->getCompList()[pApp->getCompCount() - 1])->setDestPin(&(pApp->getCompList()[Index2]->getInpPin()[DstPin - 1]));
					((Connection*)pApp->getCompList()[pApp->getCompCount() - 1])->setSourcePin(((Connection*)pApp->getCompList()[Index1])->getSrcGate()->getOutPin());
					((Connection*)pApp->getCompList()[Index1])->getSrcGate()->getOutPin()->ConnectTo((Connection*)pApp->getCompList()[pApp->getCompCount() - 1]);
				}
			}
			else if (cS == rGATEGATE) {
				((Connection*)pApp->getCompList()[pApp->getCompCount() - 1])->setSrcGate(pApp->getCompList()[Index2]);
				((Connection*)pApp->getCompList()[pApp->getCompCount() - 1])->setDstGate(pApp->getCompList()[Index1]);
				((Connection*)pApp->getCompList()[pApp->getCompCount() - 1])->setDestPin(&(pApp->getCompList()[Index1]->getInpPin()[DstPin - 1]));
				((Connection*)pApp->getCompList()[pApp->getCompCount() - 1])->setSourcePin(pApp->getCompList()[Index2]->getOutPin());
				pApp->getCompList()[Index2]->getOutPin()->ConnectTo((Connection*)pApp->getCompList()[pApp->getCompCount() - 1]);
			}
		}
	}
	else if (ConnectionIndx != -1) {
		if (Index1 != -1 && Index2 != -1) {
			if (cS == GATEGATE) {
				((Connection*)pApp->getCompList()[ConnectionIndx])->setSrcGate(pApp->getCompList()[Index1]);
				((Connection*)pApp->getCompList()[ConnectionIndx])->setDstGate(pApp->getCompList()[Index2]);
				((Connection*)pApp->getCompList()[ConnectionIndx])->setDestPin(&(pApp->getCompList()[Index2]->getInpPin()[DstPin - 1]));
				((Connection*)pApp->getCompList()[ConnectionIndx])->setSourcePin(pApp->getCompList()[Index1]->getOutPin());
				pApp->getCompList()[Index1]->getOutPin()->ConnectTo((Connection*)pApp->getCompList()[ConnectionIndx]);
			}
			else if (cS == rGATEGATE) {
				((Connection*)pApp->getCompList()[ConnectionIndx])->setSrcGate(pApp->getCompList()[Index2]);
				((Connection*)pApp->getCompList()[ConnectionIndx])->setDstGate(pApp->getCompList()[Index1]);
				((Connection*)pApp->getCompList()[ConnectionIndx])->setDestPin(&(pApp->getCompList()[Index1]->getInpPin()[DstPin - 1]));
				((Connection*)pApp->getCompList()[ConnectionIndx])->setSourcePin(pApp->getCompList()[Index2]->getOutPin());
				pApp->getCompList()[Index2]->getOutPin()->ConnectTo((Connection*)pApp->getCompList()[ConnectionIndx]);
			}
		}
	}
}

void Connection::AdjustCrnrArr(ConnectionCases cS, int ClickedIndx2, int &DistPin, int**& CrnrArr, int CrnrCount, window *pWind) {
	if (ClickedIndx2 != -1 && cS != rGATEGATE) {
		if (pApp->getCompList()[ClickedIndx2]->GetCompType() == iLED) {
			pWind->SetPen(WHITE, 2);
			pWind->DrawLine(CrnrArr[CrnrCount - 1][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1]);
			pWind->DrawLine(CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 10);
			CrnrArr[CrnrCount - 2][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 10;

			pWind->SetPen(BLACK, 2);
			pWind->DrawLine(CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 10, ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1), ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 10);
			CrnrArr[CrnrCount - 1][0] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1);
			CrnrArr[CrnrCount - 1][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 10;
			DistPin = 1;
		}
		else if (pApp->getCompList()[ClickedIndx2]->getNoInp() == 3) {
			if (CrnrArr[CrnrCount - 1][1] >= ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 27) {
				if (CrnrArr[CrnrCount - 1][1] >= ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29) {
					pWind->SetPen(WHITE, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 1][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1]);
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29);
					CrnrArr[CrnrCount - 2][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29;

					pWind->SetPen(BLACK, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29, ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1), ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29);
					CrnrArr[CrnrCount - 1][0] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1);
					CrnrArr[CrnrCount - 1][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29;
					DistPin = 3;
				}
				if (CrnrArr[CrnrCount - 1][1] < ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29) {
					pWind->SetPen(WHITE, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 1][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1]);
					pWind->SetPen(BLACK, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29);
					CrnrArr[CrnrCount - 2][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29;
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29, ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1), ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29);
					CrnrArr[CrnrCount - 1][0] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1);
					CrnrArr[CrnrCount - 1][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29;
					DistPin = 3;
				}
			}
			else if (CrnrArr[CrnrCount - 1][1] <= ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 15) {
				if (CrnrArr[CrnrCount - 1][1] >= ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11) {
					pWind->SetPen(WHITE, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 1][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1]);
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11);
					CrnrArr[CrnrCount - 2][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11;

					pWind->SetPen(BLACK, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11, ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1), ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11);
					CrnrArr[CrnrCount - 1][0] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1);
					CrnrArr[CrnrCount - 1][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11;
					DistPin = 1;
				}
				if (CrnrArr[CrnrCount - 1][1] < ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11) {

					pWind->SetPen(WHITE, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 1][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1]);
					pWind->SetPen(BLACK, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11);
					CrnrArr[CrnrCount - 2][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11;
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11, ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1), ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11);
					CrnrArr[CrnrCount - 1][0] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1);
					CrnrArr[CrnrCount - 1][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11;
					DistPin = 1;
				}
			}
			else if (CrnrArr[CrnrCount - 1][1] > ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 15 && CrnrArr[CrnrCount - 1][1] < ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 27) {
				if (CrnrArr[CrnrCount - 1][1] >= ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20) {
					pWind->SetPen(WHITE, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 1][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1]);
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20);
					CrnrArr[CrnrCount - 2][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20;

					pWind->SetPen(BLACK, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20, ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1), ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20);
					CrnrArr[CrnrCount - 1][0] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1);
					CrnrArr[CrnrCount - 1][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20;
					DistPin = 2;
				}
				if (CrnrArr[CrnrCount - 1][1] < ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20) {
					pWind->SetPen(WHITE, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 1][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1]);
					pWind->SetPen(BLACK, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20);
					CrnrArr[CrnrCount - 2][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20;
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20, ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1), ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20);
					CrnrArr[CrnrCount - 1][0] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1);
					CrnrArr[CrnrCount - 1][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20;
					DistPin = 2;
				}
			}
		}
		else if (pApp->getCompList()[ClickedIndx2]->getNoInp() == 2) {
			if (CrnrArr[CrnrCount - 1][1] >= ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 21) {
				if (CrnrArr[CrnrCount - 1][1] >= ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29) {
					pWind->SetPen(WHITE, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 1][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1]);
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29);
					CrnrArr[CrnrCount - 2][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29;

					pWind->SetPen(BLACK, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29, ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1), ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29);
					CrnrArr[CrnrCount - 1][0] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1);
					CrnrArr[CrnrCount - 1][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29;
					DistPin = 2;
				}
				if (CrnrArr[CrnrCount - 1][1] < ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29) {
					pWind->SetPen(WHITE, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 1][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1]);
					pWind->SetPen(BLACK, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29);
					CrnrArr[CrnrCount - 2][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29;
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29, ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1), ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29);
					CrnrArr[CrnrCount - 1][0] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1);
					CrnrArr[CrnrCount - 1][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 29;
					DistPin = 2;
				}
			}
			else if (CrnrArr[CrnrCount - 1][1] <= ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20) {
				if (CrnrArr[CrnrCount - 1][1] >= ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11) {
					pWind->SetPen(WHITE, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 1][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1]);
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11);
					CrnrArr[CrnrCount - 2][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11;

					pWind->SetPen(BLACK, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11, ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1), ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11);
					CrnrArr[CrnrCount - 1][0] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1);
					CrnrArr[CrnrCount - 1][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11;
					DistPin = 1;
				}
				if (CrnrArr[CrnrCount - 1][1] < ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11) {

					pWind->SetPen(WHITE, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 1][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1]);
					pWind->SetPen(BLACK, 2);
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11);
					CrnrArr[CrnrCount - 2][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11;
					pWind->DrawLine(CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11, ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1), ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11);
					CrnrArr[CrnrCount - 1][0] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1);
					CrnrArr[CrnrCount - 1][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 11;
					DistPin = 1;
				}
			}
		}
		else {
			if (CrnrArr[CrnrCount - 1][1] >= ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20) {
				pWind->SetPen(WHITE, 2);
				pWind->DrawLine(CrnrArr[CrnrCount - 1][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1]);
				pWind->DrawLine(CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20);
				CrnrArr[CrnrCount - 2][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20;

				pWind->SetPen(BLACK, 2);
				pWind->DrawLine(CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20, ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1), ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20);
				CrnrArr[CrnrCount - 1][0] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1);
				CrnrArr[CrnrCount - 1][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20;
				DistPin = 1;
			}
			if (CrnrArr[CrnrCount - 1][1] < ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20) {
				pWind->SetPen(WHITE, 2);
				pWind->DrawLine(CrnrArr[CrnrCount - 1][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1]);
				pWind->SetPen(BLACK, 2);
				pWind->DrawLine(CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20);
				CrnrArr[CrnrCount - 2][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20;
				pWind->DrawLine(CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20, ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1), ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20);
				CrnrArr[CrnrCount - 1][0] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x1);
				CrnrArr[CrnrCount - 1][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20;
				DistPin = 1;
			}
		}

	}
	else if (ClickedIndx2 != -1 && cS == rGATEGATE) {
		pWind->SetPen(WHITE, 2);
		pWind->DrawLine(CrnrArr[CrnrCount - 1][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1]);
		pWind->DrawLine(CrnrArr[CrnrCount - 2][0], CrnrArr[CrnrCount - 1][1], CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y2) - 20);
		CrnrArr[CrnrCount - 2][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20;

		pWind->SetPen(BLACK, 2);
		pWind->DrawLine(CrnrArr[CrnrCount - 2][0], ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y2) - 20, ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x2), ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y1) + 20);
		CrnrArr[CrnrCount - 1][0] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).x2);
		CrnrArr[CrnrCount - 1][1] = ((pApp->getCompList()[ClickedIndx2]->getGfxInfo()).y2) - 20;
	}
}