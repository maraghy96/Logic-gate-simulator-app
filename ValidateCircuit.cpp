#include "ValidateCircuit.h"
#include "ApplicationManager.h"

ValidateCircuit::ValidateCircuit(ApplicationManager *pApp, ActionType type) :Action(pApp, type)
{
	Valid = true;
}

void ValidateCircuit::ReadActionParameters()
{
}

void ValidateCircuit::Execute()
{
	if (pManager->getCompCount() == 0) {
		Valid = false;
	}
	for (int i = 0; i < pManager->getCompCount(); i++) {
		if ((pManager->getCompList())[i]->GetCompType() == iCONNECTION) {
			continue;
		}
		if (pManager->getCompList()[i]->GetCompType() != iLED) {
			if (pManager->getCompList()[i]->getOutPin()->getConnNum() == 0) {
				Valid = false;
			}
		}
		if (pManager->getCompList()[i]->getNoInp() == 3) {
			if (pManager->getCompList()[i]->getPrevComp()[0] == NULL) {
				Valid = false;
			}
			if (pManager->getCompList()[i]->getPrevComp()[1] == NULL) {
				Valid = false;
			}
			if (pManager->getCompList()[i]->getPrevComp()[2] == NULL) {
				Valid = false;
			}
		}
		if (pManager->getCompList()[i]->getNoInp() == 2) {
			if (pManager->getCompList()[i]->getPrevComp()[0] == NULL) {
				Valid = false;
			}
			if (pManager->getCompList()[i]->getPrevComp()[1] == NULL) {
				Valid = false;
			}
		}
		if (pManager->getCompList()[i]->GetCompType() != SWTCH) {
			if (pManager->getCompList()[i]->getNoInp() == 1) {
				if (pManager->getCompList()[i]->getPrevComp()[0] == NULL) {
					Valid = false;
				}
			}
		}
	}
	if (!Valid) {
		pManager->GetOutput()->PrintMsg("Circuit is either empty or not valid! Check for errors then simulate.");
	}
	else {
		pManager->GetOutput()->PrintMsg("Circuit is valid. Switching to Simulation Mode.");
		pManager->ExecuteAction(IF_VALID);
	}
}

void ValidateCircuit::Undo()
{
}

void ValidateCircuit::Redo()
{
}
