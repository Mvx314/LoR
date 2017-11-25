#pragma once
#include "../SrcInterface/GameStateBase.h"

class CGameStateIntro : public CGameStateBase
{
public:
	CGameStateIntro();
	~CGameStateIntro();
	void Draw();
	void HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown);
};
