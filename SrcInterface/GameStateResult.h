#pragma once
#include "../SrcInterface/GameStateBase.h"


class CGameStateResult : public CGameStateBase
{
public:
	CGameStateResult();
	~CGameStateResult();
	void Draw();
	void HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown);
};
