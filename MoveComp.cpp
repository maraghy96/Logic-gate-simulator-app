#include "MoveComp.h"
#include "ApplicationManager.h"
#include "Components\Connection.h"

MoveAct::MoveAct(ApplicationManager *pApp, ActionType type) :Action(pApp, type)
{
	MoveCmp = NULL;
	IndexCmp = -1;
	Dragging = false;
	MovedComps = new Component*[pManager->getCompCount()];
	for (int i = 0; i < pManager->getCompCount(); i++) {
		MovedComps[i] = NULL;
	}
}


MoveAct::~MoveAct(void)
{
}

void MoveAct::ReadActionParameters()
{
	pManager->GetOutput()->PrintMsg("Move: To enable moving using dragging please select your gate.");

	Input* pIn = pManager->GetInput();
	GraphicsInfo GInfo;
	int iXn, iYn;

	NumSelected = 0;
	pManager->CompSelected(NumSelected);

	if (NumSelected == 0) {
		char cKeyData = NO_KEYPRESS;
		// Initialize the coordinates of the mouse
		pManager->GetOutput()->getWindow()->GetMouseCoord(iXOld, iYOld);
		while ((pManager->GetOutput()->getWindow()->GetButtonState(LEFT_BUTTON, iXn, iYn) != BUTTON_DOWN) && (iYOld < 82 || iYOld>598 || iXOld < 22 || iXOld>1760)) {
			pManager->GetOutput()->getWindow()->GetMouseCoord(iXOld, iYOld);
		}
		GInfo.x1 = iXOld, GInfo.y1 = iYOld;
		IndexCmp = pManager->ClickedIndxMove(GInfo);

		// Escape to terminate the whole move action,, else waits the user to drag a component.. //handles if clicks on empty place.
		while ((pManager->GetOutput()->getWindow()->GetKeyPress(cKeyData) != ESCAPE) && (pManager->GetOutput()->getWindow()->GetButtonState(LEFT_BUTTON, iXn, iYn) == BUTTON_UP || IndexCmp == -1)) {
			pManager->GetOutput()->getWindow()->GetMouseCoord(iXOld, iYOld);
			GInfo.x1 = iXOld, GInfo.y1 = iYOld;
			IndexCmp = pManager->ClickedIndxMove(GInfo);
		}
		// checks whether he clicked or terminated the action.
		if (IndexCmp != -1) {
			MoveCmp = pManager->getCompList()[IndexCmp];
		}
	}
}

void MoveAct::Execute()
{
	ReadActionParameters();
	char cKeyD = NO_KEYPRESS;
	NumSelected = 0; pManager->CompSelected(NumSelected);


	if (IndexCmp == -1 && NumSelected == 0) {
		pManager->GetOutput()->PrintMsg("Move: You didn't move anything.");
		return;
	}


	if (NumSelected > 1) {
		for (int i = 0; i < NumSelected; i++) {
			MovedComps[i] = pManager->CompSelected(NumSelected)[i];
		}
		Drag(pManager->CompSelected(NumSelected), NumSelected, Dragging, pManager->GetOutput()->getWindow(), pManager, cKeyD, pManager->GetOutput());
		pManager->CreateAction(this);
		pManager->getUndoedActions()->EmptyStack();
	}
	else {
		if (NumSelected == 0) {
			MovedComps[0] = MoveCmp;
			Drag(MoveCmp, Dragging, pManager->GetOutput()->getWindow(), pManager, cKeyD, pManager->GetOutput());
			pManager->CreateAction(this);
			pManager->getUndoedActions()->EmptyStack();
		}
		else {
			MoveCmp = pManager->CompSelected(NumSelected)[0];
			MovedComps[0] = MoveCmp;
			Drag(MoveCmp, Dragging, pManager->GetOutput()->getWindow(), pManager, cKeyD, pManager->GetOutput());
			pManager->CreateAction(this);
			pManager->getUndoedActions()->EmptyStack();
		}
	}
	
	pManager->GetOutput()->PrintMsg("Move/Multimove: Done");
	pManager->GetOutput()->ClearDrawingArea();
}

