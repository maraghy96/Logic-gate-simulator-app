#include "ApplicationManager.h"
#include"DELETE.h"
#include"Components/Connection.h"

DELo::DELo(ApplicationManager *pApp, ActionType type) :Action(pApp, type)
{//CompCount=pApp->getCompCount();
 //CompList=pApp->getCompList();
	deletionsCount = 0;

	dos = 0;
	rdos = 0;

	dels = 0;
	delsc = 0;

}
DELo::~DELo(void) {}
void DELo::ReadActionParameters() {

	//Get a Pointer to the Input / Output Interfaces
	//Output* OutputInterface = pManager->GetOutput();
	//Input* InputInterface = pManager->GetInput();

}
void DELo::Execute()
{
	CompList = pManager->getCompList();
	int CompCount = pManager->getCompCount();
	for (int i = 0; i < pManager->getCompCount(); i++)
	{
		if (CompList[i]->getSEL() && CompList[i]->GetCompType() != iCONNECTION)
		{
			deletions[deletionsCount] = CompList[i]->getID();
			redos[rdos] = CompList[i]->getID();
			rdos++;
			deletionsCount++;
			undos[dos] = CompList[i];
			dos++;

			////Loop on the next gates
			//for (int j = 0; j < AND2_FANOUT; j++)
			//{
			//	//loop on the previous of the next gates
			//	if (CompList[i]->getNext()[j] != NULL)
			//	{
			//		for (int s = 0; s < CompList[i]->getNext()[j]->getNoInp(); s++)
			//		{
			//			if (CompList[i]->GetCompType() != iLED && CompList[i]->getNext()[j] != NULL)
			//			{
			//				if (CompList[i]->getNext()[j]->getPrevComp()[s] == CompList[i])
			//				{
			//					CompList[i]->getNext()[j]->resetPrevious(s);
			//				}
			//			}
			//		}
			//	}

			//}
			////Loop on the previous gates
			//for (int k = 0; k < CompList[i]->getNoInp(); k++)
			//{
			//	//loop on the nexts of the previous gates
			//	for (int z = 0; z < AND2_FANOUT; z++)
			//	{
			//		if (CompList[i]->GetCompType() != SWTCH && CompList[i]->getPrevComp()[k] != NULL)
			//		{
			//			if (CompList[i]->getPrevComp()[k]->getNext()[z] == CompList[i])
			//			{
			//				CompList[i]->getPrevComp()[k]->resetNext(z);
			//			}
			//		}
			//	}
			//}
		}
	}

	for (int s = 0; s < deletionsCount; s++)
	{
		for (int g = 0; g < CompCount; g++)
		{
			if (CompList[g]->GetCompType() == iCONNECTION && ((Connection*)CompList[g])->getDestGate() != NULL && ((Connection*)CompList[g])->getDestGate() != NULL && ((Connection*)CompList[g])->getDestGate()->getID() == deletions[s])
			{
				deletions[deletionsCount] = CompList[g]->getID();
				deletionsCount++;
				for (int h = 0; h < CompCount; h++)
				{
					if (((Connection*)CompList[g])->getSrcGate() != NULL && ((Connection*)CompList[h])->getSrcGate() != NULL&&CompList[h]->GetCompType() == iCONNECTION && ((Connection*)CompList[h])->getSrcGate()->getID() == ((Connection*)CompList[g])->getSrcGate()->getID() && h != g)
					{
						deletions[deletionsCount] = CompList[h]->getID();
						deletionsCount++;
					}

				}
			}
		}
	}
	for (int s = 0; s < deletionsCount; s++)
	{
		for (int g = 0; g < CompCount; g++)
		{
			if (CompList[g]->GetCompType() == iCONNECTION && ((Connection*)CompList[g])->getSrcGate() != NULL && ((Connection*)CompList[g])->getSrcGate()->getID() == deletions[s])
			{
				deletions[deletionsCount] = CompList[g]->getID();
				deletionsCount++;
			}
		}
	}
	for (int i = 0; i < pManager->getCompCount(); i++)
	{
		if (CompList[i]->getSEL() && CompList[i]->GetCompType() == iCONNECTION)
		{
			deletions[deletionsCount] = CompList[i]->getID();
			redos[rdos] = CompList[i]->getID();
			rdos++;
			deletionsCount++;
			undos[dos] = CompList[i];
			dos++;
		}
	}
	pManager->Deleting(deletions, deletionsCount, undos, dos, dels, undosC, delsc);
	pManager->BubbleSort();
	pManager->CreateAction(this);
	pManager->getUndoedActions()->EmptyStack();
}
void DELo::Undo() {
	for (int j = 0; j < dos; j++)
	{
		pManager->getCompList()[pManager->getCompCount()] = undos[j];
		pManager->GetOutput()->DrawLabel(undos[j]->getCompLabel(), undos[j]->getGfxInfo());
		if (undos[j]->GetCompType() == iCONNECTION)
		{
			((Connection*)undos[j])->getSourcePin()->ConnectTo((Connection*)undos[j]);
		}
		pManager->incrCompCount();
	}
	pManager->BubbleSort();
	pManager->decCompCount();
	//pManager->deletionUndo(delsc,dos,undosC,undos,redos,rdos);

}

void DELo::Redo() { pManager->Deleting(deletions, deletionsCount, undos, delsc, dels, undosC, delsc); }