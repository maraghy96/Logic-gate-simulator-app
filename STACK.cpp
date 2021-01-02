#include "Stack.h"

Stack::Stack()
{
	Top = NULL;
	Count = 0;
}

void Stack::Push(Node * addedNode)
{
	if (addedNode == NULL)
	{
		return;
	}
	if (Count == 0)
	{
		addedNode->next = NULL;
		Top = addedNode;
	}
	else
	{
		addedNode->next = Top;
		Top = addedNode;
	}
	Count++;
}

Node* Stack::Pop()
{
	if (Count == 0)
	{
		return NULL;
	}
	else
	{
		Node* PoppedNode = Top;
		Top = Top->next;
		Count--;
		return PoppedNode;
	}
}

Node * Stack::StackTop()
{
	if (Count != 0)
	{
		return Top;
	}
	else
	{
		return NULL;
	}
}

bool Stack::isEmpty()
{
	if (Count == 0)
	{
		return true;
	}
	return false;
}

void Stack::EmptyStack()
{
	if (Count == 0)
	{
		return;
	}
	while (Count > 0)
	{
		Pop();
	}
}
Stack::~Stack()
{
	Node* ptr = Top;
	while (ptr != NULL)
	{
		Top = Top->next;
		delete ptr;
		ptr = ptr->next;
		Count--;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
StackPaste::StackPaste()
{
	Top = NULL;
	Count = 0;
}

void StackPaste::Push(NodePaste * addedNode)
{
	if (addedNode == NULL)
	{
		return;
	}
	if (Count == 0)
	{
		addedNode->next = NULL;
		Top = addedNode;
	}
	else
	{
		addedNode->next = Top;
		Top = addedNode;
	}
	Count++;
}

NodePaste* StackPaste::Pop()
{
	if (Count == 0)
	{
		return NULL;
	}
	else
	{
		NodePaste* PoppedNode = Top;
		Top = Top->next;
		Count--;
		return PoppedNode;
	}
}

NodePaste * StackPaste::StackTop()
{
	if (Count != 0)
	{
		return Top;
	}
	else
	{
		return NULL;
	}
}

bool StackPaste::isEmpty()
{
	if (Count == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void StackPaste::EmptyStack()
{
	if (Count == 0)
	{
		return;
	}
	while (Count > 0)
	{
		Pop();
	}
}
StackPaste::~StackPaste()
{
	NodePaste* ptr = Top;
	while (ptr != NULL)
	{
		Top = Top->next;
		delete ptr;
		ptr = ptr->next;
		Count--;
	}
}

