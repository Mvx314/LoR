#include "dxstdafx.h"
#include "../SrcInterface/MouseHandler.h"
#include "../SrcInterface/GameStateBase.h"
#include "../SrcGame/GameObject.h"

CMouseHandler::CMouseHandler()
{
}
CMouseHandler::~CMouseHandler()
{
	ClearGameObjects();
}
void CMouseHandler::SetMousePos(int p_x, int p_y)
{
	m_mousePos.x = p_x;
	m_mousePos.y = p_y;
	g_GameState->HandleMouseMove(false);
}
void CMouseHandler::LeftClick(int p_x, int p_y)
{
	m_LCPos.x = p_x;
	m_LCPos.y = p_y;
	g_GameState->HandleLeftClick();
}
void CMouseHandler::RightClick(int p_x, int p_y)
{
	m_RCPos.x = p_x;
	m_RCPos.y = p_y;
	g_GameState->HandleRightClick();
}
void CMouseHandler::MiddleClick(int p_x, int p_y)
{
	m_MCPos.x = p_x;
	m_MCPos.y = p_y;
	g_GameState->HandleMiddleClick();
}
void CMouseHandler::SetMouseWheel(int p_delta)
{
	m_MouseWheel = p_delta;
	g_GameState->HandleMouseWheel();
}
POINT CMouseHandler::GetMousePos()
{
	return m_mousePos;
}
POINT CMouseHandler::GetLCPos()
{
	return m_LCPos;
}
POINT CMouseHandler::GetRCPos()
{
	return m_RCPos;
}
POINT CMouseHandler::GetMCPos()
{
	return m_MCPos;
}
int CMouseHandler::GetMouseWheel()
{
	return m_MouseWheel;
}
void CMouseHandler::SetFocus(bool p_value)
{
	m_Focus = p_value;
}
bool CMouseHandler::GetFocus()
{
	return m_Focus;
}
CGameObject* CMouseHandler::GetGameObject(POINT p_xy)
{
	// Last object entered returned when overlapping
	CGameObject *l_object = g_Global.m_NullObject;
	for(std::vector<CGameObject *>::iterator it = m_GameObjects.begin();it != m_GameObjects.end();++it)
	{
		if( (*it)->ScreenPos().x < p_xy.x &&
			(*it)->ScreenPos().y < p_xy.y &&
			(*it)->ScreenPos().x + (*it)->ScreenSize().x > p_xy.x &&
			(*it)->ScreenPos().y + (*it)->ScreenSize().y > p_xy.y )
		{
			l_object = *it;
		}
	}
	return l_object;
}
CGameObject* CMouseHandler::GetGameObjectOwner(CGameObject *p_GameObject)
{
	if(p_GameObject == g_Global.m_NullObject)
		return g_Global.m_NullObject;
	return p_GameObject->Owner();
}
bool CMouseHandler::IsGameObject(POINT p_xy)
{
	if(GetGameObject(p_xy) == g_Global.m_NullObject)
		return false;
	else
		return true;
}
void CMouseHandler::ClearGameObjects()
{
// !!!!!!!!!!!! IDIOT !!!!!!!!!!!!!!!!!!
//	for(std::vector<CGameObject *>::iterator it = m_GameObjects.begin();it != m_GameObjects.end();++it)
//	{
//		delete (*it);
//	}
	m_GameObjects.clear();
}
void CMouseHandler::AddGameObject(CGameObject *p_GameObject)
{
	m_GameObjects.push_back(p_GameObject);
}
