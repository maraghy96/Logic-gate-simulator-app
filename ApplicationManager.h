#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Component.h"
#include"STACK.h"
#include "Actions\AddANDgate2.h"
#include "AddORgate2.h"
#include "AddINV.h"
#include "AddANDgate3.h"
#include "AddORgate3.h"
#include "AddNANDgate2.h"
#include"AddNANDgate3.h"
#include "AddNORgate2.h"
#include "AddNORgate3.h"
#include "AddXORgate2.h"
#include "AddXORgate3.h"
#include "AddXNORgate2.h" 
#include"AddXNORgate3.h"
#include"AddSwitch.h"
#include"AddLabel.h"
#include"AddLED.h"
#include "SaveDesign.h"
#include "AddBUFF.h"
#include"UNDO.h"
#include"REDO.h"
#include"EditComp.h"
#include"COPY.h"
#include"CUT.h"
#include"PasteComp.h"
#include"SelectComp.h"
#include"DeSelectComp.h"
#include "MoveComp.h"
#include"AddConnection.h"
#include"LoadAct.h"
#include "EditConnection.h"
#include "MultiSelect.h"
#include"DemultiSelect.h"
#include "SimMode.h"
#include "DesignMode.h"
#include"SimulateCircuit.h"
#include"OperateSWTCH.h"
#include"CreateTruthTable.h"
#include"DELETE.h"
#include "Exit.h"
#include "ValidateCircuit.h"
//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxCompCount = 200 };	//Max no of Components	

private:

	//Data Members
	int CompCount;		//Actual number of Components
	int CompDeleted;   //Actual number of Components deleted
	int ComponentsSelected; //Actual number of Components selected
	int CompsSelectedIndex[MaxCompCount];//Array of indexes of selected components
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)
	Component* DelCompList[MaxCompCount]; //List of all Deleted Components
	Stack*Actions; //Stack of actions performed
	Stack* UndoedActions; //Stack of actions undoed
	Stack* OperationMode;//Stack of operating switches
	StackPaste* CopiedComps; //Stack of indexes of copied components
	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Clase Interface

public:
	ApplicationManager(); //constructor

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();

	//Creates an action and executes it
	void ExecuteAction(ActionType);

	void UpdateInterface();	//Redraws all the drawing window

	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();


	//Functions Added
	/////////////////////////////////////////////////////////////////////////
	void UpdateIntr();	//Clears then Draws

	void UpdateIntra();

	int ClickedIndx(GraphicsInfo GfsInfo);

	int ClickedIndxMove(GraphicsInfo GfsInfo);

	int ClickedIndx2(GraphicsInfo GfsInfo);

	Component** getCompList();  //returns array of components

	int getCompCount() const;  //returns actual number of components

	void ResetApplication();//Resets Everything!

	void UndoTheAction();    //Undo an Action

	void RedoTheAction();    //Redo an action

	Component** getDelCompList();   //returns array of deleted components

	Stack* getUndoedActions();  //returns the stack of undoed actions

	Stack* getActions();  //returns stack of actions

	Stack* getOperationStack();//returns stack of operations for simulation mode

	StackPaste* getCopyCutIndex(); //Returns stack of indexes 

	int getCompDeleted() const;  //returns actual number of components deleted

	int getCompSelected()const; //returs actual number of components selected

	void DeleteComponent();     //Delete last component

	void DeleteComponent(int x); //Overloaded Delete Function For error case while Drawing Connection!

	void RedoComponent();//Redo The Component

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

	//Reset all the components
	void DeOperate();

	//Pushes new action into the stack of actions
	void CreateAction(Action* pAct);

	//A function that returns the index of component in the components list
	int WhichComp(int Cx, int Cy);

	//This function takes an ID as a parameter and returns the index of the component having this ID
	int IDForWhichComp(int id);

	//A function that returns comp index
	int WhichCompClicked(int Cx, int Cy);

	//This function returns an array of pointers to indeces of selected components
	int* WhichCompSelected();

	//This function returns the index of the click component
	int WhichCompClicked();

	//This function counts the selected components but should be removed
	int CountSelected();

	//This function counts the number of connections
	int CountConnections();

	//This function resets the Switches
	void ResetSwitchesAndLEDs();

	//This Function counts number of inputs
	int getNumInputs() const;

	//This function counts number of outputs
	int getNumOutputs() const;

	//This functions checks if overlapping of a component occurs
	void OverlappingComp(int &Cx, int &Cy);

	//This function checks overlapping for a bunch of components
	bool CheckBunchOverlapping(GraphicsInfo GInfo);

	bool CheckBunchOverlapping(GraphicsInfo GInfo, Component * moveCmp);

	//Saving Design
	void Save(ofstream &output_f);

	void CheckDirectionConnection(ConnectionCases & cS, int ClickedIndx, int **& CrnrArr, GraphicsInfo r_GfxInfo, int & xAvg, int & DistPin, int & xStart, int & xEnd, int & xEndi, int & yEnd, int & yEndi, int & yStart, int & deltaX, int & deltaY);

	bool CheckErrorConnection(Connection * Cmp = NULL, int Index = -1);

	void ConnectionsLinked(Component * iComp, int *& SrcConnections, int *& DistConnections, int & SrcCount, int & DstCount);

	Component ** CompSelected(int & NumSelected);

	void Deleting(int deletions[], int &countt, Component**undos, int &dos, int &dels, int undosC[], int delsc);

	void  BubbleSort();

	void decCompCount();

	void incrCompCount();

	//destructor
	~ApplicationManager();
};
#endif