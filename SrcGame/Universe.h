#pragma once
#include <vector>

class CStar;
class CEmpire;
class CPlanet;

class CUniverse
{
private:
	std::vector<CStar *> m_Stars;
	std::vector<CEmpire *> m_Empires;
	UINT m_numStars;
	UINT m_numEmpires;
	UINT m_mapSize;
public:
	CUniverse();
	~CUniverse();
	void Settings(UINT p_numStars,UINT p_numEmpires,UINT p_mapSize);
	UINT GetMapSize();
	UINT GetMapSizeInPixels();
	bool Create();
/*	POINT GetStarPos(CStar *p_star);
	DWORD GetStarColor(UINT);
	const std::string& GetStarName(UINT) const;
	int GetStarOwner(UINT);
	UINT GetStarType(UINT);
	UINT GetStarSize(UINT);
	UINT GetStarSpecial(UINT);
	UINT GetStarPlanetCount(UINT);
	double GetSystemPop(UINT);
	double GetSystemInd(UINT);
	double GetSystemSci(UINT);
	UINT GetNumEmpires();
	double GetEmpirePopulation(UINT);
	double GetEmpireIndEff(UINT);*/
	CPlanet* GetHomePlanet(UINT);
	CStar* GetHomeStar(UINT);
	DWORD GetEmpireColor(UINT p_empNum);
/*	int GetEmpireShipsByType(UINT,UINT);
	UINT GetEmpireFleetCount(UINT);
	UINT GetFleetSize(UINT,UINT);
	CStar* GetFleetLocation(CFleet *p_fleet);
	CStar* GetFleetDest(UINT,UINT);
	void SendFleet(UINT p_empire,CFleet *p_fleet,CStar *p_dest);*/
	CEmpire* GenerateEmpires();
	void ProcessTurn();
	void Print();
	void DrawStars(bool p_real);
	void DrawFleets(bool p_real);
	std::vector<CStar *> GetStarList();
//	void DrawToolTip(CGameObject *p_object);
};
