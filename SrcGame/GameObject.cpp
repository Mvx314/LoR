#include "dxstdafx.h"
#include "../SrcGame/Global.h"
#include "../SrcGame/GameObject.h"

CGameObject::CGameObject() :
	m_x (0),
	m_y (0),
	m_width (1),
	m_height(1)
{
}
CGameObject::~CGameObject()
{
}
void CGameObject::OnMouseOver()
{
}
void CGameObject::OnRightClick()
{
}
void CGameObject::OnMiddleClick()
{
}
void CGameObject::OnWheelMove(int p_delta)
{
}
void CGameObject::ToolTip()
{
}
CGameObject* CGameObject::Owner()
{
	return g_Global.m_NullObject;
}
POINT CGameObject::ScreenPos()
{
	POINT l_pos = {m_x,m_y};
	return l_pos;
}
POINT CGameObject::ScreenSize()
{
	POINT l_pos = {m_width,m_height};
	return l_pos;
}
POINT CGameObject::InternalLCPos()
{
	POINT l_pos = ScreenPos();
	l_pos.x = g_MouseHandler.GetLCPos().x - l_pos.x;
	l_pos.y = g_MouseHandler.GetLCPos().y - l_pos.y;
	return l_pos;
}
bool CGameObject::IsAFleet()
{
	return false;
}
bool CGameObject::IsAStar()
{
	return false;
}
