#pragma once
#include <list>
#include "../SrcGame/Star.h"
#include "../SrcInterface/ToolTip.h"

class CGameObject;
class CStar;
class CEmpire;
class CShip;

class CFleet : public CGameObject
{
private:
	CStar *m_home;
	CStar *m_location;
	CStar *m_destination;
	CEmpire *m_owner;
	std::list<CShip *> m_ships;
	bool m_moveline;
public:
	CFleet(CStar *p_homeStar,CEmpire *p_owner);
	~CFleet();
	void Draw();
	void OnMouseOver();
	void OnLeftClick();
	void OnRightClick();
	void ToolTip();
	CGameObject* Location();
	POINT ScreenPos();
	POINT ScreenSize();
	CEmpire* FleetOwner();
	UINT GetShipCount(){return (UINT)m_ships.size();};
	CStar *GetHome(){return m_home;};
	void SetLocation(CStar *);
	CStar *GetLocation(){return m_location;};
	void SetDestination(CStar *);
	CStar *GetDestination(){return m_destination;};
	void AddShip(CShip *p_ship);
	void RemoveShip(CShip *p_ship);
	void Merge(CFleet *);
	void DrawPrepare(bool p_real);
	bool IsAFleet(){return true;};
};
