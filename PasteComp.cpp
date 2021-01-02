#include "PasteComp.h"
#include"COPY.h"
#include"CUT.h"
#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "AddORgate2.h"
#include "AddINV.h"
#include "AddANDgate3.h"
#include "AddORgate3.h"
#include "AddNANDgate2.h"
#include"AddNANDgate3.h"
#include "AddNORgate2.h"
#include "AddNORgate3.h"
#include "AddXORgate2.h"
#include "AddXORgate3.h"
#include "AddXNORgate2.h" 
#include"AddXNORgate3.h"
#include"AddSwitch.h"
#include"AddLabel.h"
#include"AddLED.h"
#include "AddBUFF.h"



PasteComp::PasteComp(ApplicationManager *pApp, ActionType type) :Action(pApp, type)
{
	UndosCount = 0;
	DeletionsCount = 0;
	
}


PasteComp::~PasteComp()
{
}

void PasteComp::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();

	//Wait for User Input
	Ctype = pOut->getWindow()->WaitMouseClick(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();
}

void PasteComp::Execute()
{
	//Get a Pointer to the Output Interface
	Output* pOut = pManager->GetOutput();

	//Print Action Message
	pOut->PrintMsg("Paste");

	//Checking if no components to copy or previous action wasn't copy/cut
	if (pManager->getCopyCutIndex()->StackTop() == NULL && (pManager->getActions()->StackTop()->ActionExecuted->getActionType() != COPY || pManager->getActions()->StackTop()->ActionExecuted->getActionType() != CUT))
	{
		return;
	}

	//Getting component index
	ComponentIndex=pManager->getCopyCutIndex()->StackTop()->CompIndex;
	Cmpnt = pManager->getCopyCutIndex()->StackTop()->Comp;
	CutOrCopy = pManager->getCopyCutIndex()->StackTop()->ActType;

	if (CutOrCopy == COPY)//solve this issue
	{
		//Loop to paste more than once 
		do
		{
			ReadActionParameters();
			if (Ctype == RIGHT_CLICK)
			{
				break;
			}
			else
			{
				pOut->PrintMsg("Click To paste");
				pManager->OverlappingComp(Cx, Cy);
				GraphicsInfo GInfo;
				GInfo.x1 = Cx - 20;
				GInfo.x2 = Cx + 20;
				GInfo.y1 = Cy - 20;
				GInfo.y2 = Cy + 20;
				Cmpnt->setGfxInfo(GInfo);
				pManager->AddComponent(Cmpnt);
				pManager->UpdateInterface();
				pOut->DrawLabel(Cmpnt->getCompLabel(), GInfo);
				pManager->CreateAction(this);
				pManager->getUndoedActions()->EmptyStack();
				Cmpnt = pManager->getCopyCutIndex()->StackTop()->Comp->Copy();
			}
		} while (Ctype == LEFT_CLICK);
	}
	else if (CutOrCopy == CUT)
	{

		//Print Action Message
		pOut->PrintMsg("Click on a position to cut");

		//Get pointer of class input
		Input* pIn = pManager->GetInput();

		//Get Center point of the Gate
		pIn->GetPointClicked(_Cx, _Cy);

		//Getting current position
		GfxOld = Cmpnt->getGfxInfo();

		//Clear the component
		pOut->ClearComponent(GfxOld);

		//Erasing Label
		pOut->EraseLabel(Cmpnt->getCompLabel(), GfxOld);

		//Checking Overlapping
		pManager->OverlappingComp(_Cx, _Cy);

		//GraphicsInfo GInfo;
		GfxNew.x1 = _Cx - 20;
		GfxNew.x2 = _Cx + 20;
		GfxNew.y1 = _Cy - 20;
		GfxNew.y2 = _Cy + 20;

		//Setting the new position of component
		Cmpnt->setGfxInfo(GfxNew);

		//Draw Label 
		pOut->DrawLabel(Cmpnt->getCompLabel(), GfxNew);

		pManager->CreateAction(this);
		pManager->getUndoedActions()->EmptyStack();
		
		 DeletionsCount= 0;
		UndosCount = 0;

		Component**CompList = pManager->getCompList();
		int CountSelected = pManager->CountSelected();
		int CompCount = pManager->getCompCount();
		for (int i = 0; i<CompCount; i++) {
			if (CompList[i]->getSEL()) {
				Deletions[DeletionsCount] = CompList[i]->getID();
				DeletionsCount++;
			}
		}
		for (int s = 0; s<DeletionsCount; s++)
		{
			for (int g = 0; g<CompCount; g++) 
			{
				if (CompList[g]->GetCompType() == iCONNECTION && ((Connection*)CompList[g])->getDestGate() != NULL && ((Connection*)CompList[g])->getDestGate() != NULL && ((Connection*)CompList[g])->getDestGate()->getID() == Deletions[s])
				{
					Deletions[DeletionsCount] = CompList[g]->getID();
					DeletionsCount++;
					undos[UndosCount] = CompList[g];
					UndosCount++;
					for (int h = 0; h<CompCount; h++) {
						if (((Connection*)CompList[g])->getSrcGate() != NULL && ((Connection*)CompList[h])->getSrcGate() != NULL&&CompList[h]->GetCompType() == iCONNECTION && ((Connection*)CompList[h])->getSrcGate()->getID() == ((Connection*)CompList[g])->getSrcGate()->getID() && h != g)
						{
							Deletions[DeletionsCount] = CompList[h]->getID();
							DeletionsCount++;
							undos[UndosCount] = CompList[h];
							UndosCount++;
						}
					}
				}
			}
		}
		for (int s = 0; s<DeletionsCount; s++) {
			for (int g = 0; g<CompCount; g++) 
			{
				if (CompList[g]->GetCompType() == iCONNECTION && ((Connection*)CompList[g])->getSrcGate() != NULL && ((Connection*)CompList[g])->getSrcGate()->getID() == Deletions[s])
				{
					Deletions[DeletionsCount] = CompList[g]->getID();
					DeletionsCount++;
					undos[UndosCount] = CompList[g];
					UndosCount++;
				}
			}
		}
		for (int i = 0; i<DeletionsCount; i++)
		{
			for (int j = 0; j<CompCount; j++)
			{
				if (CompList[j]->GetCompType() != iCONNECTION&&CompList[j]->getID() == Deletions[i])
				{
					Deletions[i] = 0;
				}
			}
		}
		int f = 0, s = 0;
		Component*undoss[200];
		pManager->Deleting(Deletions, DeletionsCount, undoss, f, s, 0, 0);
	}
	pManager->getCopyCutIndex()->Pop();
}

