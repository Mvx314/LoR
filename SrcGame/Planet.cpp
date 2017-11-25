#include "dxstdafx.h"
#include "../SrcGame/Global.h"
#include "../SrcGame/Planet.h"
#include "../SrcGame/Star.h"
#include "../SrcGame/Empire.h"

CPlanet::CPlanet(UINT i,bool ismoon,CStar *p_loc,bool homeworld,CEmpire *p_owner) :
	m_Index (i),
	m_isMoon (ismoon),
	m_Location (p_loc),
	m_isHome (homeworld),
	m_Owner (p_owner)
{
/*	if(!ismoon)
		g_Global.LogInfo(  creating plnt:" << i << endl;
	else
		g_Global.LogInfo(   creating moon: " << i << endl;*/
	m_Habitability = g_Global.GetRandInRange(0U,4);
	m_Population = 0;
	m_PopMax = m_Habitability*7;
	m_Fertility = g_Global.GetRandInRange(0U,4);
	m_Nutrients = 0;
	m_NutMax = m_Fertility*7;
	m_Resources = g_Global.GetRandInRange(0U,4);
	m_IndEff = 1.0f;
	m_IndMax = m_Population*m_Resources*m_IndEff;
	m_Industry = 0;
	m_Science = 0;
	if(m_isHome)
	{
		m_Habitability = 3.0f;
		m_Population = 10.0f;
		m_PopMax = m_Habitability*7;
		m_Fertility = 3.0f;
		m_Nutrients = 10.0f;
		m_NutMax = m_Fertility*7;
		m_Resources = 2.0f;
		m_Industry = 10.0f;
		m_IndMax = m_Population*m_Resources*m_IndEff;
		m_Science = 10.0f;
	}
	if(!ismoon)
	{
		for (UINT j=0;j<g_Global.GetRandInRange(0U,4);++j)
		{
//			g_Global.LogInfo(   Creating " << j << "/" << num%5 << " moon for planet " << Index << endl;
			m_Moons.push_back(new CPlanet(j,true,m_Location,false,p_owner));
		}
//		g_Global.LogInfo("  plnt created" << endl;
	}
//	else
//		g_Global.LogInfo("   moon created" << endl;
//	of.close();
}
CPlanet::~CPlanet()
{
//	if(!m_isMoon)
//		g_Global.LogInfo("  plnt ",m_Index," destroyed");
//	else
//		g_Global.LogInfo("   moon ",m_Index," destroyed");
	for(std::vector<CPlanet *>::iterator it = m_Moons.begin();it != m_Moons.end();++it)
	{
		delete (*it);
	}
}
void CPlanet::Draw()
{
}
void CPlanet::OnLeftClick()
{
}
CGameObject* CPlanet::Location()
{
	return m_Location;
}
POINT CPlanet::ScreenPos()
{
	POINT l_XXX;
	l_XXX.x = 0;
	l_XXX.y = 0;
	return l_XXX;
}
POINT CPlanet::ScreenSize()
{
	POINT l_XXX;
	l_XXX.x = 10;
	l_XXX.y = 10;
	return l_XXX;
}
double CPlanet::GetPopulation()
{
	return m_Population;
}
double CPlanet::GetPopMax()
{
	return m_PopMax;
}
double CPlanet::GetIndustry()
{
	return m_Industry;
}
double CPlanet::GetScience()
{
	return m_Science;
}
CEmpire* CPlanet::GetOwner()
{
	return m_Owner;
}
void CPlanet::PlGrowth()
{
	if(m_Owner != NULL)
	{
		m_IndEff = m_Owner->GetIndEff();
		m_PopMax = m_Habitability*7;
		m_Population += ((m_PopMax-m_Population)*(m_Population/m_PopMax)*
			((m_Nutrients > m_Population) ? 1.0f : m_Nutrients/m_Population))/10;
		m_NutMax = m_Fertility*7;
		m_Nutrients += ((m_NutMax-m_Nutrients)*(m_Nutrients/m_NutMax))/10;
		m_IndMax = m_Population*m_Resources*m_IndEff;
		m_Industry += ((m_IndMax-m_Industry)*(m_Industry/m_IndMax))/10;
		m_Science = (m_Population+m_Industry)/2;
	}
}
void CPlanet::AddMigrants(double p_num)
{
	m_Population += p_num;
}
void CPlanet::SetPopToMax()
{
	m_Population = m_PopMax;
}
void CPlanet::SetAsHome(CEmpire *p_empire)
{
	m_isHome = true;
	m_Owner = p_empire;
	m_Habitability = 3.0f;
	m_Population = 10.0f;
	m_PopMax = m_Habitability*7;
	m_Fertility = 3.0f;
	m_Nutrients = 10.0f;
	m_NutMax = m_Fertility*7;
	m_Resources = 2.0f;
	m_Industry = 10.0f;
	m_IndMax = m_Population*m_Resources*m_IndEff;
	m_Science = (m_Population+m_Industry)/2;
}
void CPlanet::Print()
{
	if(!m_isMoon)
		g_Global.LogInfo("planet ",(int)m_Index," has ",(int)m_Moons.size()," moons");
	else
		g_Global.LogInfo("moon ",(int)m_Index,"");
//    textprintf_ex(screen,font,0,250,makecol(128,128,0),-1,"%d",index);
    for (size_t i = 0;i < m_Moons.size();++i)
        m_Moons[i]->Print();
//    while (!(mouse_b & 1));
}
