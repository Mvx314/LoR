#pragma once
#include "../SrcInterface/GameStateBase.h"


class CGameStateOptions :
	public CGameStateBase
{
public:
	CGameStateOptions();
	~CGameStateOptions();
	void Draw();
	void HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown);
};
