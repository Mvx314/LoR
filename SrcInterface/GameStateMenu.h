#pragma once
#include "../SrcInterface/GameStateBase.h"

class CGameStateMenu : public CGameStateBase
{
public:
	CGameStateMenu();
	~CGameStateMenu();
	void Draw();
	void HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown);
};
