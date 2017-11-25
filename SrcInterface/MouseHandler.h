#pragma once
#include <vector>

class CGameObject;

class CMouseHandler
{
private:
	POINT m_mousePos,m_LCPos,m_RCPos,m_MCPos;
	int m_MouseWheel;
	bool m_Focus;
	std::vector<CGameObject *> m_GameObjects;
public:
	CMouseHandler();
	~CMouseHandler();
	void SetMousePos(int p_x,int p_y);
	void LeftClick(int p_x,int p_y);
	void RightClick(int p_x,int p_y);
	void MiddleClick(int p_x,int p_y);
	void SetMouseWheel(int p_delta);
	POINT GetMousePos();
	POINT GetLCPos();
	POINT GetRCPos();
	POINT GetMCPos();
	int GetMouseWheel();
	void SetFocus(bool);
	bool GetFocus();
	CGameObject* GetGameObject(POINT);
	CGameObject* GetGameObjectOwner(CGameObject *p_button);
	bool IsGameObject(POINT p_xy);
	void ClearGameObjects();
	void AddGameObject(CGameObject *p_button);
};
