#include "dxstdafx.h"
#include "../SrcGame/Global.h"
#include "../SrcGame/Fleet.h"

CFleet::CFleet(CStar *p_homeStar,CEmpire *p_owner) :
	m_home (p_homeStar),
	m_location (p_homeStar),
	m_destination (p_homeStar),
	m_owner (p_owner),
	m_moveline (false)
{
}
CFleet::~CFleet()
{
}
void CFleet::Draw()
{
}
void CFleet::OnMouseOver()
{
	POINT l_pos = ScreenPos();
	POINT l_size = ScreenSize();
	g_Gfx.MakeSquare(l_pos.x,l_pos.y,l_size.x,l_size.y,
				0.4f,0xFFFFFF00,0xFFFF00FF,0xFFFFFF00,0xFFFF00FF);
}
void CFleet::OnLeftClick()
{
	g_Global.m_CurrSelection = this;
	g_Global.m_CurrSelectionLocation = m_location;
	m_moveline = true;
}
void CFleet::OnRightClick()
{
	m_moveline = false;
}
void CFleet::ToolTip()
{
	CToolTip l_tt;
	l_tt.AddLine("Ships: "+g_Global.itoa((int)GetShipCount()));
	l_tt.AddLine("Location: "+m_location->GetStarName());
	l_tt.AddLine("Destination: "+m_destination->GetStarName());
	l_tt.Draw();
}
CGameObject* CFleet::Location()
{
	return m_location;
}
POINT CFleet::ScreenPos()
{
	POINT l_pos = m_location->ScreenPos();
	l_pos.x += (m_owner == g_Global.m_CurrPlayer
			? (int)(m_location->ScreenSize().x) 
			: -(int)(g_Global.m_FleetGfxSize)); // XXX
	l_pos.y -= g_Global.m_FleetGfxSize/2; // XXX flattening
	return l_pos;
}
POINT CFleet::ScreenSize()
{
	POINT l_size = {g_Global.m_FleetGfxSize,g_Global.m_FleetGfxSize/2}; // XXX flattening
	return l_size;
}
CEmpire* CFleet::FleetOwner()
{
	return m_owner;
}
void CFleet::SetLocation(CStar *p_loc)
{
	m_location = p_loc;
}
void CFleet::SetDestination(CStar *p_dest)
{
	m_moveline = false;
	m_destination = p_dest;
}
void CFleet::AddShip(CShip *p_ship)
{
	m_ships.push_back(p_ship);
}
void CFleet::RemoveShip(CShip *p_ship)
{
	m_ships.remove(p_ship);
}
void CFleet::Merge(CFleet *p_other)
{
	m_ships.merge(p_other->m_ships);
//	for(std::list<UINT>::iterator it = p_other->m_ships.begin();it != p_other->m_ships.end();++it)
//		this->AddShip(p_other->RemoveShip(*it));
}
void CFleet::DrawPrepare(bool p_real)
{
	if(p_real)
	{
		POINT l_pos = ScreenPos();
		POINT l_size = ScreenSize();
		g_Gfx.MakeQuad(l_pos.x,l_pos.y,l_size.x,l_size.y,0.5f,
//		(p_owner==g_Global.m_CurrPlayer ? 0xffff3fff : 0xffff0000),(p_owner==g_Global.m_CurrPlayer ? 0xffff3fff : 0xffff0000),
		0xffffffff,0xffffffff,0xffffffff,0xffffffff,
//		(p_owner==g_Global.m_CurrPlayer ? 0xffff3fff : 0xffff0000),(p_owner==g_Global.m_CurrPlayer ? 0xffff3fff : 0xffff0000),
		true,g_Textures.m_FleetTexture,1,0);

		if(m_owner == g_Global.m_CurrPlayer)
			g_MouseHandler.AddGameObject(this);
		// travelline
		if(m_location != m_destination)
		{
//		POINT l_pos1 = CStarmap::GetTransformedPos((int)(g_Global.m_Width*g_Global.m_Universe->GetStarPos(m_location).x/CGlobal::StarGridSize+g_Global.m_StarGfxSize/2+g_Global.m_FleetGfxSize/2),(int)(g_Global.m_Height*g_Global.m_Universe->GetStarPos(m_location).y/CGlobal::StarGridSize-g_Global.m_StarGfxSize/2+g_Global.m_FleetGfxSize/4));
//		POINT l_pos2 = CStarmap::GetTransformedPos((int)(g_Global.m_Width*g_Global.m_Universe->GetStarPos(m_destination).x/CGlobal::StarGridSize+g_Global.m_StarGfxSize/2),(int)(g_Global.m_Height*g_Global.m_Universe->GetStarPos(m_destination).y/CGlobal::StarGridSize+g_Global.m_StarGfxSize/2));
			POINT l_pos1 = ScreenPos();
			POINT l_pos2 = m_destination->ScreenPos();
			g_Gfx.MakeLine(l_pos1,l_pos2,0.5f,0xFF00FF00,0xFF00FF00);
		}
		// moveline
		if(g_Global.m_CurrSelection == this && m_moveline)
		{
			POINT l_pos3 = ScreenPos();
			g_Gfx.MakeLine(l_pos3,g_MouseHandler.GetMousePos(),0.5f,0xFF00FF00,0xFF00FF00);
		}
	}
	else // Minimap?
	{
	}
}
