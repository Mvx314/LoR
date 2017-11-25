#pragma once
#include "../SrcGame/GameObject.h"
#include <vector>

class CGameObject;
class CEmpire;
class CStar;

class CPlanet : public CGameObject
{
private:
	UINT m_Index;
	CEmpire *m_Owner;
	bool m_isMoon;
	std::vector<CPlanet *> m_Moons;
	CStar *m_Location;
	bool m_isHome;
	double m_Habitability; // 0-4
	double m_Population; // 0-PopMax
	double m_PopMax; // Hab*7
	double m_Fertility; // 0-4
	double m_Nutrients; // 0-NutMax
	double m_NutMax; // Fer*7
	double m_Resources; // 0-4
	double m_IndEff; // 0.5 - n
	double m_Industry; // 0-IndMax
	double m_IndMax; // Pop*Res*IndEff
	double m_Science;
	int m_BuildingShipType;
	double m_BuildingShipProgress;
	int m_BuildingType;
	double m_BuildingProgress;
public:
	CPlanet(UINT,bool,CStar *p_loc,bool,CEmpire *p_owner);
	~CPlanet();
	void Draw();
	void OnLeftClick();
	CGameObject* Location();
	POINT ScreenPos();
	POINT ScreenSize();
	double GetPopulation();
	double GetPopMax();
	double GetIndustry();
	double GetScience();
	CEmpire* GetOwner();
	void PlGrowth();
	void AddMigrants(double p_num);
	void SetPopToMax();
	void SetAsHome(CEmpire *p_empire);
	void Print();
};
