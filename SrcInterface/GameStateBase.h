#pragma once
#include "../SrcGame/Global.h"

class CGameStateBase
{
protected:
	CGameStateBase();
public:
	virtual ~CGameStateBase();
	virtual void Draw() = 0;
	virtual void HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown) = 0;
	virtual void HandleMouseMove(bool p_still);
	virtual void HandleLeftClick();
	virtual void HandleRightClick();
	virtual void HandleMiddleClick();
	virtual void HandleMouseWheel();
protected:
	void SetState(GameStates p_NewState,bool p_SetNow);
	void HandleGlobalKeys(UINT nChar, bool bKeyDown, bool bAltDown);
	void DrawCommon();
	std::vector<CGameObject *> m_buttons;
};
