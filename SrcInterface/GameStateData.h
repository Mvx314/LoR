#pragma once
#include "../SrcInterface/GameStateBase.h"

enum DataTabs
{
	TAB_STAR,
	TAB_FLEET
};

class CGameStateData : public CGameStateBase
{
public:
	CGameStateData();
	~CGameStateData();
	void Draw();
	void HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown);
	static void SetTab(DataTabs p_NewTab);
private:
	static DataTabs m_currTab;
};
