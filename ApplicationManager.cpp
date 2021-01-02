//The Includes
//////////////////////////////////////////////////
#include "ApplicationManager.h"


//////////////////////////////////////////////////////////////
ApplicationManager::ApplicationManager()
{
	CompCount = 0;
	CompDeleted = 0;
	ComponentsSelected = 0;

	//Creates the 2 stacks for actions
	Actions = new Stack;
	UndoedActions = new Stack;
	CopiedComps = new StackPaste;
	OperationMode = new Stack;

	for (int i = 0; i < MaxCompCount; i++)
	{
		CompList[i] = NULL;
		DelCompList[i] = NULL;
		CompsSelectedIndex[i] = 0;
	}

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
}

////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount] = pComp;
	CompCount++;
}

/////////////////////////////////////////////////////////////////////
int ApplicationManager::IDForWhichComp(int id)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->getID() == id)
		{
			return i;
		}
	}
	return -1;
}

////////////////////////////////////////////////////////////////////
int ApplicationManager::WhichComp(int Cx, int Cy)
{
	bool inPlace = true;
	int cx, cy, x1, x2, y1, y2;
	int CompIndex;
	do
	{
		if (Cy <= 100 || Cy >= 550 || Cx <= 50 || Cx >= 1200)
		{
			inPlace = true;
		}
		else
		{
			for (int i = 0; i < CompCount; i++)
			{
				x1 = (CompList[i]->getGfxInfo().x1); x2 = (CompList[i]->getGfxInfo().x2);
				y1 = (CompList[i]->getGfxInfo().y1); y2 = (CompList[i]->getGfxInfo().y2);
				cx = (x1 + x2) / 2;
				cy = (y1 + y2) / 2;
				if ((abs(Cx - cx) <= 40) && (abs(Cy - cy) <= 40))
				{
					inPlace = false;
					CompIndex = i;
					break;
				}
			}
		}
		if (inPlace == true)
		{
			OutputInterface->PrintMsg("You did not click on component");
			InputInterface->GetPointClicked(Cx, Cy);
		}
	} while (inPlace == true);
	return CompIndex;
}

/////////////////////////////////////////////////////////////////////
int ApplicationManager::WhichCompClicked(int Cx, int Cy)
{
	int cx, cy, x1, x2, y1, y2;
	int CompIndex;
	if (Cy <= 100 || Cy >= 550 || Cx <= 50 || Cx >= 1700)
	{
		return -1;
	}
	else
	{
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i]->GetCompType() != iCONNECTION) {
				x1 = (CompList[i]->getGfxInfo().x1); x2 = (CompList[i]->getGfxInfo().x2);
				y1 = (CompList[i]->getGfxInfo().y1); y2 = (CompList[i]->getGfxInfo().y2);
				cx = (x1 + x2) / 2;
				cy = (y1 + y2) / 2;
				if ((abs(Cx - cx) <= 40) && (abs(Cy - cy) <= 40))
				{
					CompIndex = i;
					CompList[CompIndex]->Click();
					return CompIndex;
				}
			}
			else {
				int CrnrCount = ((Connection*)CompList[i])->getCrnrCount();
				for (int r = 0; r < CrnrCount - 1; r++) {
					if ((Cx > ((Connection*)CompList[i])->getCrnrArr()[r][0] && Cx < ((Connection*)CompList[i])->getCrnrArr()[r + 1][0] && Cy <= ((Connection*)CompList[i])->getCrnrArr()[r][1] + 2 && Cy >= ((Connection*)CompList[i])->getCrnrArr()[r][1] - 2)) {
						CompIndex = i;
						CompList[CompIndex]->Click();
						return CompIndex;
					}
					if (Cy > ((Connection*)CompList[i])->getCrnrArr()[r][1] && Cy < ((Connection*)CompList[i])->getCrnrArr()[r + 1][1] && Cx <= ((Connection*)CompList[i])->getCrnrArr()[r][0] + 2 && Cx >= ((Connection*)CompList[i])->getCrnrArr()[r][0] - 2) {
						CompIndex = i;
						CompList[CompIndex]->Click();
						return CompIndex;
					}
				}
			}
		}
	}
	return -1;
}

/////////////////////////////////////////////////////////////////////
int* ApplicationManager::WhichCompSelected()
{
	int c = 0;
	CompsSelectedIndex[0] = NULL;
	int index;
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->isSelected() == true)
		{
			index = i;
			CompsSelectedIndex[c++] = index;
		}
	}
	return CompsSelectedIndex;
}