//Drag is overloaded to handle if the user enters directly to move action without selecting any gate.
void MoveAct::Drag(Component*iMoveComp, bool iDragging, window* pWind, ApplicationManager*ipManager, char cKeyData, Output*pOut)
{
	MultipleMove = false;
	int xI = iMoveComp->getGfxInfo().x1, yI = iMoveComp->getGfxInfo().y1;
	int*SrcConnections = new int[20];
	int*DstConnections = new int[20];
	int SrcCount, DstCount = 0;
	ipManager->ConnectionsLinked(iMoveComp, SrcConnections, DstConnections, SrcCount, DstCount);
	int deltaX = 0, deltaY = 0;
	Component**CompList = ipManager->getCompList();
	int**sCrnrArri = new int*[8]; int**dCrnrArri = new int*[8];
	for (int i = 0; i < 8; i++) {
		sCrnrArri[i] = new int[2];
		dCrnrArri[i] = new int[2];
	}
	pOut->setBuff(true);
	while (pWind->GetKeyPress(cKeyData) != ESCAPE) {
		{
			pManager->GetOutput()->PrintMsg("Move: Begin dragging your gate. Press Escape to stop moving.");
			if (iDragging == false) {
				if (pWind->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_DOWN) {
					if (((iX > iMoveComp->getGfxInfo().x1) && (iX < (iMoveComp->getGfxInfo().x1 + 40))) && ((iY > iMoveComp->getGfxInfo().y1) && (iY < iMoveComp->getGfxInfo().y1 + 40))) {
						iDragging = true;
						deltaX = iX - iXOld, deltaY = iY - iYOld;
						iXOld = iX; iYOld = iY;
					}
				}
			}
			else {
				if (pWind->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_UP) {
					iDragging = false;
				}
				else if (iY > 82 && iY < 578 && iX>22 && iX < 1760) {
					if (iX != iXOld && pWind->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_DOWN) {
						iMoveComp->setPos(iMoveComp->getGfxInfo().x1 + (iX - iXOld), iMoveComp->getGfxInfo().y1);
						deltaX = iX - iXOld;
						if (SrcCount > 0) {
							for (int i = 0; i < SrcCount; i++) {
								int k = ((Connection*)CompList[SrcConnections[i]])->getCrnrCount();
								for (int z = 0; z < k; z++) {
									sCrnrArri[z][0] = ((Connection*)CompList[SrcConnections[i]])->getCrnrArr()[z][0];
									sCrnrArri[z][1] = ((Connection*)CompList[SrcConnections[i]])->getCrnrArr()[z][1];
								}
								for (int j = 0; j < 3; j++) {
									sCrnrArri[j][0] = sCrnrArri[j][0] + deltaX;
								}
								((Connection*)CompList[SrcConnections[i]])->setCrnrArr(sCrnrArri);
							}
						}
						if (DstCount > 0) {
							for (int i = 0; i < DstCount; i++) {
								int k = ((Connection*)CompList[DstConnections[i]])->getCrnrCount();
								for (int z = 0; z < k; z++) {
									dCrnrArri[z][0] = ((Connection*)CompList[DstConnections[i]])->getCrnrArr()[z][0];
									dCrnrArri[z][1] = ((Connection*)CompList[DstConnections[i]])->getCrnrArr()[z][1];
								}
								if (k == 4) {
									for (int j = 1; j < 4; j++) {
										dCrnrArri[j][0] = dCrnrArri[j][0] + deltaX;
									}
								}
								else if (k > 4) {
									for (int j = 3; j < 6; j++) {
										dCrnrArri[j][0] = dCrnrArri[j][0] + deltaX;
									}
								}
								((Connection*)CompList[DstConnections[i]])->setCrnrArr(dCrnrArri);
							}

						}
						iXOld = iX;
					}
					if (iY != iYOld&& pWind->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_DOWN) {
						iMoveComp->setPos(iMoveComp->getGfxInfo().x1, iMoveComp->getGfxInfo().y1 + (iY - iYOld));
						deltaY = iY - iYOld;
						if (SrcCount > 0) {
							for (int i = 0; i < SrcCount; i++) {
								int k = ((Connection*)CompList[SrcConnections[i]])->getCrnrCount();
								for (int z = 0; z < k; z++) {
									sCrnrArri[z][0] = ((Connection*)CompList[SrcConnections[i]])->getCrnrArr()[z][0];
									sCrnrArri[z][1] = ((Connection*)CompList[SrcConnections[i]])->getCrnrArr()[z][1];
								}
								for (int j = 0; j < 2; j++) {
									sCrnrArri[j][1] = sCrnrArri[j][1] + deltaY;
								}
								((Connection*)CompList[SrcConnections[i]])->setCrnrArr(sCrnrArri);
							}
						}
						if (DstCount > 0) {
							for (int i = 0; i < DstCount; i++) {
								int k = ((Connection*)CompList[DstConnections[i]])->getCrnrCount();
								for (int z = 0; z < k; z++) {
									dCrnrArri[z][0] = ((Connection*)CompList[DstConnections[i]])->getCrnrArr()[z][0];
									dCrnrArri[z][1] = ((Connection*)CompList[DstConnections[i]])->getCrnrArr()[z][1];
								}
								if (k == 4) {
									for (int j = 2; j < 4; j++) {
										dCrnrArri[j][1] = dCrnrArri[j][1] + deltaY;
									}
								}
								else if (k > 4) {
									for (int j = 4; j < 6; j++) {
										dCrnrArri[j][1] = dCrnrArri[j][1] + deltaY;
									}
								}
								((Connection*)CompList[DstConnections[i]])->setCrnrArr(dCrnrArri);
							}

						}
						iYOld = iY;
					}
				}

			}
			iMoveComp->Draw(pOut);
			ipManager->UpdateIntra();
			pWind->UpdateBuffer();
		}
	}
	DeltaOld.x1 = iMoveComp->getGfxInfo().x1- xI;
	DeltaOld.y1 = iMoveComp->getGfxInfo().y1- yI;
	pOut->setBuff(false);
	delete[]SrcConnections;
	delete[]DstConnections;
	for (int i = 0; i < 4; i++) {
		delete sCrnrArri[i];
	}
	delete sCrnrArri;
	for (int i = 0; i < 4; i++) {
		delete dCrnrArri[i];
	}
	delete dCrnrArri;
}

