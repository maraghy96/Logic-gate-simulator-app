#include"SimulateCircuit.h"
#include"ApplicationManager.h"

SimulateCircuit::SimulateCircuit(ApplicationManager *pApp, ActionType type) :Action(pApp, type)
{
}

SimulateCircuit::~SimulateCircuit(void)
{
}

void SimulateCircuit::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();

	pOut->getWindow()->GetMouseClick(Cx, Cy);

	pOut->PrintMsg("Simulate Circuit");

	//Clear Status Bar
	pOut->ClearStatusBar();
}

void SimulateCircuit::Execute()
{
	int CompCount = pManager->getCompCount();
	int CountConnection = pManager->CountConnections();
	int NumSwitches = pManager->getNumInputs();
	Component **ArrPtrToSWTCH = new Component*[NumSwitches];
	int CountInputs = 0;

	//In this loop , an array of pointers to all switches in the Component List is implemented
	for (int i = 0; i < CompCount; i++)
	{
		if (pManager->getCompList()[i]->GetCompType() == SWTCH)
		{
			ArrPtrToSWTCH[CountInputs] = pManager->getCompList()[i];
			ArrPtrToSWTCH[CountInputs]->setOperated();
			CountInputs++;
		}
		if (CountInputs == NumSwitches)
		{
			break;
		}
	}

	//Simulating
	for (int i = 0; i < NumSwitches; i++)
	{
		OperateComp(ArrPtrToSWTCH[i]);
	}

	//Reset everything
	pManager->DeOperate();
	pManager->getOperationStack()->EmptyStack();
}

void SimulateCircuit::Execute2()
{
	int CompCount = pManager->getCompCount();
	int NumSwitches = pManager->getNumInputs();
	Component **ArrPtrToSWTCH = new Component*[NumSwitches];
	int CountInputs = 0;

	//In this loop , an array of pointers to all switches in the Component List is implemented
	for (int i = 0; i < CompCount; i++)
	{
		if (pManager->getCompList()[i]->GetCompType() == SWTCH)
		{
			ArrPtrToSWTCH[CountInputs] = pManager->getCompList()[i];
			CountInputs++;
		}
		if (CountInputs == NumSwitches)
		{
			break;
		}
	}

	//Simulating
	for (int i = 0; i < NumSwitches; i++)
	{
		OperateComp(ArrPtrToSWTCH[i]);
	}

	//Reset everything
	pManager->DeOperate();
	pManager->getOperationStack()->EmptyStack();
}

bool SimulateCircuit::CheckPrevious(Component * Comp)
{
	int inputs = Comp->getNoInp();
	if (inputs == 1)
	{
		if (!Comp->getPrevComp()[0]->isOperated())
		{
			return false;
		}
	}
	else if (inputs == 2)
	{
		if (!Comp->getPrevComp()[0]->isOperated() || !Comp->getPrevComp()[1]->isOperated())
		{
			return false;
		}
	}
	else if (inputs == 3)
	{
		if (!Comp->getPrevComp()[0]->isOperated() || !Comp->getPrevComp()[1]->isOperated() || !Comp->getPrevComp()[0]->isOperated())
		{
			return false;
		}
	}
	return true;
}

void SimulateCircuit::OperateComp(Component * Comp)
{

	if (Comp->GetCompType() == SWTCH)
	{
		if (!Comp->isOperated())
		{
			((SWITCH*)Comp)->setOperated();
		}
	}
	else
	{
		if (!CheckPrevious(Comp))
		{
			return;
		}
		if (!Comp->isOperated())
		{
			Comp->Operate();
		}
	}
	if (Comp->GetCompType()==iLED)
	{
		return;
	}
	for (int i = 0; i < AND2_FANOUT; i++)
	{
		if (Comp->getNext()[i] != NULL)
		{
			OperateComp(Comp->getNext()[i]);
		}
	}
}


void SimulateCircuit::Simulate(STATUS ** InputCombinations, int NumInputs, STATUS **& Outputs, int NumOutputs)
{
	for (double i = 0; i < pow(2, NumInputs); i++)
	{
		for (int j = 0; j <NumInputs; j++)
		{
			for (int k = 0; k < pManager->getCompCount(); k++)
			{
				if (pManager->getCompList()[k]->GetCompType() == SWTCH)
				{
					if (!((SWITCH*)pManager->getCompList()[k])->isSet())
					{
						((SWITCH*)pManager->getCompList()[k])->setOutputPinStatus(InputCombinations[(int)i][j]);
						((SWITCH*)pManager->getCompList()[k])->setSwitchStatus();
						break;
					}
				}
			}
		}
		pManager->UpdateInterface();
		Execute2();
		pManager->UpdateInterface();
		for (int s = 0; s < NumOutputs; s++)
		{
			for (int k = 0; k < pManager->getCompCount(); k++)
			{
				if (pManager->getCompList()[k]->GetCompType() == iLED)
				{
					if (!((LED*)pManager->getCompList()[k])->isTaken())
					{
						Outputs[(int)i][s] = (STATUS)(pManager->getCompList()[k]->GetInputPinStatus(1));
						((LED*)(pManager->getCompList()[k]))->Take();
						break;
					}
				}
			}
		}
		////////////////////////////////////////////////////////////////////////////////
		//Reset everything
		pManager->ResetSwitchesAndLEDs();
		pManager->DeOperate();
		pManager->getOperationStack()->EmptyStack();
	}
}

void SimulateCircuit::Undo()
{
}

void SimulateCircuit::Redo()
{
}


