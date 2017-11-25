#include "dxstdafx.h"
#include "../SrcGame/ShipClass.h"

CShipClass::CShipClass(const std::string& scname,UINT weap,UINT def,UINT arm,UINT shi,UINT spe) :
	m_name(scname),
	m_existCounter (0),
	m_weapons (weap),
	m_defence (def),
	m_armour (arm),
	m_shield (shi),
	m_speed (spe)
{
	m_cost = m_speed; // XXX
//	g_Global.LogInfo("Shipclass ",m_index," created");
}
/*
CShipClass::CShipClass(CShipClass const &other)
{
	g_Global.LogInfo("Copy constructor of shipclass ");
	copy(other);
}
*/
CShipClass::~CShipClass()
{
//	g_Global.LogInfo("Shipclass ",m_index," destroyed");
}
/*
void CShipClass::copy(CShipClass const &other)
{
	m_index = other.m_index;
	m_name = std::string(other.m_name);
	m_existCounter = other.m_existCounter;
	m_weapons = other.m_weapons;
	m_defence = other.m_defence;
	m_armour = other.m_armour;
	m_shield = other.m_shield;
	m_speed = other.m_speed;
	g_Global.LogInfo("ShipClass copy const for: "+m_name);
}
*/
void CShipClass::ShipBuilt()
{
	++m_existCounter;
}
void CShipClass::ShipDestroyed()
{
	assert(m_existCounter > 0);
	m_existCounter--;
}
const std::string& CShipClass::GetSCName() const
{
	return m_name;
}
UINT CShipClass::GetCost()
{
	return m_cost;
}