void MoveAct::Drag(Component**iMoveComps, int NumSelected, bool iDragging, window* pWind, ApplicationManager*ipManager, char cKeyData, Output*pOut)
{
	MultipleMove = true;

	int SrcCount, DstCount = 0; int deltaX = 0, deltaY = 0;

	Component**CompList = ipManager->getCompList();
	int*SrcConnections = new int[20];
	int*DstConnections = new int[20];
	int**sCrnrArri = new int*[8];
	int**dCrnrArri = new int*[8];
	for (int i = 0; i < 8; i++) {
		sCrnrArri[i] = new int[2];
		dCrnrArri[i] = new int[2];
	}

	bool move = false;
	GraphicsInfo GInfo;
	int ClickedIndx = -1;
	pManager->GetOutput()->PrintMsg("Multimove: Please Select your gate of reference.");
	pManager->GetInput()->GetPointClicked(iXOld, iYOld); GInfo.x1 = iXOld, GInfo.y1 = iYOld;
	ClickedIndx = ipManager->ClickedIndx(GInfo);
	for (int i = 0; i < NumSelected; i++) {
		if (ipManager->getCompList()[ClickedIndx] == iMoveComps[i]) {
			ClickedIndx = i;
			move = false;
			break;
		}
		move = true;
	}
	while (ClickedIndx == -1 && move) {
		pManager->GetOutput()->PrintMsg("Multimove: Please Select your gate of reference from the selected one or Escape to terminate move Action. ");
		pManager->GetInput()->GetPointClicked(iXOld, iYOld); GInfo.x1 = iXOld, GInfo.y1 = iYOld;
		ClickedIndx = ipManager->ClickedIndx(GInfo);
		if (ClickedIndx != -1) {
			for (int i = 0; i < NumSelected; i++) {
				if (ipManager->getCompList()[ClickedIndx] == iMoveComps[i]) {
					ClickedIndx = i;
					move = false;
					break;
				}
				move = true;
			}
		}
	}

	pManager->GetOutput()->PrintMsg("Multimove: Please select your destination.");
	pManager->GetInput()->GetPointClicked(iXOld, iYOld);
	while (iXOld < 22 || iXOld>1760 || iYOld < 52 || iYOld>620) {
		pManager->GetOutput()->PrintMsg("Multimove: Unallowed Place.");
		pManager->GetInput()->GetPointClicked(iXOld, iYOld);
	}

	deltaX = iXOld - ipManager->getCompList()[ClickedIndx]->getGfxInfo().x1 - 20;
	deltaY = iYOld - ipManager->getCompList()[ClickedIndx]->getGfxInfo().y1 - 20;
	DeltaOld.x1 = deltaX;
	DeltaOld.y1 = deltaY;

	for (int i = 0; i < NumSelected; i++) {
		iMoveComps[i]->setPos(iMoveComps[i]->getGfxInfo().x1 + deltaX, iMoveComps[i]->getGfxInfo().y1 + deltaY);
	}
	move = false;
	for (int i = 0; i < NumSelected; i++) {
		move = ipManager->CheckBunchOverlapping(iMoveComps[i]->getGfxInfo(), iMoveComps[i]);
		if (iMoveComps[i]->getGfxInfo().x1 < 22 || iMoveComps[i]->getGfxInfo().x2 >1750 || iMoveComps[i]->getGfxInfo().y1 < 82 || iMoveComps[i]->getGfxInfo().y2 >580) {
			move = true;
		}
		if (move) {
			break;
		}
	}
	bool duplicate;
	int CnrCount;
	if (move) {
		for (int i = 0; i < NumSelected; i++) {
			iMoveComps[i]->setPos(iMoveComps[i]->getGfxInfo().x1 - deltaX, iMoveComps[i]->getGfxInfo().y1 - deltaY);
		}
		ipManager->GetOutput()->PrintMsg("Multimove: Action cancelled due to overlapping or gates are overflowing.");
	}
	else {
		for (int k = 0; k < NumSelected; k++) {
			ipManager->ConnectionsLinked(iMoveComps[k], SrcConnections, DstConnections, SrcCount, DstCount);
			for (int i = 0; i < SrcCount; i++) {
				if ((((Connection*)(ipManager->getCompList()[SrcConnections[i]]))->getDestGate())->isSelected())
				{
					duplicate = true;
				}
				if (!duplicate) {
					CnrCount = ((Connection*)(ipManager->getCompList()[SrcConnections[i]]))->getCrnrCount();
					for (int b = 0; b < CnrCount; b++) {
						sCrnrArri[b][0] = ((Connection*)(ipManager->getCompList()[SrcConnections[i]]))->getCrnrArr()[b][0] + deltaX;
						sCrnrArri[b][1] = ((Connection*)(ipManager->getCompList()[SrcConnections[i]]))->getCrnrArr()[b][1] + deltaY;
					}
					((Connection*)(ipManager->getCompList()[SrcConnections[i]]))->setCrnrArr(sCrnrArri);
				}
				((Connection*)(ipManager->getCompList()[SrcConnections[i]]))->setTempCrnrArr();
			}
			for (int i = 0; i < DstCount; i++) {
				CnrCount = ((Connection*)(ipManager->getCompList()[DstConnections[i]]))->getCrnrCount();
				for (int b = 0; b < CnrCount; b++) {
					dCrnrArri[b][0] = ((Connection*)(ipManager->getCompList()[DstConnections[i]]))->getCrnrArr()[b][0] + deltaX;
					dCrnrArri[b][1] = ((Connection*)(ipManager->getCompList()[DstConnections[i]]))->getCrnrArr()[b][1] + deltaY;
				}
				((Connection*)(ipManager->getCompList()[DstConnections[i]]))->setCrnrArr(dCrnrArri);
				((Connection*)(ipManager->getCompList()[DstConnections[i]]))->setTempCrnrArr();
			}
		}
	}
	delete[]SrcConnections;
	delete[]DstConnections;
	for (int i = 0; i < 8; i++) {
		delete sCrnrArri[i];
		delete dCrnrArri[i];
	}
	delete sCrnrArri;
	delete dCrnrArri;
}

