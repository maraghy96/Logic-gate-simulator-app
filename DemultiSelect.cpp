#include "DemultiSelect.h"
#include "ApplicationManager.h"


DemultiSelect::DemultiSelect(ApplicationManager *pApp, ActionType type) :Action(pApp, type)
{
}


DemultiSelect::~DemultiSelect()
{

}

void DemultiSelect::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput(); int Cx1, Cy1, Indx = -1;
	pOut->PrintMsg("Select: Click on the gate to be selected.");

	window* pWind = pOut->getWindow();

	char cKeyData = NO_KEYPRESS;
	GraphicsInfo GfxInf;
	Component**CompList = pManager->getCompList();
	int CompCount = pManager->getCompCount();
	Input *pIn = new Input(pWind);

	pIn->GetPointClicked(Cx1, Cy1);
	GfxInf.x1 = Cx1;
	GfxInf.y1 = Cy1;
	Indx = pManager->ClickedIndx(GfxInf);

	while (pWind->GetKeyPress(cKeyData) != ESCAPE) {
		if (Indx == -1) {
			pOut->PrintMsg("You selected an empty place in the Drawing area");
		}
		else if (Indx < CompCount) {
			CompList[Indx]->setSEL();
			CompList[Indx]->Draw(pOut);
			pOut->PrintMsg("Done: Press Escape then Right click to exit.");
		}
		pIn->GetPointClicked(Cx1, Cy1);
		GfxInf.x1 = Cx1;
		GfxInf.y1 = Cy1;
		Indx = pManager->ClickedIndx(GfxInf);
	}

	pOut->PrintMsg("Done");
	delete pIn;
}

void DemultiSelect::Execute()
{
	ReadActionParameters();
}


void DemultiSelect::Undo()
{
}

void DemultiSelect::Redo()
{
}

int DemultiSelect::iX = 0;
int DemultiSelect::iY = 0;