#pragma once
#include "../SrcInterface/GameStateBase.h"


class CGameStateOver : public CGameStateBase
{
public:
	CGameStateOver();
	~CGameStateOver();
	void Draw();
	void HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown);
};
