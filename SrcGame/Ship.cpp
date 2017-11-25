#include "dxstdafx.h"
#include "../SrcGame/Ship.h"
#include "../SrcGame/ShipClass.h"
#include "../SrcGame/Star.h"

CShip::CShip(UINT p_id,CShipClass *p_shipClass,CStar *p_location,CEmpire *p_owner) :
	m_shipClass (p_shipClass),	
	m_index (p_id), 
	m_location (p_location),
	m_owner (p_owner)
{
	p_shipClass->ShipBuilt();
//	g_Global.LogInfo("Ship ",m_index," built");
}
/*
CShip::CShip(CShip const &other)
{
	g_Global.LogInfo("Copy constructor of ship ",other.m_index,"");
	m_shipClass = other.m_shipClass;
	m_index = other.m_index;
	m_location = other.m_location;
	m_loctype = other.m_loctype; // all ships created at systems
	m_owner = other.m_owner;
}
*/
CShip::~CShip()
{
//	g_Global.LogInfo("Ship ",m_index," destroyed");
}
void CShip::Draw()
{
}
void CShip::OnLeftClick()
{
}
CGameObject* CShip::Location()
{
	return m_location;
}
POINT CShip::ScreenPos()
{
	POINT l_XXX;
	l_XXX.x = 0;
	l_XXX.y = 0;
	return l_XXX;
}
POINT CShip::ScreenSize()
{
	POINT l_XXX;
	l_XXX.x = 0;
	l_XXX.y = 0;
	return l_XXX;
}
UINT CShip::GetIndex()
{
	return m_index;
}