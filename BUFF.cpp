#include "BUFF.h"
#include "Components\Connection.h"
BUFFER::BUFFER(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut)
{
	SEL = false;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	Type = Buff;
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
BUFFER::BUFFER(int r_Fanout) :Gate(1, r_Fanout)
{
	SEL = false;
	Type = Buff;
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


void BUFFER::Operate()
{
	//caclulate the output status as the BUFFERing of the 1 input pin
	//Add you code here
	if (GetInputPinStatus(1) == HIGH)
	{
		m_OutputPin.setStatus(HIGH);

	}
	else
	{
		m_OutputPin.setStatus(LOW);

	}
	for (int i = 0; i < m_OutputPin.getConnNum(); i++) {
		((Connection*)m_OutputPin.getConnections()[i])->Operate();
	}
	Operated = true;
}

// Function Draw
// Draws 1-input BUFFER gate
void BUFFER::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawBUFF(m_GfxInfo, SEL);
}

void BUFFER::setSEL()
{
	SEL = true;
}

void BUFFER::deSEL()
{
	SEL = false;
}


void BUFFER::DrawHi(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawBUFF(m_GfxInfo,true);
}

//returns status of outputpin
int BUFFER::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int BUFFER::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void BUFFER::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

void BUFFER::Save(ofstream &output_f)
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

int BUFFER::getNoInp()
{
	return 1;
}

OutputPin * BUFFER::getOutPin()
{
	return &m_OutputPin;
}
InputPin * BUFFER::getInpPin()
{
	return m_InputPins;
}
void BUFFER::Load(ifstream & output_f, Output*pOut)
{
	output_f >> ID >> m_Label >> m_GfxInfo.x1 >> m_GfxInfo.y1;
	m_GfxInfo.x2 = m_GfxInfo.x1 + 40;
	m_GfxInfo.y2 = m_GfxInfo.y1 + 40;
	if (m_Label != "$")
	{
		pOut->DrawLabel(m_Label, m_GfxInfo);
	}
}

Component * BUFFER::Copy()
{
	Component *Copied = new BUFFER;
	if (m_Label != "")
	{
		Copied->setCompLabel(m_Label);
	}
	Copied->setCompType(Type);
	Copied->deSEL();
	return Copied;
}
