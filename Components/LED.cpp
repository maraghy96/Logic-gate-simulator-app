#include "LED.h"

LED::LED(const GraphicsInfo & r_GfxInfo)
{
	SEL = false;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	Type = iLED;
	Previous = new Component*[1];
	for (int i = 0; i < 1; i++)
	{
		Previous[i] = NULL;
	}
	AttachedConnection = NULL;
	Next = NULL;
	Taken = false;
}

LED::LED()
{
	SEL = false;
	Type = iLED;
	AttachedConnection = NULL;
	Previous = new Component*[1];
	for (int i = 0; i < 1; i++)
	{
		Previous[i] = NULL;
	}
	Next = NULL;
	Taken = false;

}

void LED::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawLED(m_GfxInfo, SEL);
}

void LED::setSEL()
{
	SEL = true;
}

void LED::deSEL()
{
	SEL = false;
}


void LED::DrawHi(Output * pOut)
{
	if (GetInputPinStatus(1) == HIGH) {
		pOut->DrawLEDSIMU(m_GfxInfo, true);
	}
	else {
		pOut->DrawLEDSIMU(m_GfxInfo);
	}
}

void LED::Operate()
{
	Operated = true;

}

void LED::Save(ofstream &output_f)
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

int LED::GetInputPinStatus(int n)
{
	return m_InputPin.getStatus();
}

void LED::setInputPinStatus(int n, STATUS s)
{
	m_InputPin.setStatus(s);
}

int LED::GetOutPinStatus()
{
	return -1;
}

int LED::getNoInp()
{
	return 1;
}
void LED::Load(ifstream & output_f, Output*pOut)
{
	output_f >> ID >> m_Label >> m_GfxInfo.x1 >> m_GfxInfo.y1;
	m_GfxInfo.x2 = m_GfxInfo.x1 + 40;
	m_GfxInfo.y2 = m_GfxInfo.y1 + 40;
	if (m_Label != "$")
	{
		pOut->DrawLabel(m_Label, m_GfxInfo);
	}
}

Component * LED::Copy()
{
	Component *Copied = new LED;
	if (m_Label != "")
	{
		Copied->setCompLabel(m_Label);
	}
	Copied->setCompType(Type);
	Copied->deSEL();
	return Copied;
}

InputPin LED::getInpiPin()
{
	return m_InputPin;
}

InputPin * LED::getInpPin()
{
	return &m_InputPin;
}

OutputPin * LED::getOutPin()
{
	return nullptr;
}

void LED::Take()
{
	Taken = true;
}

bool LED::isTaken()
{
	return Taken;
}

void LED::ResetLed()
{
	Taken = false;
}
