#include "dxstdafx.h"
#include "../SrcGame/Global.h"
#include "../SrcGame/Starmap.h"

POINT CStarmap::m_ViewportPosA = {0,0};
POINT CStarmap::m_ViewportPosB = {2,2};
POINT CStarmap::m_Focus = {1,1};

void CStarmap::ChangeZoom(const double p_zoom)
{
	int l_zoomAmount = 0;
	if(p_zoom > 0)
		l_zoomAmount = 20;
	if(p_zoom < 0)
		l_zoomAmount = -20;
	POINT l_posA = {GetViewportPosA().x+l_zoomAmount,GetViewportPosA().y+l_zoomAmount};
	POINT l_posB = {GetViewportPosB().x-l_zoomAmount,GetViewportPosB().y-l_zoomAmount};
	if(l_posA.x < 0)
		l_posA.x = 0;
	if(l_posA.y < 0)
		l_posA.y = 0;
	if(l_posB.x > (int)g_Global.m_Universe->GetMapSizeInPixels())
		l_posB.x = g_Global.m_Universe->GetMapSizeInPixels();
	if(l_posB.y > (int)g_Global.m_Universe->GetMapSizeInPixels())
		l_posB.y = g_Global.m_Universe->GetMapSizeInPixels();
	SetViewportPos(l_posA,l_posB);
}
double CStarmap::GetZoom()
{
	return g_Global.m_Universe->GetMapSizeInPixels()/(double)(m_ViewportPosB.x - m_ViewportPosA.x);
}
void CStarmap::SetFocus(UINT p_x,UINT p_y)
{
	POINT l_vpSize = {m_ViewportPosB.x - m_ViewportPosA.x,m_ViewportPosB.y - m_ViewportPosA.y};
//	if(p_x < (UINT)l_vpSize.x/2 || p_x > g_Global.m_Universe->GetMapSizeInPixels()-l_vpSize.x/2 ||
//	   p_y < (UINT)l_vpSize.y/2 || p_y > g_Global.m_Universe->GetMapSizeInPixels()-l_vpSize.y/2)
//	   return;
	m_Focus.x = p_x;
	m_Focus.y = p_y;
	POINT l_posA = {m_Focus.x-l_vpSize.x/2,m_Focus.y-l_vpSize.y/2};
	POINT l_posB = {m_Focus.x+l_vpSize.x/2,m_Focus.y+l_vpSize.y/2};
	SetViewportPos(l_posA,l_posB);
//	m_ViewportPosA.x = m_Focus.x-l_vpSize.x/2;
//	m_ViewportPosA.y = m_Focus.y-l_vpSize.y/2;
//	m_ViewportPosB.x = m_Focus.x+l_vpSize.x/2;
//	m_ViewportPosB.y = m_Focus.y+l_vpSize.y/2;
	/*
	m_Focus.x = p_x;
	m_Focus.y = p_y;
	if(m_Focus.x < 0)
		m_Focus.x = 0;
	if(m_Focus.y < 0)
		m_Focus.y = 0;
	assert(m_ZoomLevel != 0);
	if(m_Focus.x > g_Global.m_Width*(g_Global.m_MapSize/CGlobal::StarGridSize)-(g_Global.m_Width/m_ZoomLevel))
		m_Focus.x = (int)(g_Global.m_Width*(g_Global.m_MapSize/CGlobal::StarGridSize)-(g_Global.m_Width/m_ZoomLevel));
	if(m_Focus.y > g_Global.m_Height*(g_Global.m_MapSize/CGlobal::StarGridSize)-(g_Global.m_Height/m_ZoomLevel))
		m_Focus.y = (int)(g_Global.m_Height*(g_Global.m_MapSize/CGlobal::StarGridSize)-(g_Global.m_Height/m_ZoomLevel));
*/
}
void CStarmap::ChangeFocus(int p_x,int p_y)
{
	POINT l_newFocus;
	l_newFocus.x = m_Focus.x+p_x;
	l_newFocus.y = m_Focus.y+p_y;
	SetFocus(l_newFocus.x,l_newFocus.y);
}
POINT CStarmap::GetFocus()
{
	return m_Focus;
}
void CStarmap::DrawStarmap()
{
	// MAP
	g_Global.m_Universe->DrawStars(true);
	g_Global.m_Universe->DrawFleets(true);
}
void CStarmap::SetViewportPos(const POINT p_posA,const POINT p_posB)
{
	int l_mapSize = (int)(g_Global.m_Universe->GetMapSizeInPixels());
//	if(p_posA.x < 0 || p_posA.y < 0 || p_posB.x > l_mapSize || p_posB.y > l_mapSize)
//		return;
	POINT l_oldA = m_ViewportPosA;
	POINT l_oldB = m_ViewportPosB;
	m_ViewportPosA = p_posA;
	m_ViewportPosB = p_posB;
	if( m_ViewportPosA.x >= m_ViewportPosB.x || m_ViewportPosA.y >= m_ViewportPosB.y)
	{
		m_ViewportPosA = l_oldA;
		m_ViewportPosB = l_oldB;
	}
	if( m_ViewportPosA.x < 0)
	{
		m_ViewportPosA.x = 0;
		m_ViewportPosB.x = l_oldB.x - l_oldA.x;
	}
	if( m_ViewportPosA.y < 0)
	{
		m_ViewportPosA.y = 0;
		m_ViewportPosB.y = l_oldB.y - l_oldA.y;
	}
	if( m_ViewportPosA.x > (l_mapSize-(int)g_Global.m_StarGfxSize))
		m_ViewportPosA.x = l_mapSize-g_Global.m_StarGfxSize;
	if( m_ViewportPosA.y > (l_mapSize-(int)g_Global.m_StarGfxSize))
		m_ViewportPosA.y = l_mapSize-g_Global.m_StarGfxSize;
	if( m_ViewportPosB.x > l_mapSize)
	{
		m_ViewportPosB.x = l_mapSize;
		m_ViewportPosA.x = l_mapSize - (l_oldB.x - l_oldA.x);
	}
	if( m_ViewportPosB.y > l_mapSize)
	{
		m_ViewportPosB.y = l_mapSize;
		m_ViewportPosA.y = l_mapSize - (l_oldB.y - l_oldA.y);
	}
	if( m_ViewportPosA.x == m_ViewportPosB.x || m_ViewportPosA.y == m_ViewportPosB.y)
	{
		g_Global.LogInfo("Error: Viewport size 0 in SetViewportPos at xpos:",m_ViewportPosA.x,"");
		m_ViewportPosA.x = 0;
		m_ViewportPosA.y = 0;
		m_ViewportPosB.x = 1;
		m_ViewportPosB.y = 1;
	}
	m_Focus.x = m_ViewportPosA.x + (m_ViewportPosB.x - m_ViewportPosA.x)/2;
	m_Focus.y = m_ViewportPosA.y + (m_ViewportPosB.y - m_ViewportPosA.y)/2;
	g_Global.ShowData("lpax:",m_ViewportPosA.x,false);
	g_Global.ShowData("lpay:",m_ViewportPosA.y,false);
	g_Global.ShowData("lpbx:",m_ViewportPosB.x,false);
	g_Global.ShowData("lpby:",m_ViewportPosB.y,false);
	assert(m_ViewportPosA.x >= 0);
//	g_Global.ShowBox(L"vpa:",m_ViewportPosA.x,m_ViewportPosB.x);
}
POINT CStarmap::GetViewportPosA()
{
	return m_ViewportPosA;
}
POINT CStarmap::GetViewportPosB()
{
	return m_ViewportPosB;
}
UINT CStarmap::GetViewportWidth()
{
	return m_ViewportPosB.x - m_ViewportPosA.x;
}
UINT CStarmap::GetViewportHeight()
{
	return m_ViewportPosB.y - m_ViewportPosA.y;
}
CMinimap::CMinimap(int p_x,int p_y,int p_width,int p_height,double p_depth) :
	m_depth(p_depth)
{
	m_x = p_x;
	m_y = p_y;
	m_width = p_width;
	m_height = p_height;
	Draw();
}
void CMinimap::Draw()
{
	// MINIMAP
		// black background
	g_Gfx.MakeQuad(m_x,
					m_y,
					m_width,
					m_height,
					m_depth,0xFF000000,0xFF000000,0xFF000000,0xFF000000,false,NULL,0,0);
		// frame
	g_Gfx.MakeSquare(m_x,
					m_y,
					m_width,
					m_height,
					m_depth-0.05f,0xFFFF00FF,0xFFFF00FF,0xFFFF00FF,0xFF00FFFF);
		// focusframe
	double l_ratiox = g_Global.m_Universe->GetMapSizeInPixels()/(double)g_Global.m_Width;
	double l_ratioy = g_Global.m_Universe->GetMapSizeInPixels()/(double)g_Global.m_Height;
	g_Gfx.MakeSquare((double)(g_Global.m_Width-m_width+CStarmap::GetViewportPosA().x/(l_ratiox*g_Global.m_MinimapScale)-1),
					(double)(CStarmap::GetViewportPosA().y/(l_ratioy*g_Global.m_MinimapScale)),
					(double)(CStarmap::GetViewportWidth()/(double)(l_ratiox*g_Global.m_MinimapScale)-1),
					(double)(CStarmap::GetViewportHeight()/(double)(l_ratioy*g_Global.m_MinimapScale)+1),
					m_depth-0.1f,0xFF00FFFF,0xFF00FFFF,0xFF00FFFF,0xFFFF00FF);
	g_Global.m_Universe->DrawStars(false);
	g_Global.m_Universe->DrawFleets(false);
}
void CMinimap::OnLeftClick()
{
//	POINT l_pos = {(int)g_Global.Scale(g_MouseHandler.GetLCPos().x,(g_Global.m_Width-g_Global.m_Width/g_Global.m_MinimapScale),g_Global.m_Width,0,g_Global.m_Universe->GetMapSizeInPixels()),
//		(int)g_Global.Scale(g_MouseHandler.GetLCPos().y,0,(g_Global.m_Height/g_Global.m_MinimapScale),0,g_Global.m_Universe->GetMapSizeInPixels())};
	POINT l_pos = {(int)g_Global.Scale(InternalLCPos().x,0,m_width,0,g_Global.m_Universe->GetMapSizeInPixels()),
		(int)g_Global.Scale(InternalLCPos().y,0,m_height,0,g_Global.m_Universe->GetMapSizeInPixels())};
	CStarmap::SetFocus(l_pos.x,l_pos.y);
}
