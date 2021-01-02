#include"ApplicationManager.h"
#include "LoadAct.h"


LoadDesign::LoadDesign(ApplicationManager *pApp, ActionType type) :Action(pApp, type)
{
}


LoadDesign::~LoadDesign()
{
}

void LoadDesign::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Load Design");

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void LoadDesign::Execute()
{
	ifstream Output_F;

	//Getting a pointer to the output interface
	Output* pOut = pManager->GetOutput();

	ReadActionParameters();

	//Opening file for reading
	Output_F.open("Design.txt", ios::in);

	if (pManager->getCompCount() != 0)
	{
		pManager->ResetApplication();
		pOut->ClearDrawingArea();
	}

	int ComponentCount;
	int type;
	Output_F >> ComponentCount;
	Output_F >> type;
	CompType ComponentType = (CompType)type;
	for (int i = 0; i < ComponentCount; i++)
	{
		Component* Comp = NULL;
		switch (ComponentType)
		{
		case AND2in:
			Comp = new AND2;
			break;
		case AND3in:
			Comp = new AND3;
			break;
		case OR2in:
			Comp = new OR2;
			break;
		case OR3in:
			Comp = new OR3;
			break;
		case NAND2in:
			Comp = new NAND2;
			break;
		case NAND3in:
			Comp = new NAND3;
			break;
		case NOR2in:
			Comp = new NOR2;
			break;
		case NOR3in:
			Comp = new NOR3;
			break;
		case XOR2in:
			Comp = new XOR2;
			break;
		case XOR3in:
			Comp = new XOR3;
			break;
		case XNOR2in:
			Comp = new XNOR2;
			break;
		case XNOR3in:
			Comp = new XNOR3;
			break;
		case Buff:
			Comp = new BUFFER;
			break;
		case iLED:
			Comp = new LED;
			break;
		case Inv:
			Comp = new NOT;
			break;
		case SWTCH:
			Comp = new SWITCH;
			break;
		case iCONNECTION:
			Comp = new Connection(pManager);
			break;
		}
		if (Comp)
		{
			Comp->Load(Output_F, pOut);
			pManager->AddComponent(Comp);
			Output_F >> type;
			ComponentType = (CompType)type;
		}
	}
	for (int i = 0; i < pManager->getCompCount(); i++)
	{
		int SrcID, DstID;
		if (pManager->getCompList()[i]->GetCompType() == iCONNECTION)
		{
			SrcID = ((Connection*)pManager->getCompList()[i])->getSrcCompID();
			DstID= ((Connection*)pManager->getCompList()[i])->getDstCompID();
			int SourceIndex = pManager->IDForWhichComp(SrcID);
			int DestIndex= pManager->IDForWhichComp(DstID);
			pManager->getCompList()[SourceIndex]->setNext(pManager->getCompList()[DestIndex]);
			pManager->getCompList()[DestIndex]->setPrevious(pManager->getCompList()[SourceIndex]);
		}
	}
}
void LoadDesign::Undo()
{

}

void LoadDesign::Redo()
{

}