/////////////////////////////////////////////////////////////////////
int ApplicationManager::WhichCompClicked()
{
	int index;
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->isClicked() == true)
		{
			index = i;
			return index;
		}
	}
	return -1;
}

////////////////////////////////////////////////////////////////////////
int ApplicationManager::getNumInputs() const
{
	int NumInputs = 0;
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->GetCompType() == SWTCH)
		{
			NumInputs++;
		}
	}
	return NumInputs;
}

int ApplicationManager::getNumOutputs() const
{
	int NumOutputs = 0;
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->GetCompType() == iLED)
		{
			NumOutputs++;
		}
	}
	return NumOutputs;
}
/////////////////////////////////////////////DELETIOn
void ApplicationManager::Deleting(int deletions[], int &countt, Component**undos, int &dos, int &dels, int undosC[], int delsc) {
	int x, y;

	////Connections deletion
	for (int s = 0; s < countt; s++)
	{
		for (int g = 0; g < CompCount; g++)
		{
			if (CompList[g]->GetCompType() == iCONNECTION &&CompList[g]->getID() == deletions[s])
			{
				for (int i = 0; i < ((Connection*)CompList[g])->getCrnrCount() - 1; i++)
				{
					OutputInterface->getWindow()->SetBrush(WHITE);
					OutputInterface->getWindow()->SetPen(WHITE, 55);
					OutputInterface->getWindow()->DrawLine(((Connection*)CompList[g])->getCrnrArr()[i][0], ((Connection*)CompList[g])->getCrnrArr()[i][1], ((Connection*)CompList[g])->getCrnrArr()[i + 1][0], ((Connection*)CompList[g])->getCrnrArr()[i + 1][1]);
				}
				dels++;
				undos[dos] = CompList[g]; dos++;
				OutputInterface->EraseLabel(CompList[g]->getCompLabel(), CompList[g]->getGfxInfo());

				((Connection*)CompList[g])->getSourcePin()->DisconnectFrom((Connection*)CompList[g]);
				for (int j = g; j < CompCount - 1; j++) { CompList[j] = CompList[j + 1]; }CompList[CompCount--] = NULL; g--; CompList[CompCount + 1] = NULL;
			}
		}
	}


	////////////////////////////////////////////////////////////////////////
	//GATES Deletion
	for (int a = 0; a < countt; a++)
	{
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i]->GetCompType() != iCONNECTION&&CompList[i]->getID() == deletions[a])
			{
				x = CompList[i]->getGfxInfo().x2;
				y = CompList[i]->getGfxInfo().y2;
				OutputInterface->getWindow()->SetPen(WHITE, 1);
				OutputInterface->getWindow()->SetBrush(WHITE);
				OutputInterface->getWindow()->DrawRectangle(x, y, x - 40, y - 40);
				undos[dos] = CompList[i];
				dos++;
				dels++;
				OutputInterface->EraseLabel(CompList[i]->getCompLabel(), CompList[i]->getGfxInfo());
				for (int j = i; j < CompCount - 1; j++)
				{
					CompList[j] = CompList[j + 1];
				}
				CompList[CompCount--] = NULL;
				i--;
			}
		}
	}

}
///////////////////////////////////////////////////////
int ApplicationManager::CountSelected()
{
	ComponentsSelected = 0;
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->isSelected())
		{
			ComponentsSelected++;
		}
	}
	return ComponentsSelected;
}

int ApplicationManager::CountConnections()
{
	int c = 0;
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->GetCompType() == iCONNECTION)
		{
			c++;
		}
	}
	return c;
}

void ApplicationManager::ResetSwitchesAndLEDs()
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->GetCompType() == SWTCH)
		{
			((SWITCH*)CompList[i])->ResetSwitch();
		}
		else if (CompList[i]->GetCompType() == iLED)
		{
			((LED*)CompList[i])->ResetLed();

		}
	}
}

