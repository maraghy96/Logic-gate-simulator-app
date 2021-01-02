#include "XOR3.h"
#include "Components\Connection.h"
XOR3::XOR3(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut)
{
	SEL = false;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	Type = XOR3in;
	Previous = new Component*[3];
	for (int i = 0; i < 3; i++)
	{
		Previous[i] = NULL;
	}
	Next = new Component*[AND2_FANOUT];
	for (int i = 0; i < (AND2_FANOUT); i++)
	{
		Next[i] = NULL;
	}
}

XOR3::XOR3(int r_FanOut) :Gate(3, r_FanOut)
{
	SEL = false;
	Type = XOR3in;
	Previous = new Component*[3];
	for (int i = 0; i < 3; i++)
	{
		Previous[i] = NULL;
	}
	Next = new Component*[AND2_FANOUT];
	for (int i = 0; i < (AND2_FANOUT); i++)
	{
		Next[i] = NULL;
	}
}

void XOR3::Operate()
{
	//caclulate the output status as the XORing of the two input pins
	//Add you code here
	int counter = 0;
	for (int i = 0; i < m_Inputs; i++)
	{
		if (GetInputPinStatus(i + 1) == HIGH)
		{
			counter++;
		}
	}
	if (counter % 2 != 0)
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
// Draws 3-input XOR gate
void XOR3::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawXOR3(m_GfxInfo, SEL);
}

void XOR3::setSEL()
{
	SEL = true;
}

void XOR3::deSEL()
{
	SEL = false;
}

void XOR3::DrawHi(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawXOR2(m_GfxInfo,true);
}

//returns status of outputpin
int XOR3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XOR3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

void XOR3::Save(ofstream &output_f)
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

int XOR3::getNoInp()
{
	return 3;
}

OutputPin * XOR3::getOutPin()
{
	return &m_OutputPin;
}
InputPin * XOR3::getInpPin()
{
	return m_InputPins;
}
void XOR3::Load(ifstream & output_f, Output*pOut)
{
	output_f >> ID >> m_Label >> m_GfxInfo.x1 >> m_GfxInfo.y1;
	m_GfxInfo.x2 = m_GfxInfo.x1 + 40;
	m_GfxInfo.y2 = m_GfxInfo.y1 + 40;
	if (m_Label != "$")
	{
		pOut->DrawLabel(m_Label, m_GfxInfo);
	}
}

Component * XOR3::Copy()
{
	Component *Copied = new XOR3;
	if (m_Label != "")
	{
		Copied->setCompLabel(m_Label);
	}
	Copied->setCompType(Type);
	Copied->deSEL();
	return Copied;
}