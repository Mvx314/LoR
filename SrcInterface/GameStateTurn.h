#pragma once
#include "../SrcInterface/GameStateBase.h"

class CGameStateTurn : public CGameStateBase
{
public:
	CGameStateTurn();
	~CGameStateTurn();
	void Draw();
	void HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown);
};
