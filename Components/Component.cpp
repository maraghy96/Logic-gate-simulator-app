#include "Component.h"

int Component::ComponentsCount = 0;


Component::Component(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;
	SEL = false;
	Operated = false;
	Labelled = false;
	ID = ++ComponentsCount;
	Clicked = false;
	Next = NULL;
}

Component ** Component::getPrevComp() const
{
	return Previous;
}

bool Component::isSelected()
{
	return SEL;
}

void Component::setGfxInfo(GraphicsInfo Ginfo)
{
	m_GfxInfo = Ginfo;
}

void Component::setPos(int iX, int iY)
{
	m_GfxInfo.x1 = iX;
	m_GfxInfo.y1 = iY;
	m_GfxInfo.y2 = m_GfxInfo.y1 + 40;
	m_GfxInfo.x2 = m_GfxInfo.x1 + 40;
}

GraphicsInfo Component::getGfxInfo()
{
	return m_GfxInfo;
}

int Component::getID() const
{
	return ID;
}

Component ** Component::getNext() const
{
	return Next;
}

void Component::setNext(Component * Comp)
{
	for (int i = 0; i < AND2_FANOUT; i++)
	{
		if (Next[i] == NULL)
		{
			Next[i] = Comp;
			return;
		}
	}
	return;
}

bool Component::setPrevious(Component * Comp)
{
	if (getNoInp() == 1)
	{
		if (getPrevComp()[0] == NULL)
		{
			Previous[0] = Comp;//Added Newly For Simulation
			return true;
		}
	}
	else if (getNoInp() == 2)
	{
		if (getPrevComp()[0] == NULL)
		{
			Previous[0] = Comp;//Added Newly For Simulation
			return true;
		}
		else if (getPrevComp()[1]==NULL)
		{
			Previous[1] = Comp;//Added Newly For Simulation
			return true;
		}
	}
	else if (getNoInp() == 3)
	{
		if (getPrevComp()[0] == NULL)
		{
			Previous[0] = Comp;//Added Newly For Simulation
			return true;
		}
		else if (getPrevComp()[1] == NULL)
		{
			Previous[1] = Comp;//Added Newly For Simulation
			return true;
		}
		else if(getPrevComp()[2]==NULL)
		{
			getPrevComp()[2] = Comp;//Added Newly For Simulation
			return true;
		}
	}
	return false;
}

void Component::resetPrevious(int index)
{
	if (index < AND2_FANOUT)
	{
		Previous[index] = NULL;
	}
}

void Component::resetNext(int index)
{
	if (index < AND2_FANOUT)
	{
		Next[index] = NULL;
	}
}

CompType Component::GetCompType() const
{
	return Type;
}

void Component::setCompType(CompType type)
{
	Type = type;
}

void Component::CancelOperation()
{
	Operated = false;
}

void Component::setOperated()
{
	Operated = true;
}

void Component::setConnection(Connection * Conn)
{
	AttachedConnection = Conn;
}

Connection * Component::getConnection() const
{
	return AttachedConnection;
}

void Component::setCompLabel(string sentence)
{
	Labelled = true;
	m_Label = sentence;
}

int Component::getNoInp()
{
	return 0;
}

bool Component::isClicked() const
{
	return Clicked;
}

bool Component::isOperated() const
{
	return Operated;
}

void Component::Click()
{
	Clicked = true;
}

void Component::CancelClick()
{
	Clicked = false;
}

string Component::getCompLabel() const
{
	return m_Label;
}

bool Component::isLabelled()
{
	return Labelled;
}

Component::Component()
{
	SEL = false;
	Labelled = false;
	ID = ++ComponentsCount;
	Clicked = false;
	Operated = false;
	Next = NULL;

}

OutputPin Component::getOutiPin()
{
	return OutputPin(2);
}

Component::~Component()
{
}

bool Component::getSEL() {
	return SEL;
}
int Component::getID()
{
	return ID;
}