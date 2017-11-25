#pragma once

class CGameObject
{
protected:
	CGameObject();
public:
	virtual ~CGameObject();
	virtual void Draw() = 0;
	virtual void OnMouseOver();
	virtual void OnLeftClick() = 0;
	virtual void OnRightClick();
	virtual void OnMiddleClick();
	virtual void OnWheelMove(int p_delta);
	virtual void ToolTip();
	virtual CGameObject* Location() = 0;
	virtual CGameObject* Owner();
	virtual POINT ScreenPos();
	virtual POINT ScreenSize();
	virtual POINT InternalLCPos();
	virtual bool IsAFleet();
	virtual bool IsAStar();
protected:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
};
