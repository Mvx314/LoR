#include "dxstdafx.h"
#include "../SrcGame/Global.h"
#include "../SrcGame/Star.h"
#include "../SrcGame/Planet.h"
#include "../SrcGame/Empire.h"

class CGameObject;

CStar::CStar(UINT p_index,POINT p_pos) :
	m_Index (p_index)
{
	m_x = p_pos.x;
	m_y = p_pos.y;
	std::vector<std::string> Names;
	Names.push_back("Alpha");
	Names.push_back("Beta");
	Names.push_back("Gamma");
	Names.push_back("Delta");
	Names.push_back("Epsilon");
	Names.push_back("Zeta");
	Names.push_back("Eta");
	Names.push_back("Theta");
	Names.push_back("Muu");
	Names.push_back("Nuu");
	Names.push_back("Uusiquu");
//	g_Global.LogInfo(" Creating star: " << i << " at " << clock() << endl;
	std::string suffix(" ");
	for(size_t j = m_Index;j >= Names.size();j -= Names.size())
		suffix = suffix + "I";
//	g_Global.LogInfo(" suffix: " << suffix << " at " << clock() << endl;
	m_Name = std::string(Names[m_Index%Names.size()]+suffix);
	m_Type = ((g_Global.GetRandInRange(0U,7)+g_Global.GetRandInRange(0U,7))/2);
	// 3*0, 7*1, 11*2, 15*3, 13*4, 9*5, 5*6, 1*7
	switch(m_Type)
	{
	case 0:
		m_Color = 0xff3f3fff;
		break;
	case 1:
		m_Color = 0xffffff7f;
		break;
	case 2:
		m_Color = 0xffffff00;
		break;
	case 3:
		m_Color = 0xffff7f00;
		break;
	case 4:
		m_Color = 0xffff3f00;
		break;
	case 5:
		m_Color = 0xffffffff;
		break;
	case 6:
		m_Color = 0xffaf0000;
		break;
	case 7:
		m_Color = 0xff7f3f00;
		break;
	}
	m_Size = ((g_Global.GetRandInRange(0U,4))+2);
	m_Special = (g_Global.GetRandInRange(0U,99));
	UINT l_numplanets = g_Global.GetRandInRange(0U,4);
	l_numplanets += g_Global.GetRandInRange(0U,4);
	for (UINT j=0;j<l_numplanets;++j)
	{
//		g_Global.LogInfo(" Creating " << j << "/" << l_numplanets << " planet for star " << Index << endl;
		m_Planets.push_back(new CPlanet(j,false,this,false,NULL));
	}
	/*		Starnameindex =	rand()%Size_of_starnames;
		while ((Starnames[Starnameindex].Used != 0) ||
			   (Starnames[Starnameindex].Name[0] == 0))
		  Starnameindex = rand()%Size_of_starnames;
		Stars[i].Starnameindex = Starnameindex;
	Starnames[Starnameindex].Used++;
		for (j=0;j<MAXPLAYERS;++j)
			Stars[i].Players_present[j] = 0;
	*/
//	of << Planets.size() << " planets created at star " << Index << endl;
//	of.close();
}
CStar::~CStar()
{	
//	g_Global.LogInfo(" star ",m_Index," destroyed");
	for(std::vector<CPlanet *>::iterator it = m_Planets.begin();it != m_Planets.end();++it)
	{
		delete (*it);
	}
}
void CStar::OnMouseOver()
{
	POINT l_pos = ScreenPos();
	POINT l_size = ScreenSize();
	g_Gfx.MakeSquare(l_pos.x,l_pos.y,l_size.x,l_size.y,
				0.4f,0xFFFFFF00,0xFFFF00FF,0xFFFFFF00,0xFFFF00FF);
}
void CStar::OnLeftClick()
{
	if(g_Global.m_CurrSelection->IsAFleet())
		dynamic_cast<CFleet *>(g_Global.m_CurrSelection)->SetDestination(this);
	g_Global.m_CurrSelection = this;
}
void CStar::ToolTip()
{
	CToolTip l_tt;
	l_tt.AddLine(m_Name+g_Global.itoa(m_x)+","+g_Global.itoa(m_y));
	l_tt.AddLine("ежд,.:!?Size:"+g_Global.itoa((int)m_Size));
	l_tt.AddLine("Type:"+g_Global.itoa((int)m_Type));
	l_tt.AddLine("Special:"+g_Global.itoa((int)m_Special));
	l_tt.AddLine("Planets:"+g_Global.itoa((int)GetPlanetCount()));
	l_tt.AddLine("Pop:"+g_Global.dtoa(GetSystemPop()));
	l_tt.AddLine("Ind:"+g_Global.dtoa(GetSystemInd()));
	l_tt.AddLine("Sci:"+g_Global.dtoa(GetSystemSci()));
	l_tt.Draw();
}
CGameObject* CStar::Location()
{
	return g_Global.m_NullObject;
}
POINT CStar::ScreenPos()
{
	double l_ratiox = g_Global.m_Width/(double)CStarmap::GetViewportWidth();
	double l_ratioy = g_Global.m_Height/(double)CStarmap::GetViewportHeight();
	POINT l_pos;
	l_pos.x = (int)((m_x*(int)g_Global.m_StarGfxSize - CStarmap::GetViewportPosA().x)*l_ratiox);
	l_pos.y = (int)((m_y*(int)g_Global.m_StarGfxSize - CStarmap::GetViewportPosA().y)*l_ratioy);
	return l_pos;
}
POINT CStar::ScreenSize()
{
	POINT l_size;
	l_size.x = (UINT)(g_Global.m_StarGfxSize*CStarmap::GetZoom()/2);
	l_size.y = (UINT)(g_Global.m_StarGfxSize*CStarmap::GetZoom()/2);
	return l_size;
}
void CStar::Print()
{
	g_Global.LogInfo("star ",(int)m_Index," has ",(int)m_Planets.size()," planets");
	for (size_t i = 0;i < m_Planets.size();++i)
		m_Planets[i]->Print();
}
std::vector<std::string> CStar::GetDataSet(bool p_header)
{
	std::vector<std::string> l_vector;
	if(p_header)
	{
		l_vector.push_back("NAME");
		l_vector.push_back("TYPE");
		l_vector.push_back("SIZE");
		l_vector.push_back("PLANETS");
	}
	else
	{
		l_vector.push_back(m_Name);
		l_vector.push_back(g_Global.itoa(m_Type));
		l_vector.push_back(g_Global.itoa(m_Size));
		l_vector.push_back(g_Global.itoa((int)m_Planets.size()));
	}
	return l_vector;
}
void CStar::Growth()
{
	double sysPop = 0;
	for(UINT i=0;i<m_Planets.size();++i)
	{
		sysPop += m_Planets[i]->GetPopulation();
		if(m_Planets[i]->GetPopulation() > 0)
			m_Planets[i]->PlGrowth();
	}
	double migrants = sysPop/100;
	for(UINT i=0;i<m_Planets.size();++i)
	{
		m_Planets[i]->AddMigrants(migrants/m_Planets.size());
		if(m_Planets[i]->GetPopulation() > m_Planets[i]->GetPopMax())
			m_Planets[i]->SetPopToMax();
	}
}
void CStar::AddPlayerPresence(CEmpire *p_empire)
{
	m_PlayersPresent.push_back(p_empire);
}
void CStar::RemovePlayerPresence(CEmpire *p_empire)
{
	for(std::vector<CEmpire *>::iterator it = m_PlayersPresent.begin();it != m_PlayersPresent.end();++it)
		if(*it == p_empire)
		{
			m_PlayersPresent.erase(it);
			break;
		}
}
UINT CStar::GetIndex()
{
	return m_Index;
}
DWORD CStar::GetColor()
{
	return m_Color;
}
DWORD CStar::GetOwnerColor()
{
	if(GetOwner() == NULL)
		return D3DXCOLOR(0.5f,0.5f,0.5f,1.0f);
	else
		return GetOwner()->GetColor();
}
const std::string& CStar::GetStarName() const
{
	return m_Name;
}
CEmpire* CStar::GetOwner()
{
	if(m_PlayersPresent.empty())
		return NULL;
	else
		return m_PlayersPresent[0];
}
UINT CStar::GetSize()
{
	return m_Size;
}
UINT CStar::GetType()
{
	return m_Type;
}
UINT CStar::GetSpecial()
{
	return m_Special;
}
UINT CStar::GetPlanetCount()
{
	return (UINT)m_Planets.size();
}
double CStar::GetSystemPop()
{
	double sumPop = 0;
	for(UINT i=0;i<m_Planets.size();++i)
		sumPop += m_Planets[i]->GetPopulation();
	return sumPop;
}
double CStar::GetSystemInd()
{
	double sumInd = 0;
	for(UINT i=0;i<m_Planets.size();++i)
		sumInd += m_Planets[i]->GetIndustry();
	return sumInd;
}
double CStar::GetSystemSci()
{
	double sumSci = 0;
	for(UINT i=0;i<m_Planets.size();++i)
		sumSci += m_Planets[i]->GetScience();
	return sumSci;
}
void CStar::CreateHomePlanet()
{
	if(m_Planets.size() == 0)
		m_Planets.push_back(new CPlanet(0,false,this,true,NULL));
	else
		m_Planets[0]->SetAsHome(NULL);
}
CPlanet* CStar::GetPlanet(UINT p_index)
{
	if(p_index < m_Planets.size())
		return m_Planets[p_index];
	else
		return NULL;
}
void CStar::Draw()
{
	POINT l_pos = ScreenPos();
	POINT l_size = ScreenSize();
	g_Gfx.MakeQuad(l_pos.x,l_pos.y,l_size.x,l_size.y,
				0.5f,m_Color,m_Color,m_Color,m_Color,true,g_Textures.m_StarTexture,11,
				((g_Global.m_CurrAnimFrame%11)+(m_Index%11))%11);
	g_MouseHandler.AddGameObject(this);
	// name
//	l_pos.x += (int)(g_Global.m_StarGfxSize/(2*CStarmap::GetZoomNew())-(300*m_Name.length()/(2*g_Global.m_StarGfxSize))/CStarmap::GetZoomNew());
	l_pos.y += (int)(l_size.y+1);
	CTextGroup l_starName(0,l_pos,GetOwnerColor(),g_Gfx.GetFont(2));
	l_starName.AddLine(m_Name);
	g_Gfx.m_textGroups.push_back(l_starName);
}
void CStar::DrawMinimap()
{
	POINT l_pos;
	l_pos.x = (g_Global.m_Width*m_x)/g_Global.m_MapSize;
	l_pos.y = (g_Global.m_Height*m_y)/g_Global.m_MapSize;
	g_Gfx.MakeQuad((l_pos.x/g_Global.m_MinimapScale+g_Global.m_Width-g_Global.m_Width/g_Global.m_MinimapScale),
				(l_pos.y/g_Global.m_MinimapScale),
				g_Global.m_StarGfxSize/6.0f,g_Global.m_StarGfxSize/6.0f,
				0.4f,m_Color,m_Color,m_Color,m_Color,true,g_Textures.m_StarTexture,11,
				((g_Global.m_CurrAnimFrame%11)+(m_Index%11))%11);
}
/*POINT CStar::GetPos()
{
	POINT l_pos = {m_x,m_y};
	return l_pos;
}*/
