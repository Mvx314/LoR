#include "dxstdafx.h"
#include "../SrcGame/Global.h"
#include "../SrcInterface/ToolTip.h"

CToolTip::CToolTip()
{
	m_data.Clear();
}

CToolTip::~CToolTip()
{
}
void CToolTip::AddLine(const std::string &p_line)
{
	m_data.AddLine(p_line);
}
void CToolTip::Draw()
{
	POINT l_pos;
	l_pos.x = 0;
	l_pos.y = 0;
	m_data.SetDepth(0.0f);
	m_data.SetPosition(l_pos);
	m_data.SetColor(0xFF00FF00);
	m_data.SetFont(g_Gfx.GetFont(2));
	double x = g_MouseHandler.GetMousePos().x-(int)g_Global.m_TTWidth;
	double y = g_MouseHandler.GetMousePos().y-((int)m_data.LineCount()*12+10);
	double w = g_Global.m_TTWidth;
	double h = m_data.LineCount()*12+10;
	if( x < 0) 
		x = 0;
	if( x > (g_Global.m_Width-w)) 
		x = (g_Global.m_Width-w);
	if( y < 0) 
		y = 0;
	if( y > (g_Global.m_Height-h)) 
		y = (g_Global.m_Height-h);
	l_pos.x = (int)x+5;
	l_pos.y = (int)y+5;
	m_data.SetPosition(l_pos);
	g_Gfx.m_textGroups.push_back(m_data);
	g_Gfx.MakeQuad(x,y,w,h,0.1f,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,false,g_Textures.m_MiscBG,1,0);
}