void MoveAct::Undo()
{
	int SrcCount;
	int DstCount;
	int*SrcConnections = new int[20];
	int*DstConnections = new int[20];
	int**sCrnrArri = new int*[8];
	int**dCrnrArri = new int*[8];
	for (int i = 0; i < 8; i++) {
		sCrnrArri[i] = new int[2];
		dCrnrArri[i] = new int[2];
	}
	bool duplicate = false;
	int CnrCount;
	if (MultipleMove) {
		for (int i = 0; i < NumSelected; i++) {
			pManager->GetOutput()->ClearDrawingArea();
			MovedComps[i]->setPos(MovedComps[i]->getGfxInfo().x1 - DeltaOld.x1, MovedComps[i]->getGfxInfo().y1 - DeltaOld.y1);
			pManager->ConnectionsLinked(MovedComps[i], SrcConnections, DstConnections, SrcCount, DstCount);
			for (int i = 0; i < SrcCount; i++) {
				if ((((Connection*)(pManager->getCompList()[SrcConnections[i]]))->getDestGate())->isSelected())
				{
					duplicate = true;
				}
				if (!duplicate) {
					CnrCount = ((Connection*)(pManager->getCompList()[SrcConnections[i]]))->getCrnrCount();
					for (int b = 0; b < CnrCount; b++) {
						sCrnrArri[b][0] = ((Connection*)(pManager->getCompList()[SrcConnections[i]]))->getCrnrArr()[b][0] - DeltaOld.x1;
						sCrnrArri[b][1] = ((Connection*)(pManager->getCompList()[SrcConnections[i]]))->getCrnrArr()[b][1] - DeltaOld.y1;
					}
					((Connection*)(pManager->getCompList()[SrcConnections[i]]))->setCrnrArr(sCrnrArri);
				}
				((Connection*)(pManager->getCompList()[SrcConnections[i]]))->setTempCrnrArr();
			}
			for (int i = 0; i < DstCount; i++) {
				CnrCount = ((Connection*)(pManager->getCompList()[DstConnections[i]]))->getCrnrCount();
				for (int b = 0; b < CnrCount; b++) {
					dCrnrArri[b][0] = ((Connection*)(pManager->getCompList()[DstConnections[i]]))->getCrnrArr()[b][0] - DeltaOld.x1;
					dCrnrArri[b][1] = ((Connection*)(pManager->getCompList()[DstConnections[i]]))->getCrnrArr()[b][1] - DeltaOld.y1;
				}
				((Connection*)(pManager->getCompList()[DstConnections[i]]))->setCrnrArr(dCrnrArri);
				((Connection*)(pManager->getCompList()[DstConnections[i]]))->setTempCrnrArr();
			}
		}
	}
	else {
		pManager->GetOutput()->ClearDrawingArea();
		MovedComps[0]->setPos(MovedComps[0]->getGfxInfo().x1 - DeltaOld.x1, MovedComps[0]->getGfxInfo().y1 - DeltaOld.y1);
		pManager->ConnectionsLinked(MovedComps[0], SrcConnections, DstConnections, SrcCount, DstCount);
		for (int i = 0; i < SrcCount; i++) {
			if ((((Connection*)(pManager->getCompList()[SrcConnections[i]]))->getDestGate())->isSelected())
			{
				duplicate = true;
			}
			if (!duplicate) {
				CnrCount = ((Connection*)(pManager->getCompList()[SrcConnections[i]]))->getCrnrCount();
				for (int b = 0; b < CnrCount; b++) {
					sCrnrArri[b][0] = ((Connection*)(pManager->getCompList()[SrcConnections[i]]))->getCrnrArr()[b][0] - DeltaOld.x1;
					sCrnrArri[b][1] = ((Connection*)(pManager->getCompList()[SrcConnections[i]]))->getCrnrArr()[b][1] - DeltaOld.y1;
				}
				((Connection*)(pManager->getCompList()[SrcConnections[i]]))->setCrnrArr(sCrnrArri);
			}
			((Connection*)(pManager->getCompList()[SrcConnections[i]]))->setTempCrnrArr();
		}
		for (int i = 0; i < DstCount; i++) {
			CnrCount = ((Connection*)(pManager->getCompList()[DstConnections[i]]))->getCrnrCount();
			for (int b = 0; b < CnrCount; b++) {
				dCrnrArri[b][0] = ((Connection*)(pManager->getCompList()[DstConnections[i]]))->getCrnrArr()[b][0] - DeltaOld.x1;
				dCrnrArri[b][1] = ((Connection*)(pManager->getCompList()[DstConnections[i]]))->getCrnrArr()[b][1] - DeltaOld.y1;
			}
			((Connection*)(pManager->getCompList()[DstConnections[i]]))->setCrnrArr(dCrnrArri);
			((Connection*)(pManager->getCompList()[DstConnections[i]]))->setTempCrnrArr();
		}
	}
	delete[]SrcConnections;
	delete[]DstConnections;
	for (int i = 0; i < 8; i++) {
		delete sCrnrArri[i];
		delete dCrnrArri[i];
	}
	delete sCrnrArri;
	delete dCrnrArri;
}

