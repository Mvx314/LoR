#include "dxstdafx.h"
#include "../SrcInterface/GameStateIntro.h"

CGameStateIntro::CGameStateIntro()
{
}

CGameStateIntro::~CGameStateIntro()
{
}

void CGameStateIntro::Draw()
{
	SetState(GAME_MAIN,false);
}

void CGameStateIntro::HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown)
{
	HandleGlobalKeys(nChar,bKeyDown,bAltDown);
}
