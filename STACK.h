#pragma once
#ifndef _Stack_H
#define _Stack_H
#include"Actions\Action.h"
#include"CMUgraphicsLib\CMUgraphics.h"

class Component;

struct Node
{
	Action* ActionExecuted;
	Node* next;
};

////////////////////////////////////////////////////////////////////
struct NodePaste
{
	Component *Comp;
	ActionType ActType;
	NodePaste* next;
	int CompIndex;
};

///////////////////////////////////////////////////////////////////
class Stack
{
	Node* Top;
	int Count;
public:
	Stack();
	void Push(Node* addedNode);
	Node* Pop();
	void EmptyStack();
	Node* StackTop();
	bool isEmpty();
	~Stack();
};
/////////////////////////////////////////////////////////////
class StackPaste
{
	NodePaste* Top;
	int Count;
public:
	StackPaste();
	void Push(NodePaste* addedNode);
	NodePaste* Pop();
	void EmptyStack();
	NodePaste* StackTop();
	bool isEmpty();
	~StackPaste();
};
#endif