void MoveAct::Redo()
{
	int SrcCount;
	int DstCount;
	int*SrcConnections = new int[20];
	int*DstConnections = new int[20];
	int**sCrnrArri = new int*[8];
	int**dCrnrArri = new int*[8];
	for (int i = 0; i < 8; i++) {
		sCrnrArri[i] = new int[2];
		dCrnrArri[i] = new int[2];
	}
	bool duplicate = false;
	int CnrCount;
	if (MultipleMove) {
		for (int i = 0; i < NumSelected; i++) {
			pManager->GetOutput()->ClearDrawingArea();
			MovedComps[i]->setPos(MovedComps[i]->getGfxInfo().x1 + DeltaOld.x1, MovedComps[i]->getGfxInfo().y1 + DeltaOld.y1);
			pManager->ConnectionsLinked(MovedComps[i], SrcConnections, DstConnections, SrcCount, DstCount);
			for (int i = 0; i < SrcCount; i++) {
				if ((((Connection*)(pManager->getCompList()[SrcConnections[i]]))->getDestGate())->isSelected())
				{
					duplicate = true;
				}
				if (!duplicate) {
					CnrCount = ((Connection*)(pManager->getCompList()[SrcConnections[i]]))->getCrnrCount();
					for (int b = 0; b < CnrCount; b++) {
						sCrnrArri[b][0] = ((Connection*)(pManager->getCompList()[SrcConnections[i]]))->getCrnrArr()[b][0] + DeltaOld.x1;
						sCrnrArri[b][1] = ((Connection*)(pManager->getCompList()[SrcConnections[i]]))->getCrnrArr()[b][1] + DeltaOld.y1;
					}
					((Connection*)(pManager->getCompList()[SrcConnections[i]]))->setCrnrArr(sCrnrArri);
				}
				((Connection*)(pManager->getCompList()[SrcConnections[i]]))->setTempCrnrArr();
			}
			for (int i = 0; i < DstCount; i++) {
				CnrCount = ((Connection*)(pManager->getCompList()[DstConnections[i]]))->getCrnrCount();
				for (int b = 0; b < CnrCount; b++) {
					dCrnrArri[b][0] = ((Connection*)(pManager->getCompList()[DstConnections[i]]))->getCrnrArr()[b][0] + DeltaOld.x1;
					dCrnrArri[b][1] = ((Connection*)(pManager->getCompList()[DstConnections[i]]))->getCrnrArr()[b][1] + DeltaOld.y1;
				}
				((Connection*)(pManager->getCompList()[DstConnections[i]]))->setCrnrArr(dCrnrArri);
				((Connection*)(pManager->getCompList()[DstConnections[i]]))->setTempCrnrArr();
			}
		}
	}
	else {
		pManager->GetOutput()->ClearDrawingArea();
		MovedComps[0]->setPos(MovedComps[0]->getGfxInfo().x1 + DeltaOld.x1, MovedComps[0]->getGfxInfo().y1 + DeltaOld.y1);
		pManager->ConnectionsLinked(MovedComps[0], SrcConnections, DstConnections, SrcCount, DstCount);
		for (int i = 0; i < SrcCount; i++) {
			if ((((Connection*)(pManager->getCompList()[SrcConnections[i]]))->getDestGate())->isSelected())
			{
				duplicate = true;
			}
			if (!duplicate) {
				CnrCount = ((Connection*)(pManager->getCompList()[SrcConnections[i]]))->getCrnrCount();
				for (int b = 0; b < CnrCount; b++) {
					sCrnrArri[b][0] = ((Connection*)(pManager->getCompList()[SrcConnections[i]]))->getCrnrArr()[b][0] + DeltaOld.x1;
					sCrnrArri[b][1] = ((Connection*)(pManager->getCompList()[SrcConnections[i]]))->getCrnrArr()[b][1] + DeltaOld.y1;
				}
				((Connection*)(pManager->getCompList()[SrcConnections[i]]))->setCrnrArr(sCrnrArri);
			}
			((Connection*)(pManager->getCompList()[SrcConnections[i]]))->setTempCrnrArr();
		}
		for (int i = 0; i < DstCount; i++) {
			CnrCount = ((Connection*)(pManager->getCompList()[DstConnections[i]]))->getCrnrCount();
			for (int b = 0; b < CnrCount; b++) {
				dCrnrArri[b][0] = ((Connection*)(pManager->getCompList()[DstConnections[i]]))->getCrnrArr()[b][0] + DeltaOld.x1;
				dCrnrArri[b][1] = ((Connection*)(pManager->getCompList()[DstConnections[i]]))->getCrnrArr()[b][1] + DeltaOld.y1;
			}
			((Connection*)(pManager->getCompList()[DstConnections[i]]))->setCrnrArr(dCrnrArri);
			((Connection*)(pManager->getCompList()[DstConnections[i]]))->setTempCrnrArr();
		}
	}
	delete[]SrcConnections;
	delete[]DstConnections;
	for (int i = 0; i < 8; i++) {
		delete sCrnrArri[i];
		delete dCrnrArri[i];
	}
	delete sCrnrArri;
	delete dCrnrArri;
}

int MoveAct::iX = 0;
int MoveAct::iY = 0;
int MoveAct::iYOld = 0;
int MoveAct::iXOld = 0;