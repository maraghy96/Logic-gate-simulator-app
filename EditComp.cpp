#include"EditComp.h"



EditComp::EditComp(ApplicationManager *pApp, ActionType type) :Action(pApp, type)
{
}


EditComp::~EditComp()
{
}

void EditComp::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void EditComp::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	Component** ComponentsList = pManager->getCompList();
	int ComponentsCount = pManager->getCompCount();

	pOut->PrintMsg("Edit A Label");

	if (ComponentsCount == 0)
	{
		pOut->PrintMsg("There're no available gates to add a label");
		return;
	}
	//Getting the gate label by the user
	//CompLabel = pIn->GetString(pOut);

	//Print Action Message
	pOut->PrintMsg("click on a gate to edit its label");

	//get component for editing label
	ReadActionParameters();

	//validating
	int cx, cy, x1, x2, y1, y2;
	bool inPlace = false;
	do
	{
		inPlace = false;
		if (Cy <= 100 || Cy >= 550 || Cx <= 50 || Cx >= 1200)
		{
			inPlace = false;
		}
		else
		{
			for (int i = 0; i < ComponentsCount; i++)
			{
				if (ComponentsList[i]->GetCompType() != iCONNECTION)
				{
					x1 = ComponentsList[i]->getGfxInfo().x1; x2 = ComponentsList[i]->getGfxInfo().x2;
					y1 = ComponentsList[i]->getGfxInfo().y1; y2 = ComponentsList[i]->getGfxInfo().y2;
					cx = (x1 + x2) / 2;
					cy = (y1 + y2) / 2;
					if (abs(Cx - cx) <= 60 && abs(Cy - cy) <= 60)
					{
						//ComponentsList[i]->setCompLabel(CompLabel);
						inPlace = true;
						CompIndex = i;
						break;
					}
				}
			}
		}
		if (inPlace == false)
		{
			pOut->PrintMsg("Please click on a gate to edit its label!");
			ReadActionParameters();
		}
	} while (inPlace == false);

	CompLabel = pIn->GetString(pOut,ComponentsList[CompIndex]->getCompLabel());
	ComponentsList[CompIndex]->setCompLabel(CompLabel);

	window *pWind = pOut->getWindow();
	pWind->SetFont(10, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(BLACK);
	pWind->DrawString(cx - 10, (cy - 30), CompLabel);
}

void EditComp::Undo()
{
	//validating
	int cx, cy, x1, x2, y1, y2;
	Output* pOut = pManager->GetOutput();
	Component** ComponentsList = pManager->getCompList();
	x1 = ComponentsList[CompIndex]->getGfxInfo().x1; x2 = ComponentsList[CompIndex]->getGfxInfo().x2;
	y1 = ComponentsList[CompIndex]->getGfxInfo().y1; y2 = ComponentsList[CompIndex]->getGfxInfo().y2;
	cx = (x1 + x2) / 2;
	cy = (y1 + y2) / 2;
	window *pWind = pOut->getWindow();
	pWind->SetFont(10, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(WHITE);
	pWind->DrawString(cx - 10, (cy - 30), ComponentsList[CompIndex]->getCompLabel());
	pWind->DrawString(cx - 10, (cy - 30), ComponentsList[CompIndex]->getCompLabel());
	pWind->DrawString(cx - 10, (cy - 30), ComponentsList[CompIndex]->getCompLabel());
	pWind->DrawString(cx - 10, (cy - 30), ComponentsList[CompIndex]->getCompLabel());
	pWind->DrawString(cx - 10, (cy - 30), ComponentsList[CompIndex]->getCompLabel());
	pWind->DrawString(cx - 10, (cy - 30), ComponentsList[CompIndex]->getCompLabel());
	pWind->DrawString(cx - 10, (cy - 30), ComponentsList[CompIndex]->getCompLabel());
	pWind->DrawString(cx - 10, (cy - 30), ComponentsList[CompIndex]->getCompLabel());
	pWind->DrawString(cx - 10, (cy - 30), ComponentsList[CompIndex]->getCompLabel());
	pWind->DrawString(cx - 10, (cy - 30), ComponentsList[CompIndex]->getCompLabel());
	pWind->DrawString(cx - 10, (cy - 30), ComponentsList[CompIndex]->getCompLabel());
	pWind->DrawString(cx - 10, (cy - 30), ComponentsList[CompIndex]->getCompLabel());
	pWind->DrawString(cx - 10, (cy - 30), ComponentsList[CompIndex]->getCompLabel());
	pWind->DrawString(cx - 10, (cy - 30), ComponentsList[CompIndex]->getCompLabel());
	pWind->DrawString(cx - 10, (cy - 30), ComponentsList[CompIndex]->getCompLabel());
	pWind->DrawString(cx - 10, (cy - 30), ComponentsList[CompIndex]->getCompLabel());
	pWind->DrawString(cx - 10, (cy - 30), ComponentsList[CompIndex]->getCompLabel());
	ComponentsList[CompIndex]->setCompLabel("");
}

void EditComp::Redo()
{
	//validating
	int cx, cy, x1, x2, y1, y2;
	Output* pOut = pManager->GetOutput();
	Component** ComponentsList = pManager->getCompList();
	x1 = ComponentsList[CompIndex]->getGfxInfo().x1; x2 = ComponentsList[CompIndex]->getGfxInfo().x2;
	y1 = ComponentsList[CompIndex]->getGfxInfo().y1; y2 = ComponentsList[CompIndex]->getGfxInfo().y2;
	cx = (x1 + x2) / 2;
	cy = (y1 + y2) / 2;
	window *pWind = pOut->getWindow();
	pWind->SetFont(10, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(BLACK);
	pWind->DrawString(cx - 10, (cy - 30), CompLabel);
	ComponentsList[CompIndex]->setCompLabel(CompLabel);

}