//////////////////////////////////////////////////////////////////////
void ApplicationManager::OverlappingComp(int &Cx, int &Cy)
{
	bool inPlace = false;
	int cx, cy, x1, x2, y1, y2;
	do
	{
		inPlace = false;
		if (Cy <= 100 || Cy >= 550 || Cx <= 50 || Cx >= 1200)
		{
			inPlace = true;
		}
		else
		{
			for (int i = 0; i < CompCount; i++)
			{
				x1 = (CompList[i]->getGfxInfo().x1); x2 = (CompList[i]->getGfxInfo().x2);
				y1 = (CompList[i]->getGfxInfo().y1); y2 = (CompList[i]->getGfxInfo().y2);
				cx = (x1 + x2) / 2;
				cy = (y1 + y2) / 2;
				if ((abs(Cx - cx) <= 70) && (abs(Cy - cy) <= 70))
				{
					inPlace = true;
					break;
				}
			}
		}
		if (inPlace == true)
		{
			OutputInterface->PrintMsg("Component cannot be added here! Choose another location..");
			InputInterface->GetPointClicked(Cx, Cy);
		}
	} while (inPlace == true);
	OutputInterface->ClearStatusBar();
}

/////////////////////////////////////////////////////////////////////
bool ApplicationManager::CheckBunchOverlapping(GraphicsInfo GInfo)
{
	int cx, cy;
	int Cx = (GInfo.x1 + GInfo.x2) / 2;
	int	Cy = (GInfo.y1 + GInfo.y2) / 2;
	for (int j = 0; j < CompCount; j++)
	{
		cx = (CompList[j]->getGfxInfo().x1 + CompList[j]->getGfxInfo().x2) / 2;
		cy = (CompList[j]->getGfxInfo().y1 + CompList[j]->getGfxInfo().y2) / 2;
		if (abs(Cx - cx) <= 70 && abs(Cy - cy) <= 70)
		{
			return true;
		}
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////
bool ApplicationManager::CheckBunchOverlapping(GraphicsInfo GInfo, Component*moveCmp)
{
	int cx, cy;
	int Cx = (GInfo.x1 + GInfo.x2) / 2;
	int	Cy = (GInfo.y1 + GInfo.y2) / 2;
	for (int j = 0; j < CompCount; j++)
	{
		if (CompList[j] == moveCmp) {
			continue;
		}
		cx = (CompList[j]->getGfxInfo().x1 + CompList[j]->getGfxInfo().x2) / 2;
		cy = (CompList[j]->getGfxInfo().y1 + CompList[j]->getGfxInfo().y2) / 2;
		if (abs(Cx - cx) <= 70 && abs(Cy - cy) <= 70)
		{
			return true;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////
//this function deletes the last component added
void ApplicationManager::DeleteComponent()
{
	DelCompList[CompDeleted++] = CompList[CompCount - 1];
	CompList[CompCount - 1] = NULL;
	CompCount--;
}

////////////////////////////////////////////////////////////////////////////
void ApplicationManager::DeleteComponent(int x)
{
	CompList[CompCount - 1] = NULL;
	CompCount--;
}

////////////////////////////////////////////////////////////////////
//this function returns the last component deleted to the array of components
void ApplicationManager::RedoComponent()
{
	CompList[CompCount] = DelCompList[CompDeleted - 1];
	DelCompList[CompDeleted - 1] = NULL;
	CompDeleted--;
	CompCount++;
}

////////////////////////////////////////////////////////////////////
//This function returns the array of components
Component** ApplicationManager::getCompList()
{
	return CompList;
}

///////////////////////////////////////////////////////////////////
//This function returns the actual number of components
int ApplicationManager::getCompCount() const
{
	return CompCount;

}


///////////////////////////////////////////////////////////////////////
//This function resets everything
void ApplicationManager::ResetApplication()
{
	CompCount = 0;
	CompDeleted = 0;
	ComponentsSelected = 0;

	for (int i = 0; i < MaxCompCount; i++)
	{
		CompList[i] = NULL;
		DelCompList[i] = NULL;
		CompsSelectedIndex[i] = 0;
	}
	//Creates the 2 stacks for actions
	Actions = new Stack;
	UndoedActions = new Stack;
	CopiedComps = new StackPaste;
	OperationMode = new Stack;
}

///////////////////////////////////////////////////////////////////
//This function returns the actual number of selected components
int ApplicationManager::getCompSelected()const
{
	return ComponentsSelected;
}

////////////////////////////////////////////////////////////////////
//This function returns the array of undoed components
Component** ApplicationManager::getDelCompList()
{
	return DelCompList;
}

////////////////////////////////////////////////////////////////////
//This function returns the number of undoed components
int ApplicationManager::getCompDeleted() const
{
	return CompDeleted;
}

////////////////////////////////////////////////////////////////////
ActionType ApplicationManager::GetUserAction()
{
	int x, y;
	if (UI.AppMode == SIMULATION)
	{
		if (!OperationMode->isEmpty() && OperationMode->StackTop()->ActionExecuted->getActionType() == OperateSWTCH)
		{
			return SIMU;
		}
	}
	InputInterface->WaitMouseClick(x, y);
	int index = WhichCompClicked(x, y);
	if (UI.AppMode == SIMULATION)
	{
		if (index != -1 && CompList[index]->GetCompType() == SWTCH)
		{
			return OperateSWTCH;
		}
		else
		{
			//Call input to get what action is required from the user
			return InputInterface->GetUserAction(x, y);
		}
	}
	else
	{
		if (index != -1 && !CompList[index]->isSelected())
		{
			return SEL;
		}
		else if (index != -1 && CompList[index]->isSelected())
		{
			return DESEL;
		}
		else
		{
			//Call input to get what action is required from the user
			return InputInterface->GetUserAction(x, y);
		}
	}
}

////////////////////////////////////////////////////////////////////
//This function returns the index of the clicked component
int ApplicationManager::ClickedIndx(GraphicsInfo GfsInfo) {
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->GetCompType() == iCONNECTION) {
			int CrnrCount = ((Connection*)CompList[i])->getCrnrCount();
			for (int r = 0; r < CrnrCount - 1; r++) {
				if ((GfsInfo.x1 > ((Connection*)CompList[i])->getCrnrArr()[r][0] && GfsInfo.x1 < ((Connection*)CompList[i])->getCrnrArr()[r + 1][0] && GfsInfo.y1 <= ((Connection*)CompList[i])->getCrnrArr()[r][1] + 2 && GfsInfo.y1 >= ((Connection*)CompList[i])->getCrnrArr()[r][1] - 2)) {
					return i;
				}
				if (GfsInfo.y1 > ((Connection*)CompList[i])->getCrnrArr()[r][1] && GfsInfo.y1 < ((Connection*)CompList[i])->getCrnrArr()[r + 1][1] && GfsInfo.x1 <= ((Connection*)CompList[i])->getCrnrArr()[r][0] + 2 && GfsInfo.x1 >= ((Connection*)CompList[i])->getCrnrArr()[r][0] - 2) {
					return i;
				}
			}
		}
		else {
			if (GfsInfo.x1 > (((Gate*)CompList[i])->getGfxInfo().x1 - 4) && GfsInfo.x1 < (((Gate*)CompList[i])->getGfxInfo().x2 + 4) && GfsInfo.y1 >(((Gate*)CompList[i])->getGfxInfo().y1 - 4) && GfsInfo.y1 < (((Gate*)CompList[i])->getGfxInfo().y2 + 4)) {
				return i;
			}
		}
	}
	return -1;
}

//////////////////////////////////////////////////////////////////////
int ApplicationManager::ClickedIndxMove(GraphicsInfo GfsInfo) {
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->GetCompType() == iCONNECTION) {
			continue;
		}
		if (GfsInfo.x1 > (((Gate*)CompList[i])->getGfxInfo().x1 - 4) && GfsInfo.x1 < (((Gate*)CompList[i])->getGfxInfo().x2 + 4) && GfsInfo.y1 >(((Gate*)CompList[i])->getGfxInfo().y1 - 4) && GfsInfo.y1 < (((Gate*)CompList[i])->getGfxInfo().y2 + 4)) {
			return i;
		}

	}
	return -1;
}

////////////////////////////////////////////////////////////////////
int ApplicationManager::ClickedIndx2(GraphicsInfo GfsInfo) 
{
	for (int i = 0; i < CompCount; i++) 
	{
		if (GfsInfo.x2 > ((CompList[i]->getGfxInfo()).x1 - 2) && GfsInfo.x2 < ((CompList[i]->getGfxInfo()).x2 + 2) && GfsInfo.y2 >((CompList[i]->getGfxInfo()).y1 - 2) && GfsInfo.y2 < ((CompList[i]->getGfxInfo()).y2 + 2)) {
			return i;
		}
	}
	return -1;
}

////////////////////////////////////////////////////////////////////
//This function returns the stack of undoed actions
Stack* ApplicationManager::getUndoedActions()
{
	return UndoedActions;
}

///////////////////////////////////////////////////////////////////
Stack* ApplicationManager::getActions()
{
	return Actions;
}

Stack * ApplicationManager::getOperationStack()
{
	return OperationMode;
}

///////////////////////////////////////////////////////////////////
StackPaste* ApplicationManager::getCopyCutIndex()
{
	return CopiedComps;
}

///////////////////////////////////////////////////////////////////
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
	case ADD_AND_GATE_2:
		pAct = new AddANDgate2(this, ActType);
		break;
	case ADD_Buff:
		pAct = new AddBUFF(this, ActType);
		break;
	case ADD_INV:
		pAct = new AddINV(this, ActType);
		break;
	case ADD_AND_GATE_3:
		pAct = new AddANDgate3(this, ActType);
		break;
	case ADD_NAND_GATE_2:
		pAct = new AddNANDgate2(this, ActType);
		break;
	case ADD_NAND_GATE_3:
		pAct = new AddNANDgate3(this, ActType);
		break;
	case ADD_OR_GATE_2:
		pAct = new AddORgate2(this, ActType);
		break;
	case ADD_OR_GATE_3:
		pAct = new AddORgate3(this, ActType);
		break;
	case ADD_NOR_GATE_2:
		pAct = new AddNORgate2(this, ActType);
		break;
	case ADD_NOR_GATE_3:
		pAct = new AddNORgate3(this, ActType);
		break;
	case ADD_XOR_GATE_2:
		pAct = new AddXORgate2(this, ActType);
		break;
	case ADD_XOR_GATE_3:
		pAct = new AddXORgate3(this, ActType);
		break;
	case ADD_XNOR_GATE_2:
		pAct = new AddXNORgate2(this, ActType);
		break;
	case ADD_XNOR_GATE_3:
		pAct = new AddXNORgate3(this, ActType);
		break;
	case ADD_Switch:
		pAct = new AddSwitch(this, ActType);
		break;
	case ADD_LED:
		pAct = new AddLED(this, ActType);
		break;
	case CLEAR:
		pAct = new EditConnection(this, ActType);
		break;
	case ADD_CONNECTION:
		pAct = new AddConnection(this, ActType);
		break;
	case COPY:
		pAct = new CopyComp(this, ActType);
		break;
	case CUT:
		pAct = new CutComp(this, ActType);
		break;
	case PASTE:
		pAct = new PasteComp(this, ActType);
		break;
	case SEL:
		pAct = new SelectComp(this, ActType);
		break;
	case MULTISELECT:
		pAct = new MultiSelect(this, ActType);
		break;
	case DESEL:
		pAct = new DeselectComp(this, ActType);
		break;
	case DEMULTISEL:
		pAct = new DemultiSelect(this, ActType);
		break;
	case MOVE:
		pAct = new MoveAct(this, ActType);
		break;
	case DEL:
		pAct = new  DELo(this, ActType);
		break;
	case OperateSWTCH:
		pAct = new OperateSWITCH(this, ActType);
		break;
	case LABEL:
		pAct = new AddLabel(this, ActType);
		break;
	case EDIT_Label:
		pAct = new EditComp(this, ActType);
		break;
	case UNDO:
		pAct = new UndoAction(this, ActType);
		break;
	case REDO:
		pAct = new REDOAction(this, ActType);
		break;
	case SAVE:
		pAct = new SaveDesign(this, ActType);
		break;
	case LOAD:
		pAct = new LoadDesign(this, ActType);
		break;
	case STATUS_BAR:
		break;
	case DSN_TOOL:
		break;
	case SIM_TOOL:
		break;
	case SIM_MODE:
		pAct = new ValidateCircuit(this, ActType);
		break;
	case Create_TruthTable:
		pAct = new CreateTruthTable(this, ActType);
		break;
	case SIMU:
		pAct = new SimulateCircuit(this, ActType);
		break;
	case PROB:
		break;
	case IF_VALID:
		pAct = new SimMode(this, ActType);
		break;
	case DSN_MODE:
		pAct = new DesignMode(this, ActType);
		break;
	case EXIT:
		///TODO: create ExitAction here
		break;
	}
	if (pAct)
	{
		pAct->Execute();
		//delete pAct; //I did this comment because this delete causes an error for the UNDO&REDO actions!
		pAct = NULL;
	}
}

