#pragma once
#include "../SrcInterface/GameStateBase.h"


class CGameStateBattle : public CGameStateBase
{
public:
	CGameStateBattle();
	~CGameStateBattle();
	void Draw();
	void HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown);
};