void PasteComp::Undo()
{
	//Get a pointer to the output interface
	Output* pOut = pManager->GetOutput();

	if (CutOrCopy == COPY)
	{
		//Getting the graphics info of the component
		GraphicsInfo GInfo = pManager->getCompList()[pManager->getCompCount() - 1]->getGfxInfo();

		//Erase the component
		pOut->ClearComponent(GInfo);

		//Erase Label
		pOut->EraseLabel(pManager->getCompList()[pManager->getCompCount() - 1]->getCompLabel(), GInfo);

		//Removes component from components list
		pManager->DeleteComponent();
	}
	else if (CutOrCopy == CUT)
	{
		//Erasing Label
		pOut->EraseLabel(pManager->getCompList()[ComponentIndex]->getCompLabel(), GfxNew);

		//Erasing the component
		pOut->ClearComponent(GfxNew);

		//Setting Component Graphics Info

		pManager->getCompList()[ComponentIndex]->setGfxInfo(GfxOld);

		//Draw Label 
		pOut->DrawLabel(pManager->getCompList()[ComponentIndex]->getCompLabel(), GfxOld);
		for (int i = 0; i<UndosCount; i++) 
		{
			pManager->getCompList()[pManager->getCompCount()] = undos[i];
			pManager->incrCompCount();

		}
	}
	}



void PasteComp::Redo()
{
	Output*pOut = pManager->GetOutput();

	if (CutOrCopy == COPY)
	{
		//Returning the component back to the components list
		pManager->RedoComponent();

		//Draw Label 
		pOut->DrawLabel(pManager->getCompList()[pManager->getCompCount() - 1]->getCompLabel(), pManager->getCompList()[pManager->getCompCount() - 1]->getGfxInfo());
	}
	else if (CutOrCopy == CUT)
	{
		//Getting pointer to output interface
		Output* pOut = pManager->GetOutput();

		//Erasing Label
		pOut->EraseLabel(pManager->getCompList()[ComponentIndex]->getCompLabel(), GfxOld);

		//Erasing the component
		pOut->ClearComponent(GfxOld);

		//Setting Component Graphics Info
		pManager->getCompList()[ComponentIndex]->setGfxInfo(GfxNew);

		//Draw Label 
		pOut->DrawLabel(pManager->getCompList()[ComponentIndex]->getCompLabel(), GfxNew);
		int l = 0,m = 0;
		Component*undos[50];
		pManager->Deleting(Deletions,DeletionsCount , undos, l, m, 0, 0);
	}
}