/////////////////////////////////////////////////////////////////////
void ApplicationManager::UndoTheAction()
{
	Node *UndoedAction = Actions->Pop();
	if (UndoedAction != NULL)
	{
		UndoedActions->Push(UndoedAction);
		UndoedAction->ActionExecuted->Undo();
	}
}

/////////////////////////////////////////////////////////////////////
void ApplicationManager::RedoTheAction()
{
	Node* RedoedAction = UndoedActions->Pop();

	if (RedoedAction != NULL)
	{
		Actions->Push(RedoedAction);
		RedoedAction->ActionExecuted->Redo();
	}
}

/////////////////////////////////////////////////////////////////////
void ApplicationManager::CreateAction(Action* pAct)
{
	//Push action
	Node *Action = new Node;
	Action->ActionExecuted = pAct;
	Actions->Push(Action);
}

///////////////////////////////////////////////////////////////////////
void ApplicationManager::DeOperate()
{
	for (int i = 0; i < CompCount; i++)
	{
		CompList[i]->CancelOperation();
	}
}

////////////////////////////////////////////////////////////////////
void ApplicationManager::UpdateInterface()
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->GetCompType() == iCONNECTION && !(UI.AppMode == SIMULATION))
		{
			if (((Connection*)CompList[i])->getSrcGate() == NULL || ((Connection*)CompList[i])->getDestGate() == NULL || ((Connection*)CompList[i])->getDestGate() == ((Connection*)CompList[i])->getSrcGate() || ((Connection*)CompList[i])->getSrcGate()->GetCompType() == iLED || ((Connection*)CompList[i])->getDestGate()->GetCompType() == SWTCH) {
				((Connection*)CompList[i])->DrawError(OutputInterface);
				continue;
			}
		}
		else if ((CompList[i]->GetCompType() == SWTCH || CompList[i]->GetCompType() == iLED || CompList[i]->GetCompType() == iCONNECTION) && UI.AppMode == SIMULATION) {
			CompList[i]->DrawHi(OutputInterface);
			continue;
		}
		CompList[i]->Draw(OutputInterface);
	}
}

