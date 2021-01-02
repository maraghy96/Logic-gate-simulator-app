#ifndef _ACTION_H
#define _ACTION_H

class ApplicationManager; //forward class declaration
enum ActionType;
enum clicktype;

//Base class for all possible actions (abstract class)
class Action
{
protected:
	ApplicationManager *pManager;	//Actions needs AppMngr to do their job
	ActionType Act_Type;  //Action type
	clicktype Ctype;
public:
	Action(ApplicationManager *pApp,ActionType type) //constructor
	{
		pManager = pApp;
		Act_Type = type;
	}	
	
	//Reads parameters required for action to execute
	virtual void ReadActionParameters()=0;
	
	//Execute action (code depends on action type)
	virtual void Execute()=0;

	//To undo this action (code depends on action type)
	virtual void Undo()=0;

	//To redo this action (code depends on action type)
	virtual void Redo()=0;
	
	//Returns type of the action
	ActionType getActionType() const
	{
		return Act_Type;
	}

	//Returns click type
	clicktype GetClickType()
	{
		return Ctype;
	}
};
#endif