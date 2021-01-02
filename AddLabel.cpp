#include"AddLabel.h"



AddLabel::AddLabel(ApplicationManager *pApp, ActionType type) :Action(pApp, type)
{
}


AddLabel::~AddLabel()
{
}

void AddLabel::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();


	pOut->FlushMouseQueue();

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddLabel::Execute()
{
	//Get a Pointer to the Input / Output Interfaces
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();


	int ComponentsCount = pManager->getCompCount();

	pOut->PrintMsg("Add/Edit A Label");

	if (ComponentsCount == 0)
	{
		pOut->PrintMsg("There're no available gates to add a label");
		return;
	}

	//Print Action Message
	pOut->PrintMsg("click on a gate to add/edit its label");

	//get location for adding label
	ReadActionParameters();
	//A GraphicsInfo for check
	GraphicsInfo GInfo;
	GInfo.x1 = Cx, GInfo.y1 = Cy;

	CompIndex = pManager->ClickedIndx(GInfo);

	if (pManager->getCompList()[CompIndex]->getCompLabel() == "")
	{
		//Print Action Message
		pOut->PrintMsg("click on a status bar to add/edit its label");

		//Getting Label from user
		CompLabel = pIn->GetString(pOut);

		//Setting Component Label
		pManager->getCompList()[CompIndex]->setCompLabel(CompLabel);

		if (pManager->getCompList()[CompIndex]->GetCompType() != iCONNECTION) {
			//Drawing Label
			pOut->DrawLabel(CompLabel, pManager->getCompList()[CompIndex]->getGfxInfo());
		}
		else {
			pOut->DrawLabel(CompLabel, pManager->getCompList()[CompIndex]->getGfxInfo());
		}

	}
	else
	{
		//Getting current label
		CompLabel = pManager->getCompList()[CompIndex]->getCompLabel();

		//Editing label
		CompLabelEdited = pIn->GetString(pOut, CompLabel);

		//Erase current label
		pOut->EraseLabel(CompLabel, pManager->getCompList()[CompIndex]->getGfxInfo());

		//Setting Component Label
		pManager->getCompList()[CompIndex]->setCompLabel(CompLabelEdited);

		//Drawing Label
		pOut->DrawLabel(CompLabelEdited, pManager->getCompList()[CompIndex]->getGfxInfo());
	}
	pOut->ClearStatusBar();
	pManager->CreateAction(this);
	pManager->getUndoedActions()->EmptyStack();
}

void AddLabel::Undo()
{
	Output* pOut = pManager->GetOutput();
	Component** ComponentsList = pManager->getCompList();

	if (CompLabelEdited == "")
	{
		//Erase current label
		pOut->EraseLabel(ComponentsList[CompIndex]->getCompLabel(), ComponentsList[CompIndex]->getGfxInfo());

		//Setting Component Label
		ComponentsList[CompIndex]->setCompLabel("");
	}
	else
	{
		//Erase current label
		pOut->EraseLabel(CompLabelEdited, ComponentsList[CompIndex]->getGfxInfo());

		//Setting Component Label
		ComponentsList[CompIndex]->setCompLabel(CompLabel);

		//Drawing Label
		pOut->DrawLabel(CompLabel, ComponentsList[CompIndex]->getGfxInfo());
	}
}

void AddLabel::Redo()
{
	Output* pOut = pManager->GetOutput();
	Component** ComponentsList = pManager->getCompList();

	if (CompLabelEdited == "")
	{
		//Setting Component Label
		ComponentsList[CompIndex]->setCompLabel(CompLabel);

		//Drawing Label
		pOut->DrawLabel(CompLabel, ComponentsList[CompIndex]->getGfxInfo());

	}
	else
	{
		//Erase current label
		pOut->EraseLabel(CompLabel, ComponentsList[CompIndex]->getGfxInfo());

		//Setting Component Label
		ComponentsList[CompIndex]->setCompLabel(CompLabelEdited);

		//Drawing Label
		pOut->DrawLabel(CompLabelEdited, ComponentsList[CompIndex]->getGfxInfo());
	}
}

