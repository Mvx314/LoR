#pragma once
#include "../SrcGame/GameObject.h"

class CGameObject;

class CStarmap
{
private:
	CStarmap();
	~CStarmap();
	static POINT m_ViewportPosA;
	static POINT m_ViewportPosB;
	static POINT m_Focus;
public:
	static void ChangeZoom(const double p_zoom);
	static double GetZoom();
	static void SetFocus(UINT p_x,UINT p_y);
	static void ChangeFocus(int p_x,int p_y);
	static POINT GetFocus();
	static void DrawStarmap();
	friend class CMinimap;
	// new plan
	static void SetViewportPos(const POINT p_posA,const POINT p_posB);
	static POINT GetViewportPosA();
	static POINT GetViewportPosB();
	static UINT GetViewportWidth();
	static UINT GetViewportHeight();
};

class CMinimap : public CGameObject
{
public:
	CMinimap(int p_x,int p_y,int p_width,int p_height,double p_depth);
	void Draw();
	void OnLeftClick();
	void ToolTip(){};
	CGameObject* Location(){return this;};
private:
	double m_depth;
};