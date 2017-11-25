#pragma once

#include <string>
//class CWeapons;

class CShipClass
{
private:
	UINT m_cost;
	std::string m_name;
	UINT m_existCounter;
//	std::vector<CWeapons *> weapons;
	UINT m_weapons;
	UINT m_defence;
	UINT m_armour;
	UINT m_shield;
	UINT m_speed;
//	void copy(CShipClass const &);
public:
	CShipClass(const std::string& scname,UINT weap,UINT def,UINT arm,UINT shi,UINT spe);
//	CShipClass(CShipClass const &);
	~CShipClass();
	void ShipBuilt();
	void ShipDestroyed();
	const std::string& GetSCName() const;
	UINT GetCost();
};
