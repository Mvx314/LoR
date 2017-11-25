#pragma once
#include "../SrcInterface/GameStateBase.h"

class CGameStateMain : public CGameStateBase
{
public:
	CGameStateMain();
//	~CGameStateMain();
	void Draw();
	void HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown);
//	void HandleMouseMove(bool p_still);
	void HandleRightClick();
	void HandleMouseWheel();
};
