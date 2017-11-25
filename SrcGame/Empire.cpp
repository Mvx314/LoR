#include "dxstdafx.h"
#include "../SrcGame/Global.h"
#include "../SrcGame/Empire.h"

CEmpire::CEmpire(bool p_isAI,CStar *p_homeStar,CPlanet *p_homePlanet,DWORD p_color) :
	m_isAI (p_isAI),
	m_homeStar (p_homeStar),
	m_homePlanet (p_homePlanet),
	m_color (p_color)
{
	//TODO
	m_homeStar->AddPlayerPresence(this);
	m_homePlanet->SetAsHome(this);
	m_OwnedPlanets.push_back(m_homePlanet);
	m_IndEff = 1.0f;
	m_Science = 1.0f;
	m_LeftoverIndustry = 0.0f;
//	g_Global.LogInfo("Empire ",m_empireNum," being created");
	m_ShipClasses.push_back(new CShipClass(std::string("Scout"),1,1,1,1,1));
	m_ShipClasses.push_back(new CShipClass(std::string("Frigate"),2,2,2,2,2));
	m_ShipClasses.push_back(new CShipClass(std::string("Destroyer"),3,3,3,3,3));
	for(std::list<CShipClass *>::iterator it = m_ShipClasses.begin();it != m_ShipClasses.end();++it)
	{
		if((*it)->GetSCName() == "Scout")
		{
			CShip *l_newShip = new CShip(0,*it,m_homeStar,this);
			m_OwnedShips.push_back(l_newShip);
			AddToFleet(GetPresentFleet(m_homeStar),l_newShip);
			m_OwnedShipsByType[*it] = 1;
		}
		if((*it)->GetSCName() == "Frigate")
		{
			CShip *l_newShip = new CShip(0,*it,m_homeStar,this);
			m_OwnedShips.push_back(l_newShip);
			AddToFleet(GetPresentFleet(m_homeStar),l_newShip);
			m_OwnedShipsByType[*it] = 1;
		}
	}
}
CEmpire::~CEmpire()
{
//	g_Global.LogInfo("Empire ",m_empireNum," being destroyed");
	for(std::list<CShip *>::iterator it = m_OwnedShips.begin();it != m_OwnedShips.end();++it)
	{
		delete (*it);
	}
	for(std::list<CShipClass *>::iterator it = m_ShipClasses.begin();it != m_ShipClasses.end();++it)
	{
		delete (*it);
	}
	for(std::list<CFleet *>::iterator it = m_Fleets.begin();it != m_Fleets.end();++it)
	{
		delete (*it);
	}
}
void CEmpire::BuildShips()
{
	double l_industry = GetIndustry();
	while(l_industry > 0)
	{
		for(std::list<CShipClass *>::reverse_iterator rit = m_ShipClasses.rbegin();rit != m_ShipClasses.rend();++rit)
			while(l_industry > (*rit)->GetCost()) // TODO
			{
				CShip *l_newShip = new CShip(0,*rit,m_homeStar,this);
				m_OwnedShips.push_back(l_newShip);
				m_OwnedShipsByType[*rit] = m_OwnedShipsByType[*rit]+1;
				AddToFleet(GetPresentFleet(m_homeStar),l_newShip);
				l_industry -= (*rit)->GetCost();
			}
		m_LeftoverIndustry = l_industry;
		l_industry = 0;
	}
}
void CEmpire::BuildBuildings()
{
}
void CEmpire::Research()
{
	m_Science = GetScience();
}
void CEmpire::DoAI()
{
}
UINT CEmpire::GetOwnedShipsByType(CShipClass *p_class)
{
	return m_OwnedShipsByType[p_class];
}
double CEmpire::GetIndustry()
{
	double l_industry = 0;
	for(std::list<CPlanet *>::iterator it = m_OwnedPlanets.begin();it != m_OwnedPlanets.end();++it)
		l_industry += (*it)->GetIndustry();
	l_industry += m_LeftoverIndustry;
	return l_industry;
}
double CEmpire::GetScience()
{
	double l_science = 0;
	for(std::list<CPlanet *>::iterator it = m_OwnedPlanets.begin();it != m_OwnedPlanets.end();++it)
		l_science += (*it)->GetIndustry();
	return l_science;
}
CFleet* CEmpire::GetPresentFleet(CStar *p_loc)
{
	for(std::list<CFleet *>::iterator it = m_Fleets.begin();it != m_Fleets.end();++it)
		if((*it)->GetLocation() == p_loc)
			return (*it);
	CreateFleet(p_loc);
	return *m_Fleets.begin();
}
CFleet* CEmpire::CreateFleet(CStar *p_loc)
{
	CFleet *l_fleet = new CFleet(p_loc,this);
	m_Fleets.push_back(l_fleet);
	return l_fleet;
}
void CEmpire::RemoveFleet(CFleet *p_fleet)
{
	m_Fleets.remove(p_fleet);
}
void CEmpire::AddToFleet(CFleet *p_fleet,CShip *p_ship)
{
	p_fleet->AddShip(p_ship);
//	if(fleetnum < m_Fleets.size())
//		m_Fleets[fleetnum]->AddShip(shipnum);
}
void CEmpire::RemoveFromFleet(CFleet *p_fleet,CShip *p_ship)
{
	p_fleet->RemoveShip(p_ship);
}
void CEmpire::TransferShip(CFleet *p_src,CFleet *p_dest,CShip *p_ship)
{
	CFleet *l_dest = p_dest;
	if(l_dest == NULL)
		l_dest = CreateFleet(p_src->GetLocation());
	RemoveFromFleet(p_src,p_ship);
	AddToFleet(l_dest,p_ship);
}
UINT CEmpire::GetFleetCount()
{
	return (UINT)m_Fleets.size();
}
UINT CEmpire::GetFleetSize(CFleet *p_fleet)
{
	return p_fleet->GetShipCount();
}
CStar* CEmpire::GetFleetLocation(CFleet *p_fleet)
{
	return p_fleet->GetLocation();
}
CStar* CEmpire::GetFleetDestination(CFleet *p_fleet)
{
	return p_fleet->GetDestination();
}
void CEmpire::SendFleet(CFleet *p_fleet,CStar *p_dest)
{
	p_fleet->SetDestination(p_dest);
}
void CEmpire::MoveFleets()
{
	for(std::list<CFleet *>::iterator it = m_Fleets.begin();it != m_Fleets.end();++it)
	{
		(*it)->SetLocation((*it)->GetDestination());
	}
}
void CEmpire::MergeFleets(CFleet *p_first,CFleet *p_second)
{
	p_first->Merge(p_second);
}
void CEmpire::DrawFleets(bool p_real)
{
	for(std::list<CFleet *>::iterator it = m_Fleets.begin();it != m_Fleets.end();++it)
		(*it)->DrawPrepare(p_real);
}
CPlanet* CEmpire::GetHomePlanet()
{
	return m_homePlanet;
}
CStar* CEmpire::GetHomeStar()
{
	return m_homeStar;
}