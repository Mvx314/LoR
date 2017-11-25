#pragma once
#include "../SrcGame/Global.h"
#include "../SrcGame/GameObject.h"
#include "../SrcInterface/ToolTip.h"

class CGameObject;

class CGameObjectNull : public CGameObject
{
public:
	CGameObjectNull();
	void Draw(){};
	void OnLeftClick(){};
	void ToolTip(){};
	CGameObject* Location(){return this;};
	POINT ScreenSize();
};
class CButtonSetState : public CGameObject
{
public:
	CButtonSetState(int p_x,int p_y,int p_width,int p_height,double p_depth,
		enum GameStates p_newState,IDirect3DTexture9* p_graphic,std::string p_label,std::string p_toolTip);
	void Draw();
	void OnLeftClick();
	void ToolTip();
	CGameObject* Location(){return g_Global.m_NullObject;};
private:
	GameStates m_newState;
	IDirect3DTexture9* m_graphic;
	std::string m_label;
	std::string m_toolTip;
	double m_depth;
};
class CButtonSlider : public CGameObject
{
public:
	CButtonSlider(UINT *p_variable,UINT p_min,UINT p_max,int p_x,int p_y,UINT p_width,UINT p_height,double p_depth);
	void Draw();
	void OnLeftClick();
	void ToolTip();
	CGameObject* Location(){return g_Global.m_NullObject;};
private:
	UINT *m_variable;
	UINT m_min;
	UINT m_max;
	double m_depth;
};
class CButtonSetTab : public CGameObject
{
public:
	CButtonSetTab(int p_x,int p_y,int p_width,int p_height,double p_depth,
					enum DataTabs p_newTab,IDirect3DTexture9* p_graphic,std::string p_label,std::string p_toolTip);
	void Draw();
	void OnLeftClick();
	void ToolTip();
	CGameObject* Location(){return g_Global.m_NullObject;};
private:
	DataTabs m_newTab;
	IDirect3DTexture9* m_graphic;
	std::string m_label;
	std::string m_toolTip;
	double m_depth;
};
