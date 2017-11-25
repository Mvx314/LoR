#include "dxstdafx.h"
#include "../SrcInterface/GameStateOver.h"

CGameStateOver::CGameStateOver()
{
}

CGameStateOver::~CGameStateOver()
{
}

void CGameStateOver::Draw()
{
	PostQuitMessage(0);
}

void CGameStateOver::HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown)
{
	HandleGlobalKeys(nChar,bKeyDown,bAltDown);
}
