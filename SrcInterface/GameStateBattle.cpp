#include "dxstdafx.h"
#include "../SrcInterface/GameStateBattle.h"

CGameStateBattle::CGameStateBattle()
{
}

CGameStateBattle::~CGameStateBattle()
{
}

void CGameStateBattle::Draw()
{
}

void CGameStateBattle::HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown)
{
	HandleGlobalKeys(nChar,bKeyDown,bAltDown);
}
