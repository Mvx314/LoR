#pragma once
#include "../SrcInterface/GameStateBase.h"


class CGameStateNull :
	public CGameStateBase
{
public:
	CGameStateNull();
	~CGameStateNull();
	void Draw();
	void HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown);
};
