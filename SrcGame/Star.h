#pragma once
#include "../SrcGame/GameObject.h"
#include <string>
#include <vector>

class CGameObject;
class CPlanet;
class CEmpire;
//class CUniverse;

class CStar : public CGameObject
{
private:
	std::string m_Name;
	UINT m_Index;
	UINT m_Type;
	UINT m_Special;
//	POINT m_Pos;
	UINT m_Size;
	DWORD m_Color;
	std::vector<CPlanet *> m_Planets;
	std::vector<UINT> m_PlanetDistances;
	std::vector<CEmpire *> m_PlayersPresent; // players who have planets here
public:
	CStar(UINT p_index,POINT p_pos);
	~CStar();
	void Draw();
	void OnMouseOver();
	void OnLeftClick();
	void ToolTip();
	CGameObject* Location();
	POINT ScreenPos();
	POINT ScreenSize();
	void Print();
	std::vector<std::string> GetDataSet(bool p_header);
	void Growth();
	void AddPlayerPresence(CEmpire *p_empire);
	void RemovePlayerPresence(CEmpire *p_empire);
	UINT GetIndex();
	DWORD GetColor();
	DWORD GetOwnerColor();
	const std::string& GetStarName() const;
	CEmpire* GetOwner();
	UINT GetSize();
	UINT GetType();
	UINT GetSpecial();
	UINT GetPlanetCount();
	double GetSystemPop();
	double GetSystemInd();
	double GetSystemSci();
	void CreateHomePlanet();
	CPlanet* GetPlanet(UINT p_index);
	void DrawMinimap();
//	POINT GetPos();
	bool IsAStar(){return true;};
};
