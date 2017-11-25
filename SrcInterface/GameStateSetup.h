#pragma once
#include "../SrcInterface/GameStateBase.h"

class CGameStateSetup : public CGameStateBase
{
public:
	CGameStateSetup();
	~CGameStateSetup();
	void Draw();
	void HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown);
};
