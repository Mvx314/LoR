#include "dxstdafx.h"
#include "../SrcInterface/GameStateBase.h"

CGameStateBase::CGameStateBase()
{
}

CGameStateBase::~CGameStateBase()
{
	for(std::vector<CGameObject *>::iterator it = m_buttons.begin();it != m_buttons.end();++it)
		delete (*it);
	m_buttons.clear();
}

void CGameStateBase::HandleGlobalKeys(UINT nChar, bool bKeyDown, bool bAltDown)
{
	if( bKeyDown )
    {
        switch( nChar )
        {
			case VK_F1: DXUTToggleFullScreen(); break;
        }
    }
}
void CGameStateBase::SetState(GameStates p_NewState,bool p_SetNow)
{
	g_Global.SetState(p_NewState,p_SetNow);
}
void CGameStateBase::DrawCommon()
{
	// interfacebuttons
	for(std::vector<CGameObject *>::iterator it = m_buttons.begin();it != m_buttons.end();++it)
		g_MouseHandler.AddGameObject(*it);
	// tooltip
	{
		POINT l_MouseLoc = g_MouseHandler.GetMousePos();
		if(g_Global.m_HoldDelay > 30 && g_MouseHandler.IsGameObject(l_MouseLoc))
		{
			g_MouseHandler.GetGameObject(l_MouseLoc)->ToolTip();
		}
	}
	HandleMouseMove(true);
}
void CGameStateBase::HandleMouseMove(bool p_still)
{
	if(!p_still)
		g_Global.m_HoldDelay = 0;
	g_MouseHandler.GetGameObject(g_MouseHandler.GetMousePos())->OnMouseOver();
}
void CGameStateBase::HandleLeftClick()
{
	g_Global.m_HoldDelay = 0;
	g_MouseHandler.GetGameObject(g_MouseHandler.GetLCPos())->OnLeftClick();
}
void CGameStateBase::HandleRightClick()
{
}
void CGameStateBase::HandleMiddleClick()
{
}
void CGameStateBase::HandleMouseWheel()
{
}