/////////////////////////////////////////////////////////////////////
void ApplicationManager::UpdateIntr()
{
	OutputInterface->ClearDrawingArea();
	for (int i = 0; i < CompCount; i++)
	{
		CompList[i]->Draw(OutputInterface);
	}
}

/////////////////////////////////////////////////////////////////////
void ApplicationManager::UpdateIntra()
{
	OutputInterface->ClearDrawingArea();
	for (int i = 0; i < CompCount; i++)
	{
		CompList[i]->Draw(OutputInterface);
	}
}

////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

////////////////////////////////////////////////////////////////////
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
	//delete Actions;
	//delete UndoedActions;
}

/////////////////////////////////////////////////////////////////////
void ApplicationManager::ConnectionsLinked(Component*iComp, int *&SrcConnections, int*&DistConnections, int&SrcCount, int&DstCount) 
{
	int SrcInd = 0, DstInd = 0;
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->GetCompType() == iCONNECTION) {
			if (((Connection*)CompList[i])->getDestGate() == iComp) {
				DistConnections[DstInd] = i;
				DstInd++;
			}
			if (((Connection*)CompList[i])->getSrcGate() == iComp) {
				SrcConnections[SrcInd] = i;
				SrcInd++;
			}
		}
	}
	SrcCount = SrcInd;
	DstCount = DstInd;
}

