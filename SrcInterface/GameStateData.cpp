#include "dxstdafx.h"
#include "../SrcInterface/GameStateData.h"
#include "../SrcInterface/MiscButtons.h"
#include "../SrcGame/Star.h"
#include "../SrcGame/Empire.h"

DataTabs CGameStateData::m_currTab = TAB_STAR;

CGameStateData::CGameStateData()
{
	m_buttons.push_back(new CButtonSetState(0,g_Global.m_Height-64,128,64,0.0f,GAME_MAIN,
		g_Textures.m_Button,"MAIN MAP","Back to map"));
	m_buttons.push_back(new CButtonSetTab(100,0,128,32,0.0f,TAB_STAR,g_Textures.m_Button,"Stars","Stars"));
	m_buttons.push_back(new CButtonSetTab(230,0,128,32,0.0f,TAB_FLEET,g_Textures.m_Button,"Fleets","Fleets"));
}
CGameStateData::~CGameStateData()
{
}
void CGameStateData::Draw()
{
	// background
	g_Gfx.MakeQuad(0.0f,0.0f,g_Global.m_Width,g_Global.m_Height,1.0f,
					0xFFAAAAAA,0xFFAAAAAA,0xFFAAAAAA,0xFFAAAAAA,false,g_Textures.m_BackGround,1,0);
	DrawCommon();
	switch(m_currTab)
	{
	case TAB_STAR:
		{
			std::vector<CStar *> l_stars = g_Global.m_Universe->GetStarList();
			int i = 0;
			POINT l_pos = {100,40};
			std::vector<std::string> l_dataSet = (*(l_stars.begin()))->GetDataSet(true);
			for(std::vector<std::string>::iterator it = l_dataSet.begin();it != l_dataSet.end();++it)
			{
				CTextGroup l_dataUnit(0,l_pos,0xffffffff,g_Gfx.GetFont(2));
				l_dataUnit.AddLine(*it);
				l_pos.x += 100;
				g_Gfx.m_textGroups.push_back(l_dataUnit);
			}
			for(std::vector<CStar *>::iterator it = l_stars.begin();it != l_stars.end();++it,++i)
			{
				POINT l_pos = {100,51+i*10};
				std::vector<std::string> l_dataSet = (*it)->GetDataSet(false);
				for(std::vector<std::string>::iterator ite = l_dataSet.begin();ite != l_dataSet.end();++ite)
				{
					CTextGroup l_dataUnit(0,l_pos,0xffffffff,g_Gfx.GetFont(2));
					l_dataUnit.AddLine(*ite);
					l_pos.x += 100;
					g_Gfx.m_textGroups.push_back(l_dataUnit);
				}
			}
		}
	case TAB_FLEET:
		{
		}
	}
}
void CGameStateData::HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown)
{
	HandleGlobalKeys(nChar,bKeyDown,bAltDown);
}
void CGameStateData::SetTab(DataTabs p_NewTab)
{
	m_currTab = p_NewTab;
}