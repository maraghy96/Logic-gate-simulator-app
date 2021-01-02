#include"CreateTruthTable.h"
#include"ApplicationManager.h"

CreateTruthTable::CreateTruthTable(ApplicationManager *pApp, ActionType type) :Action(pApp, type)
{
}

CreateTruthTable::~CreateTruthTable(void)
{
	//delete pWind;
}

void CreateTruthTable::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();

	pOut->PrintMsg("Create Truth Table");

	NumInputs = pManager->getNumInputs();

	//Clear Status Bar
	pOut->ClearStatusBar();
}

void CreateTruthTable::Execute()
{
	//Creating Simulate Action
	Action* pAct = new SimulateCircuit(pManager, SIMU);

	//Getting pointer to the output interface
	Output* pOut = pManager->GetOutput();
	pWind = pOut->getWindow();


	ReadActionParameters();
	int Rows = (int)(pow(2, NumInputs));
	InputCombinations = new STATUS*[Rows];
	for (int i = 0; i < Rows; i++)
	{
		InputCombinations[i] = new STATUS[NumInputs];
	}
	for (int j = 0; j < NumInputs; j++)
	{
		double z = pow(2, j);
		for (int i = 0; i < Rows; i += z)
		{
			int k = 0;
			while (k < z)
			{
				InputCombinations[i][j] = LOW;
				InputCombinations[i + (int)z][j] = HIGH;
				i++;
				k++;
			}
		}
	}
	//Now Array of all possible combinations is created
	NumOutputs = pManager->getNumOutputs();
	Outputs = new STATUS*[Rows];
	for (int i = 0; i < Rows; i++)
	{
		Outputs[i] = new STATUS[NumOutputs];
	}
	((SimulateCircuit*)pAct)->Simulate(InputCombinations, NumInputs, Outputs, NumOutputs);//simulating the circuit

	if (NumInputs > 4)
	{
		myTruthTable.open("TruthTable.txt", ios::out);

		myTruthTable << "Input Combinations" << "\t" << "Output Combinations" << endl;
		for (double i = 0; i < pow(2, NumInputs); i++)
		{
			for (int k = 0; k < NumInputs; k++)
			{
				myTruthTable << InputCombinations[(int)i][k] << " ";
			}
			myTruthTable << " || ";
			for (int j = 0; j < NumOutputs; j++)
			{
				myTruthTable << Outputs[(int)i][j] << " ";
			}
			myTruthTable << endl;
		}
	}
	else
	{
		int y = 20;
		int x;
		int z;
		pWind = new window(300, 400, 0, 0);
		for (double i = 0; i < pow(2, NumInputs); i++)
		{
			x = 50;
			z = 200;
			for (int k = 0; k < NumInputs; k++)
			{
				pWind->SetPen(BLACK);
				pWind->SetFont(10, BOLD || ITALICIZED, BY_NAME, "Arial");
				pWind->DrawInteger(x,y, InputCombinations[(int)i][k]);
				x += 10;
			}
			for (int j = 0; j < NumOutputs; j++)
			{
				pWind->SetPen(BLACK);
				pWind->SetFont(10, BOLD || ITALICIZED, BY_NAME, "Arial");
				pWind->DrawInteger(z, y, Outputs[(int)i][j]);
				z += 10;
			}
			y += 20;
		}
	}
	pWind->WaitMouseClick(Cx, Cy);
	//delete pWind;
}



void CreateTruthTable::Undo()
{
}

void CreateTruthTable::Redo()
{
}


