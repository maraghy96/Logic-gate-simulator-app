#ifndef CONST_H
#define CONST_H
//This header file contains some defenitions to be used all over the application

//All possible actions
enum ActionType
{
	ADD_Buff,			//Add 1-input Buffer gate
	ADD_INV,			//Add 1-input Inverter gate
	ADD_AND_GATE_2,		//Add 2-input AND gate
	ADD_OR_GATE_2,		//Add 2-input OR gate
	ADD_NAND_GATE_2,	//Add 2-input NAND gate
	ADD_NOR_GATE_2,		//Add 2-input NOR gate
	ADD_XOR_GATE_2,		//Add 2-input XOR gate
	ADD_XNOR_GATE_2,	//Add 2-input XNOR gate
	ADD_AND_GATE_3,		//Add 3-input AND gate
	ADD_OR_GATE_3,      //Add 3-input OR gate
	ADD_NAND_GATE_3,    //Add 3-input NAND gate
	ADD_NOR_GATE_3,		//Add 3-input NOR gate
	ADD_XOR_GATE_3,		//Add 3-input XOR gate
	ADD_XNOR_GATE_3,    //Add 3-input XNOR gate
	ADD_Switch,			//Add Switch
	ADD_LED,			//Add LED
	ADD_CONNECTION,		//Add Wire Connection

	ADD_Label,			//Add Label to a Component, a Connection
	EDIT_Label,			//Edit Label of a Component, a Connection

	Create_TruthTable,	//Create Truth Table of the Circuit
	IF_VALID,
	PROB,
	SIMU,
	Change_Switch,		//Change Switch Status in Simulation Mode

	OperateSWTCH,
	MULTISELECT,	//Select a Component, a Connection
	SEL,
	DESEL,
	DEMULTISEL,
	LABEL,
	DEL,		//Delete a Component, a Connection
	MOVE,		//Move a Component, a Connection
	CUT,
	COPY,
	PASTE,

	SAVE,		//Save the whole Circuit to a file
	LOAD,		//Load a Circuit from a file
	CLEAR,

	UNDO,		//Undo the last Action preformed
	REDO,		//Redo the last Action canceled

	DSN_MODE,	//Switch to Design mode
	SIM_MODE,	//Switch to Simulatiom mode

	EXIT,		//Exit the application

	STATUS_BAR,		//A click on the status bar
	DSN_TOOL,	//A click on an empty place in the design tool bar
	SIM_TOOL,

};

//Possible Status for the pin
enum STATUS
{
	LOW,
	HIGH
};

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};


enum DsgnMenuItem //The items of the design menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_AND2,		//AND gate item in menu
	ITM_OR2,		//OR gate item in menu
	ITM_INV,
	ITM_OR3,
	ITM_AND3,
	ITM_NOR2,
	ITM_NAND2,
	ITM_NOR3,
	ITM_NAND3,
	ITM_XOR2,
	ITM_XNOR2,
	ITM_XOR3,
	ITM_XNOR3,
	ITM_BUFF,
	ITM_LED,
	ITM_SWITCH,
	ITM_CONNECTION,
	ITM_SIM,
	ITM_LOAD,
	ITM_SAVE,
	ITM_COPY,
	ITM_CUT,
	ITM_PASTE,
	ITM_MOVE,
	ITM_DEL,
	ITM_CLEAR,
	ITM_REDO,
	ITM_UNDO,
	ITM_LABEL,
	ITM_SEL,
	ITM_MULTIS,
	ITM_DESEL,
	ITM_DEMULTISEL,
	ITM_EXIT,		//Exit item
					//TODO: Add more items names here

					ITM_DSN_CNT		//no. of design menu items ==> This should be the last line in this enum

};

enum CompType
{
	AND2in,
	AND3in,
	OR2in,
	OR3in,
	Inv,
	Buff,
	NAND2in,
	NAND3in,
	NOR2in,
	NOR3in,
	XOR2in,
	XOR3in,
	XNOR2in,
	XNOR3in,
	iLED,
	SWTCH,
	iCONNECTION,
};

enum SimMenuItem //The items of the simulation menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//Simulate menu item
	ITM_TRUTH,	//Truth table menu item
	ITM_VALID,
	ITM_PROB,
	ITM_SIMU,
	ITM_SWITCH_DSN,
	//TODO:Add more items names here

	ITM_SIM_CNT		//no. of simulation menu items ==> This should be the last line in this enum

};

//Maximum number of input pins that can be connected to any output pin
#define MAX_CONNS 20

//assume fan out is 5 for now it can be read from the user or can be predefined as const
enum FANOUT
{
	AND2_FANOUT = 5	//Default fan out of 2-input AND gate
};

//A structure to contain drawing parameters for each component
//Each component occupies a rectangluar area so it needs 2 points to represent that area
//this structure can be extended if desired
struct GraphicsInfo
{
	int x1, y1, x2, y2;
};

#ifndef NULL
#define NULL 0
#endif

#endif