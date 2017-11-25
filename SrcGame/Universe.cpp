#include "dxstdafx.h"
#include "../SrcGame/Global.h"
#include "../SrcGame/Universe.h"
#include "../SrcGame/Star.h"
#include "../SrcGame/Empire.h"

CUniverse::CUniverse()
{
	g_Global.LogInfo("Universe object created");
}
CUniverse::~CUniverse()
{
	g_Global.LogInfo("Universe object destroyed");
	for(std::vector<CEmpire *>::iterator it = m_Empires.begin();it != m_Empires.end();++it)
	{
		delete (*it);
	}
	for(std::vector<CStar *>::iterator it = m_Stars.begin();it != m_Stars.end();++it)
	{
		delete (*it);
	}
}
void CUniverse::Settings(UINT p_numStars,UINT p_numEmpires,UINT p_mapSize)
{
	m_numStars = p_numStars;
	m_numEmpires = p_numEmpires;
	m_mapSize = p_mapSize;
}
UINT CUniverse::GetMapSize()
{
	return m_mapSize;
}
UINT CUniverse::GetMapSizeInPixels()
{
	return m_mapSize*g_Global.m_StarGfxSize;
}
bool CUniverse::Create()
{
	g_Global.LogInfo("Creating universe with ",(int)m_numStars," stars on a ",(int)CGlobal::StarGridSize," grid");
	m_Stars.clear();
	UINT l_randNum;
	UINT error = 0;
	std::vector<UINT> grid(m_mapSize*m_mapSize+2*m_mapSize+2,0); // HACK extra space for separation
	for (UINT i=0;i<m_mapSize;++i)
	{
		for (UINT j=0;j<m_mapSize;++j)
		{
			if(i == 0 || i == m_mapSize-1 || j == 0 || j == m_mapSize-1 ||
				i == 2 || i == m_mapSize-2 || j == 1 || j == m_mapSize-2)
				grid[j+m_mapSize*i] = 1;
		}
	}
	for (UINT i=0;i<m_numStars;++i)
	{
		error = 0;
		do
		{
			rand_s(&l_randNum);
			l_randNum %= m_mapSize*m_mapSize;
			++error;
		}
		while(grid[l_randNum/m_mapSize+m_mapSize*(l_randNum%m_mapSize)] == 1 && error < 100);
		if(error == 100)
		{
			g_Global.ShowBox(L"All stars did not fit in grid on first try",i,error);
			return false;
		}
		// 1x1 placed star
		grid[l_randNum/m_mapSize+m_mapSize*(l_randNum%m_mapSize)] = 1;
		if(l_randNum%m_mapSize != 0 && l_randNum/m_mapSize != 0)
		{
			// 3x3 surrounding area
			grid[l_randNum/m_mapSize+m_mapSize*(l_randNum%m_mapSize+1)] = 1;
			grid[l_randNum/m_mapSize+m_mapSize*(l_randNum%m_mapSize-1)] = 1;
			grid[l_randNum/m_mapSize+1+m_mapSize*(l_randNum%m_mapSize)] = 1;
			grid[l_randNum/m_mapSize-1+m_mapSize*(l_randNum%m_mapSize)] = 1;
			grid[l_randNum/m_mapSize+1+m_mapSize*(l_randNum%m_mapSize+1)] = 1;
			grid[l_randNum/m_mapSize-1+m_mapSize*(l_randNum%m_mapSize-1)] = 1;
			grid[l_randNum/m_mapSize+1+m_mapSize*(l_randNum%m_mapSize-1)] = 1;
			grid[l_randNum/m_mapSize-1+m_mapSize*(l_randNum%m_mapSize+1)] = 1;
			if(l_randNum%m_mapSize != 1 && l_randNum/m_mapSize != 1)
			{
				// 5x5 surrounding area
				grid[l_randNum/m_mapSize+  m_mapSize*(l_randNum%m_mapSize+2)] = 1;
				grid[l_randNum/m_mapSize+  m_mapSize*(l_randNum%m_mapSize-2)] = 1;
				grid[l_randNum/m_mapSize+2+m_mapSize*(l_randNum%m_mapSize)] = 1;
				grid[l_randNum/m_mapSize-2+m_mapSize*(l_randNum%m_mapSize)] = 1;
				grid[l_randNum/m_mapSize+2+m_mapSize*(l_randNum%m_mapSize+2)] = 1;
				grid[l_randNum/m_mapSize-2+m_mapSize*(l_randNum%m_mapSize-2)] = 1;
				grid[l_randNum/m_mapSize+2+m_mapSize*(l_randNum%m_mapSize-2)] = 1;
				grid[l_randNum/m_mapSize-2+m_mapSize*(l_randNum%m_mapSize+2)] = 1;
				grid[l_randNum/m_mapSize+1+m_mapSize*(l_randNum%m_mapSize+2)] = 1;
				grid[l_randNum/m_mapSize+1+m_mapSize*(l_randNum%m_mapSize-2)] = 1;
				grid[l_randNum/m_mapSize+2+m_mapSize*(l_randNum%m_mapSize+1)] = 1;
				grid[l_randNum/m_mapSize+2+m_mapSize*(l_randNum%m_mapSize-1)] = 1;
				grid[l_randNum/m_mapSize-1+m_mapSize*(l_randNum%m_mapSize+2)] = 1;
				grid[l_randNum/m_mapSize-1+m_mapSize*(l_randNum%m_mapSize-2)] = 1;
				grid[l_randNum/m_mapSize-2+m_mapSize*(l_randNum%m_mapSize+1)] = 1;
				grid[l_randNum/m_mapSize-2+m_mapSize*(l_randNum%m_mapSize-1)] = 1;
			}
		}
		POINT coord = {(int)(l_randNum%m_mapSize),(int)(l_randNum/m_mapSize)};
		m_Stars.push_back(new CStar(i,coord));
	}
	for(UINT i = 0;i< m_numEmpires;++i)
		m_Stars[i]->CreateHomePlanet();
	g_Global.LogInfo("Universe created with ",(int)m_Stars.size()," stars");
	return true;
}
/*POINT CUniverse::GetStarPos(CStar *p_star)
{
	POINT coord = {0,0};
//	coord = m_Stars[(UINT)g_MouseHandler.GetButtonIndex((int)p_id)]->GetPos();
	coord = p_star->GetPos();
	return coord;
}
DWORD CUniverse::GetStarColor(UINT index)
{
	return m_Stars[index]->GetColor();
}
const std::string& CUniverse::GetStarName(UINT index) const
{
	return m_Stars[index]->GetStarName();
}
int CUniverse::GetStarOwner(UINT index)
{
	return m_Stars[index]->GetOwner();
}
UINT CUniverse::GetStarType(UINT index)
{
	return m_Stars[index]->GetType();
}
UINT CUniverse::GetStarSize(UINT index)
{
	return m_Stars[index]->GetSize();
}
UINT CUniverse::GetStarSpecial(UINT index)
{
	return m_Stars[index]->GetSpecial();
}
UINT CUniverse::GetStarPlanetCount(UINT index)
{
	return m_Stars[index]->GetPlanetCount();
}
double CUniverse::GetSystemPop(UINT index)
{
	return m_Stars[index]->GetSystemPop();
}
double CUniverse::GetSystemInd(UINT index)
{
	return m_Stars[index]->GetSystemInd();
}
double CUniverse::GetSystemSci(UINT index)
{
	return m_Stars[index]->GetSystemSci();
}*/
/*UINT CUniverse::GetNumEmpires()
{
	return m_numEmpires;
}*//*
double CUniverse::GetEmpirePopulation(UINT index)
{
	double pop = 0;
	for(UINT i=0;i<m_Stars.size();++i)
	{
		if(m_Stars[i]->GetOwner() == (int)index)
			pop += m_Stars[i]->GetSystemPop();
	}
	return pop;
}*/
/*double CUniverse::GetEmpireIndEff(CEmpire *p_empire)
{
	return p_empire->GetIndEff();
}*/
CPlanet* CUniverse::GetHomePlanet(UINT index)
{
	if(index < m_Stars.size())
		return m_Stars[index]->GetPlanet(0);
	else
		return NULL;
}
CStar* CUniverse::GetHomeStar(UINT index)
{
	if(index < m_Stars.size())
		return m_Stars[index];
	else
		return NULL;
}
DWORD CUniverse::GetEmpireColor(UINT p_empNum)
{
	// XXX
	return D3DXCOLOR((float)g_Global.GetRandInRange(0.1f,1.0f),(float)g_Global.GetRandInRange(0.1f,1.0f),(float)g_Global.GetRandInRange(0.1f,1.0f),1.0f);
/*	switch(p_empNum)
	{
	case 0:
		return D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		break;
	case 1:
		return D3DXCOLOR(1.0f,1.0f,0.0f,1.0f);
		break;
	case 2:
		return D3DXCOLOR(1.0f,0.0f,1.0f,1.0f);
		break;
	case 3:
		return D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);
		break;
	case 4:
		return D3DXCOLOR(0.0f,1.0f,1.0f,1.0f);
		break;
	case 5:
		return D3DXCOLOR(0.0f,1.0f,0.0f,1.0f);
		break;
	case 6:
		return D3DXCOLOR(0.0f,0.0f,1.0f,1.0f);
		break;
	case 7:
		return D3DXCOLOR(1.0f,0.5f,0.0f,1.0f);
		break;
	default:
		return D3DXCOLOR(0.5f,0.5f,0.5f,1.0f);
		break;
	}*/
}
CEmpire* CUniverse::GenerateEmpires()
{
	m_Empires.clear();
	for(UINT i=0;i<m_numEmpires;++i)
	{
		g_Global.LogInfo("Creating empire ",(int)i,"");
		if(GetHomePlanet(i) == NULL)
			return NULL;
		else
			m_Empires.push_back(new CEmpire(i == 0 ? false : true,GetHomeStar(i),GetHomePlanet(i),GetEmpireColor(i))); // XXX
	}
	if((int)m_Empires.size() == m_numEmpires)
		return m_Empires[0]; // XXX
	else
		return NULL;
}
void CUniverse::ProcessTurn()
{
	for(UINT i=0;i<g_Global.m_NumEmpires;++i)
	{
		m_Empires[i]->MoveFleets();
//		m_Empires[i]->MergeFleets();
		m_Empires[i]->BuildShips();
		m_Empires[i]->BuildBuildings();
		m_Empires[i]->Research();
		m_Empires[i]->DoAI();
	}
	for(UINT i=0;i<g_Global.m_NumStars;++i)
	{
		m_Stars[i]->Growth();
	}
}
/*
int CUniverse::GetEmpireShipsByType(UINT empire,UINT type)
{
	if(m_Empires.size() > empire)
		return m_Empires[empire]->GetOwnedShipsByType(type);
	else
		return (int)m_Empires.size();
}*/
/*
int CUniverse::FindFleetOwner(int id)
{
	if(id == -1)
		return -1;
	for (UINT i = 0;i < g_Global.m_NumEmpires;++i)
		for(UINT j=0;j<m_Empires[i]->GetFleetCount();++j)
			if(m_Empires[i]->GetFleetIndex(j) == (UINT)id)
				return i;
	return -1;
}
*/
/*
int CUniverse::FindFleet(int id)
{
	if(id == -1)
		return -1;
	for (UINT i = 0;i < g_Global.m_NumEmpires;++i)
		for(UINT j=0;j<m_Empires[i]->GetFleetCount();++j)
			if(m_Empires[i]->GetFleetIndex(j) == (UINT)id)
				return j;
	return -1;
}
*/
/*
UINT CUniverse::GetEmpireFleetCount(UINT p_empire)
{
	return (UINT)m_Empires[p_empire]->GetFleetCount();
}

UINT CUniverse::GetFleetSize(UINT p_fleet,UINT p_owner)
{
	return m_Empires[p_owner]->GetFleetSize(p_fleet);
}
CStar* CUniverse::GetFleetLocation(CFleet *p_fleet)
{
//	return m_Empires[(UINT)g_MouseHandler.GetButtonOwner((int)p_fleet)]->GetFleetLocation((UINT)g_MouseHandler.GetButtonIndex((int)p_fleet));
//	return m_Empires[(UINT)g_MouseHandler.GetButtonOwner(p_button->m_object->ObjectOwner())]->GetFleetLocation((UINT)g_MouseHandler.GetButtonIndex((int)p_fleet));
	return p_fleet->GetLocation();
}
CStar* CUniverse::GetFleetDest(UINT p_fleet,UINT p_owner)
{
	return m_Empires[p_owner]->GetFleetDestination(p_fleet);
}
void CUniverse::SendFleet(UINT p_empire,CFleet *p_fleet,CStar *p_dest)
{
//	if(dest != -1)
//		m_Empires[p_empire]->SendFleet(p_fleet,p_dest);
	p_fleet->SetDestination(p_dest);
}
void CUniverse::Print()
{
	g_Global.LogInfo("universe has ",(int)m_Stars.size()," stars");
	for (size_t i = 0;i < m_Stars.size();++i)
		m_Stars[i]->Print();
}*/
void CUniverse::DrawStars(bool p_real)
{
	// stars
	if(p_real)
		for(std::vector<CStar *>::iterator it = m_Stars.begin();it != m_Stars.end();++it)
			(*it)->Draw();
	else
		for(std::vector<CStar *>::iterator it = m_Stars.begin();it != m_Stars.end();++it)
			(*it)->DrawMinimap();
}
void CUniverse::DrawFleets(bool p_real)
{
	for(std::vector<CEmpire *>::iterator it = m_Empires.begin();it != m_Empires.end();++it)
		(*it)->DrawFleets(p_real);
}
std::vector<CStar *> CUniverse::GetStarList()
{
	return m_Stars;
}
/*void CUniverse::DrawToolTip(CButtonBase *p_id)
{
	p_id->ButtonToolTip();
	GameObjectTypes l_GOType = g_MouseHandler.GetButtonType((int)p_ID);
	switch (l_GOType)
	{
	case GO_STAR:
		m_Stars[p_ID]->DrawToolTipData();
		break;
	case GO_FLEET:
		m_Empires[(UINT)g_MouseHandler.GetButtonOwner((int)p_ID)]->DrawFleetToolTip((UINT)g_MouseHandler.GetButtonIndex((int)p_ID));
		break;
	case GO_BUTTON:
		g_MouseHandler.DrawButtonToolTip(g_MouseHandler.GetButtonIndex(p_ID));
		break;
	case GO_SHIP:
		// TODO
		break;
	case GO_MINIMAP :
		// TODO
		break;
	case GO_NULL:
		// TODO
		break;
	default:
		g_Global.LogInfo("Drawing undefined tooltip!");
		break;
	}
}*/
