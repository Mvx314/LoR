#include "dxstdafx.h"
#include "../SrcInterface/GameStateMain.h"
#include "../SrcInterface/MiscButtons.h"

CGameStateMain::CGameStateMain()
{
	m_buttons.push_back(new CButtonSetState(0,g_Global.m_Height-64,128,64,0.0f,GAME_TURN,
		g_Textures.m_Button,"END TURN","Ends your turn"));
	m_buttons.push_back(new CButtonSetState(128,g_Global.m_Height-64,128,64,0.0f,GAME_DATA,
		g_Textures.m_Button,"LEDGER","Ledger"));
	UINT l_minimapW = g_Global.m_Width/g_Global.m_MinimapScale;
	UINT l_minimapH = g_Global.m_Height/g_Global.m_MinimapScale;
	m_buttons.push_back(new CMinimap(g_Global.m_Width-l_minimapW,0,l_minimapW-1,l_minimapH+1,0.4f));
//	m_buttons.push_back(new CButtonSlider(&g_Global.m_MinimapScale,5,15,g_Global.m_Width-20,l_minimapH,20,200,0.0f));
	m_buttons.push_back(new CButtonSlider(&g_Global.m_MinimapScale,5,15,g_Global.m_Width-l_minimapW,l_minimapH,l_minimapW,10,0.0f));
}
//CGameStateMain::~CGameStateMain()
//{
//	for(std::vector<CGameObject *>::iterator it = m_buttons.begin();it != m_buttons.end();++it)
//		delete (*it);
//	m_buttons.clear();
//}
void CGameStateMain::Draw()
{
	// background
	g_Gfx.MakeQuad(0.0f,0.0f,g_Global.m_Width,g_Global.m_Height,1.0f,
					0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,false,g_Textures.m_BackGround,1,0);
	// starmap
	CStarmap::DrawStarmap();
	DrawCommon();
}

void CGameStateMain::HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown)
{
	HandleGlobalKeys(nChar,bKeyDown,bAltDown);
	if( bKeyDown )
	{
		g_Global.m_HoldDelay = 0;
		switch( nChar )
		{
			case VK_F5: g_Global.SetState(GAME_MENU,false); break;
			case 'N': g_Global.m_CurrSelection = g_Global.m_NullObject; break;
			case VK_UP: if(DXUTIsKeyDown(VK_LCONTROL))
							CStarmap::ChangeFocus(0,-100);
						else
							  CStarmap::ChangeFocus(0,-10);
				break;
			case VK_DOWN: if(DXUTIsKeyDown(VK_LCONTROL))
							  CStarmap::ChangeFocus(0,100);
						  else
							  CStarmap::ChangeFocus(0,10);
				break;
			case VK_LEFT: if(DXUTIsKeyDown(VK_LCONTROL))
							  CStarmap::ChangeFocus(-100,0);
						  else
							  CStarmap::ChangeFocus(-10,0);
				break;
			case VK_RIGHT: if(DXUTIsKeyDown(VK_LCONTROL))
								CStarmap::ChangeFocus(100,0);
						   else
								CStarmap::ChangeFocus(10,0);
				break;
			case 'Z': CStarmap::ChangeZoom(0.1f);break;
			case 'X': CStarmap::ChangeZoom(-0.1f);break;
			default: break;
		}
	}
}
//void CGameStateMain::HandleMouseMove(bool p_still)
//{
//}
void CGameStateMain::HandleRightClick()
{
	g_Global.m_HoldDelay = 0;
	g_Global.m_CurrSelection = g_Global.m_NullObject;
	g_Global.m_CurrSelectionLocation = g_Global.m_NullObject;
	g_MouseHandler.GetGameObject(g_MouseHandler.GetRCPos())->OnRightClick();
}
void CGameStateMain::HandleMouseWheel()
{
	CStarmap::ChangeZoom(g_MouseHandler.GetMouseWheel() > 0 ? 0.1f : -0.1f);
}