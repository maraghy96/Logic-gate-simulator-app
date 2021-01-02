#include"SWITCH.h"
#include "Components\Connection.h"

SWITCH::SWITCH(const GraphicsInfo &r_GfxInfo, int r_FanOut) :s_OutputPin(r_FanOut)
{
	SEL = false;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	s_OutputPin.setStatus(LOW);
	Type = SWTCH;
	Previous = NULL;
	Operated = true;
	Next = new Component*[AND2_FANOUT];
	for (int i = 0; i < (AND2_FANOUT); i++)
	{
		Next[i] = NULL;
	}
	Set = false;
}

SWITCH::SWITCH(int r_FanOut) :s_OutputPin(r_FanOut)
{
	SEL = false;
	s_OutputPin.setStatus(LOW);
	Type = SWTCH;
	Previous = NULL;
	Operated = true;
	Next = new Component*[AND2_FANOUT];
	for (int i = 0; i < (AND2_FANOUT); i++)
	{
		Next[i] = NULL;
	}
	Set = false;
}

void SWITCH::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawSWITCH(m_GfxInfo, SEL);
}

void SWITCH::setSEL()
{
	SEL = true;
}

void SWITCH::deSEL()
{
	SEL = false;
}

void SWITCH::DrawHi(Output* pOut)
{
	if (GetOutPinStatus() == HIGH) {
		pOut->DrawSWITCHSIM(m_GfxInfo, true);
	}
	else {
		pOut->DrawSWITCHSIM(m_GfxInfo);
	}
}

int SWITCH::GetOutPinStatus()
{
	return s_OutputPin.getStatus();
}

void SWITCH::Operate()
{
	//int x, y;
	//clicktype c;
	//c = pWind->GetMouseClick(x, y);
	//if ((x >= m_GfxInfo.x1 && x <= m_GfxInfo.x2) && (y >= m_GfxInfo.y1 && y <= m_GfxInfo.y2))
	Operated = true;
	if (s_OutputPin.getStatus() == LOW)
	{
		s_OutputPin.setStatus(HIGH);
	}
	else
	{
		s_OutputPin.setStatus(LOW);

	}
	for (int i = 0; i < s_OutputPin.getConnNum(); i++) {
		((Connection*)s_OutputPin.getConnections()[i])->Operate();
	}
}
//returns status of Inputpin #n
int SWITCH::GetInputPinStatus(int n)
{
	return -1;
}

//Set status of an input pin to HIGH or LOW
void SWITCH::setInputPinStatus(int n, STATUS s)
{
	return;
}
void SWITCH::Save(ofstream &output_f)
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

void SWITCH::Load(ifstream & output_f, Output*pOut)
{
	output_f >> ID >> m_Label >> m_GfxInfo.x1 >> m_GfxInfo.y1;
	m_GfxInfo.x2 = m_GfxInfo.x1 + 40;
	m_GfxInfo.y2 = m_GfxInfo.y1 + 40;
	if (m_Label != "$")
	{
		pOut->DrawLabel(m_Label, m_GfxInfo);
	}
}

Component * SWITCH::Copy()
{
	Component *Copied = new SWITCH;
	if (m_Label != "")
	{
		Copied->setCompLabel(m_Label);
	}
	Copied->setCompType(Type);
	Copied->deSEL();
	return Copied;
}

OutputPin SWITCH::getOutiPin()
{
	return s_OutputPin;
}

InputPin * SWITCH::getInpPin()
{
	return nullptr;
}

OutputPin * SWITCH::getOutPin()
{
	return &s_OutputPin;
}

bool SWITCH::isSet()
{
	return Set;
}

void SWITCH::setSwitchStatus()
{
	Set = true;
}

void SWITCH::setOutputPinStatus(STATUS s)
{
	s_OutputPin.setStatus(s);
	for (int i = 0; i < s_OutputPin.getConnNum(); i++) {
		((Connection*)s_OutputPin.getConnections()[i])->Operate();
	}
	Operated = false;
}

void SWITCH::ResetSwitch()
{
	Set = false;
}
