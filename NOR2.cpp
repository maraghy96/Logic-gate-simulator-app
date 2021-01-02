#include "NOR2.h"
#include "Components\Connection.h"
NOR2::NOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	SEL = false;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	Type = NOR2in;
	Previous = new Component*[2];
	for (int i = 0; i < 2; i++)
	{
		Previous[i] = NULL;
	}
	Next = new Component*[AND2_FANOUT];
	for (int i = 0; i < (AND2_FANOUT); i++)
	{
		Next[i] = NULL;
	}
}

NOR2::NOR2(int r_FanOut) :Gate(2,r_FanOut)
{
	SEL = false;
	Type = NOR2in;
	Previous = new Component*[2];
	for (int i = 0; i < 2; i++)
	{
		Previous[i] = NULL;
	}
	Next = new Component*[AND2_FANOUT];
	for (int i = 0; i < (AND2_FANOUT); i++)
	{
		Next[i] = NULL;
	}
}


void NOR2::Operate()
{
	//caclulate the output status as the NORing of the two input pins
	//Add you code here
	int counter = 0;
	for (int i = 0; i < m_Inputs; i++)
	{
		if (GetInputPinStatus(i + 1) == HIGH)
		{
			m_OutputPin.setStatus(LOW);
			counter++;
			break;
		}

	}
	if (counter == 0)
	{
		m_OutputPin.setStatus(HIGH);

	}
	for (int i = 0; i < m_OutputPin.getConnNum(); i++) 
	{
		((Connection*)m_OutputPin.getConnections()[i])->Operate();
	}
	Operated = true;

}


// Function Draw
// Draws 2-input NOR gate
void NOR2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawNOR2(m_GfxInfo, SEL);
}

void NOR2::setSEL()
{
	SEL = true;
}

void NOR2::deSEL()
{
	SEL = false;
}


void NOR2::DrawHi(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawNOR2(m_GfxInfo,true);
}


//returns status of outputpin
int NOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

void NOR2::Save(ofstream &output_f)
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

int NOR2::getNoInp()
{
	return 2;
}

OutputPin * NOR2::getOutPin()
{
	return &m_OutputPin;
}
InputPin * NOR2::getInpPin()
{
	return m_InputPins;
}
void NOR2::Load(ifstream & output_f, Output*pOut)
{
	output_f >> ID >> m_Label >> m_GfxInfo.x1 >> m_GfxInfo.y1;
	m_GfxInfo.x2 = m_GfxInfo.x1 + 40;
	m_GfxInfo.y2 = m_GfxInfo.y1 + 40;
	if (m_Label != "$")
	{
		pOut->DrawLabel(m_Label, m_GfxInfo);
	}
}

Component * NOR2::Copy()
{
	Component *Copied = new NOR2;
	if (m_Label != "")
	{
		Copied->setCompLabel(m_Label);
	}
	Copied->setCompType(Type);
	Copied->deSEL();
	return Copied;
}