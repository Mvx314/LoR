#include "dxstdafx.h"
#include "../SrcInterface/MiscButtons.h"
#include "../SrcInterface/GameStateData.h"

class CToolTip;

CGameObjectNull::CGameObjectNull()
{
}
POINT CGameObjectNull::ScreenSize()
{
	POINT l_pos = {g_Global.m_Width,g_Global.m_Height};
	return l_pos;
}
CButtonSetState::CButtonSetState(int p_x,int p_y,int p_width,int p_height,double p_depth,
							   enum GameStates p_newState,IDirect3DTexture9* p_graphic,std::string p_label,std::string p_toolTip) :
	m_newState(p_newState),
	m_graphic(p_graphic),
	m_label(p_label),
	m_toolTip(p_toolTip),
	m_depth(p_depth)
{
	m_x = p_x;
	m_y = p_y;
	m_width = p_width;
	m_height = p_height;
	Draw();
}
void CButtonSetState::Draw()
{
	g_Gfx.MakeQuad(m_x,m_y,m_width,m_height,m_depth,
					0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,true,m_graphic,1,1);
	CTextGroup l_tg(1,m_x,m_y,0xffffffff,g_Gfx.GetFont(7));
	l_tg.AddLine(m_label);
	g_Gfx.m_textGroups.push_back(l_tg);
}
void CButtonSetState::OnLeftClick()
{
	g_Global.SetState(m_newState,false);
	g_Global.LogInfo("BSSOLC");
}
void CButtonSetState::ToolTip()
{
	CToolTip l_tt;
	l_tt.AddLine(m_toolTip);
	l_tt.Draw();
}
CButtonSlider::CButtonSlider(UINT *p_variable,UINT p_min,UINT p_max,int p_x,int p_y,UINT p_width,UINT p_height,double p_depth) :
	m_variable(p_variable),
	m_min(p_min),
	m_max(p_max),
	m_depth(p_depth)
{
	m_x = p_x;
	m_y = p_y;
	m_width = p_width;
	m_height = p_height;
	Draw();
}
void CButtonSlider::Draw()
{
	if(m_width < m_height)
	{
	g_Gfx.MakeQuad(m_x,m_y,m_width,m_width,m_depth,
					0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,false,g_Textures.m_ArrowUp,1,1);
	g_Gfx.MakeQuad(m_x,(m_y+m_width+(*m_variable-m_min)*(m_height-2*m_width)/(m_max-m_min+1)),m_width,
					(double)((m_height-2*m_width)/(double)(m_max-m_min+1)),m_depth,
					0xFFFF00FF,0xFFFF00FF,0xFFFF00FF,0xFFFF00FF,false,g_Textures.m_Button,1,1);
	g_Gfx.MakeQuad(m_x,(m_y+m_height-m_width),m_width,m_width,m_depth,
					0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,false,g_Textures.m_ArrowDown,1,1);
	g_Gfx.MakeSquare(m_x,(m_y+m_width),m_width,(m_height-2*m_width),m_depth,
						0xFFFF00FF,0xFFFF00FF,0xFFFF00FF,0xFFFF00FF);
	}
	else
	{
	g_Gfx.MakeQuad(m_x,m_y,m_height,m_height,m_depth,
					0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,false,g_Textures.m_ArrowLeft,1,1);
	g_Gfx.MakeQuad((m_x+m_height+(*m_variable-m_min)*(m_width-2*m_height)/(m_max-m_min+1)),m_y,
					(double)((m_width-2*m_height)/(double)(m_max-m_min+1)),m_height,m_depth,
					0xFFFF00FF,0xFFFF00FF,0xFFFF00FF,0xFFFF00FF,false,g_Textures.m_Button,1,1);
	g_Gfx.MakeQuad((m_x+m_width-m_height),m_y,m_height,m_height,m_depth,
					0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,false,g_Textures.m_ArrowRight,1,1);
	g_Gfx.MakeSquare((m_x+m_height),m_y,(m_width-2*m_height),m_height,m_depth,
						0xFFFF00FF,0xFFFF00FF,0xFFFF00FF,0xFFFF00FF);
	}
}
void CButtonSlider::OnLeftClick()
{
	if(m_width < m_height)
	{
		if(InternalLCPos().y < m_width)
			if((*m_variable) > m_min)
				(*m_variable)--;
			else
				;
		else if(InternalLCPos().y > (m_height-m_width))
			if((*m_variable) < m_max)
				(*m_variable)++;
			else
				;
		else
			(*m_variable) = m_min+(int)((InternalLCPos().y-m_width)/(double)((m_height-2*m_width)/(m_max-m_min+1)));
	}
	else
	{
		if(InternalLCPos().x < m_height)
			if((*m_variable) > m_min)
				(*m_variable)--;
			else
				;
		else if(InternalLCPos().x > (m_width-m_height))
			if((*m_variable) < m_max)
				(*m_variable)++;
			else
				;
		else
			(*m_variable) = m_min+(int)((InternalLCPos().x-m_height)/(double)((m_width-2*m_height)/(m_max-m_min+1)));
	}
}
void CButtonSlider::ToolTip()
{
	CToolTip l_tt;
	l_tt.AddLine(g_Global.itoa(*m_variable)+","+g_Global.itoa(m_min)+","+g_Global.itoa(m_max));
	l_tt.Draw();
}
CButtonSetTab::CButtonSetTab(int p_x,int p_y,int p_width,int p_height,double p_depth,
							   DataTabs p_newTab,IDirect3DTexture9* p_graphic,std::string p_label,std::string p_toolTip) :
	m_newTab(p_newTab),
	m_graphic(p_graphic),
	m_label(p_label),
	m_toolTip(p_toolTip),
	m_depth(p_depth)
{
	m_x = p_x;
	m_y = p_y;
	m_width = p_width;
	m_height = p_height;
	Draw();
}
void CButtonSetTab::Draw()
{
	g_Gfx.MakeQuad(m_x,m_y,m_width,m_height,m_depth,
					0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,false,m_graphic,1,1);
	CTextGroup l_tg(1,m_x,m_y,0xffffffff,g_Gfx.GetFont(6));
	l_tg.AddLine(m_label);
	g_Gfx.m_textGroups.push_back(l_tg);
}
void CButtonSetTab::OnLeftClick()
{
	CGameStateData::SetTab(m_newTab);
	g_Global.LogInfo("BSTOLC");
}
void CButtonSetTab::ToolTip()
{
	CToolTip l_tt;
	l_tt.AddLine(m_toolTip);
	l_tt.Draw();
}
