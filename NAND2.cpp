#include "NAND2.h"
#include "Components\Connection.h"
NAND2::NAND2(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	SEL = false;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	Type = NAND2in;
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
NAND2::NAND2(int r_FanOut) :Gate(2, r_FanOut)
{
	SEL = false;
	Type = NAND2in;
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


void NAND2::Operate()
{

	//caclulate the output status as the NANDing of the two input pins
	//Add you code here
	int counter = 0;
	for (int i = 0; i < m_Inputs; i++)
	{
		if (GetInputPinStatus(i + 1) == HIGH)
		{
			counter++;
		}
	}
	if (counter == m_Inputs)
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
// Draws 2-input NAND gate
void NAND2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawNAND2(m_GfxInfo, SEL);
}

void NAND2::setSEL()
{
	SEL = true;
}

void NAND2::deSEL()
{
	SEL = false;
}


void NAND2::DrawHi(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawNAND2(m_GfxInfo,true);
}


//returns status of outputpin
int NAND2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NAND2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NAND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

void NAND2::Save(ofstream &output_f)
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

int NAND2::getNoInp()
{
	return 2;
}

OutputPin * NAND2::getOutPin()
{
	return &m_OutputPin;
}
InputPin * NAND2::getInpPin()
{
	return m_InputPins;
}
void NAND2::Load(ifstream & output_f, Output*pOut)
{
	output_f >> ID >> m_Label >> m_GfxInfo.x1 >> m_GfxInfo.y1;
	m_GfxInfo.x2 = m_GfxInfo.x1 + 40;
	m_GfxInfo.y2 = m_GfxInfo.y1 + 40;
	if (m_Label != "$")
	{
		pOut->DrawLabel(m_Label, m_GfxInfo);
	}
}
Component * NAND2::Copy()
{
	Component *Copied = new NAND2;
	if (m_Label != "")
	{
		Copied->setCompLabel(m_Label);
	}
	Copied->setCompType(Type);
	Copied->deSEL();
	return Copied;
}
