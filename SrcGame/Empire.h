#pragma once
#include <list>
#include <map>
#include "../SrcGame/Star.h"
#include "../SrcGame/Planet.h"
#include "../SrcGame/ShipClass.h"
#include "../SrcGame/Ship.h"
#include "../SrcGame/Fleet.h"

class CStar;
class CPlanet;
class CShipClass;
class CShip;
class CFleet;

class CEmpire
{
private:
	CStar *m_homeStar;
	CPlanet *m_homePlanet;
	DWORD m_color;
	bool m_isAI;
	double m_IndEff;
	double m_Science;
	double m_LeftoverIndustry;
	std::list<CPlanet *> m_OwnedPlanets;
	std::map<CShipClass *,UINT> m_OwnedShipsByType;
	std::list<CShipClass *> m_ShipClasses;
	std::list<CShip *> m_OwnedShips;
	std::list<CFleet *> m_Fleets;
public:
	CEmpire(bool p_isAI,CStar *p_homeStar,CPlanet *p_homePlanet,DWORD p_color);
	~CEmpire();
	void BuildShips();
	void BuildBuildings();
	void Research();
	void DoAI();
	UINT GetOwnedShipsByType(CShipClass *p_class);
	double GetIndEff(){return m_IndEff;};
	double GetIndustry();
	double GetScience();
	CFleet* GetPresentFleet(CStar *p_loc);
	CFleet* CreateFleet(CStar *p_loc);
	void RemoveFleet(CFleet *p_fleet);
	void AddToFleet(CFleet *p_fleet,CShip *p_ship);
	void RemoveFromFleet(CFleet *p_fleet,CShip *p_ship);
	void TransferShip(CFleet *p_src,CFleet *p_dest,CShip *p_ship);
	UINT GetFleetCount();
//	UINT GetFleetIndex(UINT);
	UINT GetFleetSize(CFleet *p_fleet);
	CStar* GetFleetLocation(CFleet *p_fleet);
	CStar* GetFleetDestination(CFleet *p_fleet);
	void SendFleet(CFleet *p_fleet,CStar *p_dest);
//	void SetFleetSelected(UINT,bool);
//	void SetFleetIndex(UINT,UINT);
	void MoveFleets();
	void MergeFleets(CFleet *,CFleet *);
	void UnselectAll();
	void DrawFleets(bool p_real);
	CPlanet* GetHomePlanet();
	CStar* GetHomeStar();
	DWORD GetColor(){return m_color;};
};
