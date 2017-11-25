#pragma once

#include "GameObject.h"

class CGameObject;
class CShipClass;
class CStar;
class CEmpire;

class CShip : public CGameObject
{
private:
	CShipClass *m_shipClass;
	UINT m_index;
	CStar *m_location;
	CEmpire *m_owner;
public:
	CShip(UINT p_id,CShipClass *p_shipClass,CStar *p_location,CEmpire *p_owner);
	~CShip();
	void Draw();
	void OnLeftClick();
	CGameObject* Location();
	POINT ScreenPos();
	POINT ScreenSize();
	UINT GetIndex();
};
