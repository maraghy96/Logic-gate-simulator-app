#include "AddConnection.h"
#include"ApplicationManager.h"
#include "Components\Gate.h"
#include "SWITCH.h"

AddConnection::AddConnection(ApplicationManager *pApp, ActionType type) :Action(pApp, type)
{
	SrcGate = -1;
}

void AddConnection::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Wait for User Input
	int iXn, iYn;
	while (pOut->getWindow()->GetButtonState(LEFT_BUTTON, iXn, iYn) == BUTTON_UP) {
		pOut->getWindow()->GetMouseCoord(Cx1, Cy1);
	}

	
	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddConnection::Execute()
{
	//Get  Pointers to the Input/Output Interface
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Connection: Please carefully select your Source.");

	//Get Point1 of the connection
	ReadActionParameters();

	if (!(Cy1 > 82 && Cy1 < 578 && Cx1 > 22 && Cx1 < 1760)) {
		pOut->PrintMsg("Connection: Inacceptable place to draw a connection.");
		return;

	}

	GraphicsInfo GInfo;
	GInfo.x1 = Cx1;
	GInfo.y1 = Cy1;

	SrcGate = pManager->ClickedIndx(GInfo);

	if (SrcGate != -1)
	{
		if (pManager->getCompList()[SrcGate]->GetCompType() == iCONNECTION)
		{
			SrcGate = pManager->ClickedIndx(((Connection*)pManager->getCompList()[SrcGate])->getSrcGate()->getGfxInfo());
		}
		Connection *pA = new Connection(GInfo, pManager, pManager->getCompList()[SrcGate]);
		pManager->AddComponent(pA);
		pA->Draws(pOut);
		// Double checks a connection is being drawn with an error.
		bool Check = false;
		Check = pManager->CheckErrorConnection();
		if (!Check)
		{
			((Connection*)(pManager->getCompList()[pManager->getCompCount() - 1]))->setTempCrnrArr();
			pManager->CreateAction(this);
			pManager->getUndoedActions()->EmptyStack();

			//////////////////////////////////////////////////////////////////////////
			((pManager->getCompList()[SrcGate]))->setNext(pA->getDestGate());//Added Newly For Simulation
			pManager->getCompList()[SrcGate]->setConnection((Connection*)(pManager->getCompList()[pManager->getCompCount() - 1]));
			pA->getDestGate()->setPrevious(pManager->getCompList()[SrcGate]);
		}
	}
	else
	{
		Connection *pA = new Connection(GInfo, pManager);
		pManager->AddComponent(pA);
		pA->Draws(pOut);
		// Double checks a connection is being drawn with an error.
		bool Check = false;
		Check = pManager->CheckErrorConnection();
		if (!Check)
		{
			((Connection*)(pManager->getCompList()[pManager->getCompCount() - 1]))->setTempCrnrArr();
			//A connection cannot be added to the stack unless drawn correctly to prevent undo problems.
			pManager->CreateAction(this);
			pManager->getUndoedActions()->EmptyStack();

			//////////////////////////////////////////////////////////////////////////
			((pManager->getCompList()[SrcGate]))->setNext(pA->getDestGate());//Added Newly For Simulation
			pManager->getCompList()[SrcGate]->setConnection((Connection*)(pManager->getCompList()[pManager->getCompCount() - 1]));
			pA->getDestGate()->setPrevious(pManager->getCompList()[SrcGate]);
		}
	}
	pIn->WaitMouseClick(Cx3, Cx4);
	pOut->ClearDrawingArea();
}

void AddConnection::Undo()
{
	Component*SrcCmpnt = ((Connection*)(pManager->getCompList()[pManager->getCompCount() - 1]))->getSrcGate();
	SrcCmpnt->getOutPin()->DisconnectFrom(((Connection*)(pManager->getCompList()[pManager->getCompCount() - 1])));
	((Connection*)(pManager->getCompList()[pManager->getCompCount() - 1]))->DrawError(pManager->GetOutput());
	pManager->DeleteComponent();
}

void AddConnection::Redo()
{
	pManager->RedoComponent();
	Component*SrcCmpnt = ((Connection*)(pManager->getCompList()[pManager->getCompCount() - 1]))->getSrcGate();
	SrcCmpnt->getOutPin()->ConnectTo(((Connection*)(pManager->getCompList()[pManager->getCompCount() - 1])));
}

AddConnection::~AddConnection()
{

}
