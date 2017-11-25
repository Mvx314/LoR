#include "dxstdafx.h"
#include "../SrcInterface/GameStateOptions.h"

CGameStateOptions::CGameStateOptions()
{
}

CGameStateOptions::~CGameStateOptions()
{
}

void CGameStateOptions::Draw()
{
}

void CGameStateOptions::HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown)
{
	HandleGlobalKeys(nChar,bKeyDown,bAltDown);
}
