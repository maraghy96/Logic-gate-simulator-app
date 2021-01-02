#include "NOT.h"
#include "Components\Connection.h"
NOT::NOT(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut)
{
	SEL = false;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	Type = Inv;
	Previous = new Component*[1];
	for (int i = 0; i < 1; i++)
	{
		Previous[i] = NULL;
	}
	Next = new Component*[AND2_FANOUT];
	for (int i = 0; i < (AND2_FANOUT); i++)
	{
		Next[i] = NULL;
	}
}

NOT::NOT(int r_FanOut) :Gate(1, r_FanOut)
{
	SEL = false;
	Type = Inv;
	Previous = new Component*[1];
	for (int i = 0; i < 1; i++)
	{
		Previous[i] = NULL;
	}
	Next = new Component*[AND2_FANOUT];
	for (int i = 0; i < (AND2_FANOUT); i++)
	{
		Next[i] = NULL;
	}
}


void NOT::Operate()
{

	//caclulate the output status as the NOTing of the input pin
	//Add you code here
	int counter = 0;
	if (GetInputPinStatus(1) == HIGH)
	{
		m_OutputPin.setStatus(LOW);

	}
	else
	{
		m_OutputPin.setStatus(HIGH);

	}
	for (int i = 0; i < m_OutputPin.getConnNum(); i++) {
		((Connection*)m_OutputPin.getConnections()[i])->Operate();
	}
	Operated = true;
}


// Function Draw
// Draws 1-input NOT gate
void NOT::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawINV(m_GfxInfo, SEL);
}

void NOT::setSEL()
{
	SEL = true;
}

void NOT::deSEL()
{
	SEL = false;
}

void NOT::DrawHi(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawINV(m_GfxInfo,true);
}

//returns status of outputpin
int NOT::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NOT::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NOT::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

void NOT::Save(ofstream &output_f)
{
	//Don't forget to add the label!
	if (m_Label == "")
	{
		output_f << Type << "\t" << ID << "\t" << "$" << "\t" << m_GfxInfo.x1 << "\t" << m_GfxInfo.y1 << endl;
	}
	else
	{
		output_f << Type << "\t" << ID << "\t" << m_Label << "\t" << m_GfxInfo.x1 << "\t" << m_GfxInfo.y1 << endl;
	}
	output_f << endl;
}

int NOT::getNoInp()
{
	return 1;
}

OutputPin * NOT::getOutPin()
{
	return &m_OutputPin;
}
InputPin * NOT::getInpPin()
{
	return m_InputPins;
}
void NOT::Load(ifstream & output_f, Output*pOut)
{

	output_f >> ID >> m_Label >> m_GfxInfo.x1 >> m_GfxInfo.y1;
	m_GfxInfo.x2 = m_GfxInfo.x1 + 40;
	m_GfxInfo.y2 = m_GfxInfo.y1 + 40;
	if (m_Label != "$")
	{
		pOut->DrawLabel(m_Label, m_GfxInfo);
	}
}

Component * NOT::Copy()
{
	Component *Copied = new NOT;
	if (m_Label != "")
	{
		Copied->setCompLabel(m_Label);
	}
	Copied->setCompType(Type);
	Copied->deSEL();
	return Copied;
}