/////////////////////////////////////////////////////////////////////
void ApplicationManager::Save(ofstream &output_f)
{
	output_f << CompCount << endl;
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->GetCompType() != iCONNECTION)  //checking that component is not a connection
		{
			CompList[i]->Save(output_f);
		}
	}
	output_f << endl;
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->GetCompType() == iCONNECTION)  //checking that component is a connection
		{
			CompList[i]->Save(output_f);
		}
	}
	output_f << -1;
}

////////////////////////////////////////////////////////////////////////
void ApplicationManager::CheckDirectionConnection(ConnectionCases &cS, int ClickedIndx, int**&CrnrArr, GraphicsInfo r_GfxInfo, int &xAvg, int&DistPin, int &xStart, int &xEnd, int &xEndi, int &yEnd, int &yEndi, int &yStart, int &deltaX, int &deltaY) {
	if (ClickedIndx != -1 && CompList[ClickedIndx]->GetCompType() != iCONNECTION) {
		// Here xStart & yStart are initialized with the coordinates of the output pin of the gate selected. "Neat sketch requirement"
		if (ClickedIndx != -1 && r_GfxInfo.x1 < CompList[ClickedIndx]->getGfxInfo().x2 - 10) {
			cS = rGATEGATE;
			if (CompList[ClickedIndx]->getNoInp() == 3) {
				if (r_GfxInfo.y1 >= ((CompList[ClickedIndx]->getGfxInfo()).y1) + 27) {
					if (r_GfxInfo.y1 >= ((CompList[ClickedIndx]->getGfxInfo()).y1) + 29) {
						yStart = CrnrArr[0][1] = CompList[ClickedIndx]->getGfxInfo().y1 + 29;
						DistPin = 3;
					}
					if (r_GfxInfo.y1 < ((CompList[ClickedIndx]->getGfxInfo()).y1) + 29) {
						yStart = CrnrArr[0][1] = CompList[ClickedIndx]->getGfxInfo().y1 + 29;
						DistPin = 3;
					}
				}
				else if (r_GfxInfo.y1 <= ((CompList[ClickedIndx]->getGfxInfo()).y1) + 15) {
					if (r_GfxInfo.y1 >= ((CompList[ClickedIndx]->getGfxInfo()).y1) + 11) {
						yStart = CrnrArr[0][1] = CompList[ClickedIndx]->getGfxInfo().y1 + 11;
						DistPin = 1;
					}
					if (r_GfxInfo.y1 < ((CompList[ClickedIndx]->getGfxInfo()).y1) + 11) {
						yStart = CrnrArr[0][1] = CompList[ClickedIndx]->getGfxInfo().y1 + 11;
						DistPin = 1;
					}
				}
				else if (r_GfxInfo.y1 > ((CompList[ClickedIndx]->getGfxInfo()).y1) + 15 && r_GfxInfo.y1 < ((CompList[ClickedIndx]->getGfxInfo()).y1) + 27) {
					if (r_GfxInfo.y1 >= ((CompList[ClickedIndx]->getGfxInfo()).y1) + 20) {
						yStart = CrnrArr[0][1] = CompList[ClickedIndx]->getGfxInfo().y1 + 20;
						DistPin = 2;
					}
					if (r_GfxInfo.y1 < ((CompList[ClickedIndx]->getGfxInfo()).y1) + 20) {
						yStart = CrnrArr[0][1] = CompList[ClickedIndx]->getGfxInfo().y1 + 20;
						DistPin = 2;
					}
				}
			}
			else if (CompList[ClickedIndx]->getNoInp() == 2) {
				if (r_GfxInfo.y1 >= ((CompList[ClickedIndx]->getGfxInfo()).y1) + 21) {
					if (r_GfxInfo.y1 >= ((CompList[ClickedIndx]->getGfxInfo()).y1) + 29) {
						yStart = CrnrArr[0][1] = CompList[ClickedIndx]->getGfxInfo().y1 + 29;
						DistPin = 2;
					}
					if (r_GfxInfo.y1 < ((CompList[ClickedIndx]->getGfxInfo()).y1) + 29) {
						yStart = CrnrArr[0][1] = CompList[ClickedIndx]->getGfxInfo().y1 + 29;
						DistPin = 2;
					}
				}
				else if (r_GfxInfo.y1 <= ((CompList[ClickedIndx]->getGfxInfo()).y1) + 20) {
					if (r_GfxInfo.y1 >= ((CompList[ClickedIndx]->getGfxInfo()).y1) + 11) {
						yStart = CrnrArr[0][1] = CompList[ClickedIndx]->getGfxInfo().y1 + 11;
						DistPin = 1;
					}
					if (r_GfxInfo.y1 < ((CompList[ClickedIndx]->getGfxInfo()).y1) + 11) {
						yStart = CrnrArr[0][1] = CompList[ClickedIndx]->getGfxInfo().y1 + 11;

						DistPin = 1;
					}
				}
			}
			else {
				if (r_GfxInfo.y1 >= ((CompList[ClickedIndx]->getGfxInfo()).y1) + 20) {
					yStart = CrnrArr[0][1] = CompList[ClickedIndx]->getGfxInfo().y1 + 20;
					DistPin = 1;
				}
				if (r_GfxInfo.y1 < ((CompList[ClickedIndx]->getGfxInfo()).y1) + 20) {
					yStart = CrnrArr[0][1] = CompList[ClickedIndx]->getGfxInfo().y1 + 20;
					DistPin = 1;
				}
			}
			xStart = CrnrArr[0][0] = CompList[ClickedIndx]->getGfxInfo().x1;
			deltaX = deltaY = 0; // Just initializing the change in x and y to zero as a start.
			xEnd = xAvg = xEndi = xStart;
			yEnd = yEndi = yStart; // The ending coordinates is the same as the starting ones as a start also.
		}
		else if (ClickedIndx != -1) {
			cS = GATEGATE;
			if (CompList[ClickedIndx]->GetCompType() == SWTCH) {
				xStart = CrnrArr[0][0] = CompList[ClickedIndx]->getGfxInfo().x2;
				yStart = CrnrArr[0][1] = CompList[ClickedIndx]->getGfxInfo().y2 - 10;
				deltaX = deltaY = 0; // Just initializing the change in x and y to zero as a start.
				xEnd = xAvg = xEndi = xStart;
				yEnd = yEndi = yStart; // The ending coordinates is the same as the starting ones as a start also.
			}
			else {
				xStart = CrnrArr[0][0] = CompList[ClickedIndx]->getGfxInfo().x2;
				yStart = CrnrArr[0][1] = CompList[ClickedIndx]->getGfxInfo().y2 - 20;
				deltaX = deltaY = 0; // Just initializing the change in x and y to zero as a start.
				xEnd = xAvg = xEndi = xStart;
				yEnd = yEndi = yStart; // The ending coordinates is the same as the starting ones as a start also.
			}
		}
	}
	else 
	{
		cS = AIRGATE;
		xStart = xEnd = xAvg = xEndi = r_GfxInfo.x1;
		yStart = yEnd = yEndi = r_GfxInfo.y1;
		deltaX = deltaY = 0;


		CrnrArr[0][0] = r_GfxInfo.x1;
		CrnrArr[0][1] = r_GfxInfo.y1; // Obviously all previous events will be same as above but case taking a branch from a connection or drawing in an empty place.

		OutputInterface->getWindow()->SetPen(BLACK, 2);
		OutputInterface->getWindow()->SetBrush(BLACK);
		OutputInterface->getWindow()->DrawCircle(r_GfxInfo.x1, r_GfxInfo.y1, 3, FILLED); // Drawing a small filled circle to indicate a branch.
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ApplicationManager::CheckErrorConnection(Connection*Cmp, int Index)
{
	//bool Check;
	if (Cmp == NULL) {
		/*if (((Connection*)CompList[CompCount - 1])->getDestGate() != NULL) {
			Check = ((Connection*)CompList[CompCount - 1])->getDestGate()->setPrevious(((Connection*)CompList[CompCount - 1])->getSrcGate());
		}
		else {
			return true;
		}*/
		if ( ((Connection*)CompList[CompCount - 1])->getSrcGate() == NULL || ((Connection*)CompList[CompCount - 1])->getSrcGate()->getOutPin()->getConnNum() == 5 || ((Connection*)CompList[CompCount - 1])->getDestGate() == NULL || ((Connection*)CompList[CompCount - 1])->getDestGate() == ((Connection*)CompList[CompCount - 1])->getSrcGate() || ((Connection*)CompList[CompCount - 1])->getSrcGate()->GetCompType() == iLED || ((Connection*)CompList[CompCount - 1])->getDestGate()->GetCompType() == SWTCH) {
			DeleteComponent(1);
			OutputInterface->PrintMsg("Connection was deleted due to an error!");
			return true;
		}
	}
	else {
		if (((Connection*)CompList[Index])->getSrcGate() == NULL || ((Connection*)CompList[Index])->getSrcGate()->getOutPin()->getConnNum() == 5 || ((Connection*)CompList[Index])->getDestGate() == NULL || ((Connection*)CompList[Index])->getDestGate() == ((Connection*)CompList[Index])->getSrcGate() || ((Connection*)CompList[Index])->getSrcGate()->GetCompType() == iLED || ((Connection*)CompList[Index])->getDestGate()->GetCompType() == SWTCH) {
			OutputInterface->PrintMsg("Edited Connection was deleted due to an error!");
			return true;
		}
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////
Component**ApplicationManager::CompSelected(int & NumSelected) {
	Component**CompListSel = new Component*[CompCount]; NumSelected = 0;
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->isSelected()) {
			CompListSel[NumSelected] = CompList[i];
			NumSelected++;
		}
	}
	return CompListSel;
}

///////////////////////////////////////////////////////////////////////
void ApplicationManager::BubbleSort() 
{
	for (int i = 0; i < CompCount - 1; ++i)
		for (int j = 0; j < CompCount - 1 - i - 1; ++j)
			if (CompList[j]->getID() > CompList[j + 1]->getID())
			{
				Component* temp = CompList[j];
				CompList[j] = CompList[j + 1];
				CompList[j + 1] = temp;
			}
}

///////////////////////////////////////////////////////////////////////
void ApplicationManager::incrCompCount()
{
	CompCount++;
}

////////////////////////////////////////////////////////////////////////
void ApplicationManager::decCompCount()
{
	CompCount--;
}