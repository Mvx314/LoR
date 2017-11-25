#include "dxstdafx.h"
#include "../SrcInterface/GameStateNull.h"

CGameStateNull::CGameStateNull()
{
}

CGameStateNull::~CGameStateNull()
{
}

void CGameStateNull::Draw()
{
}

void CGameStateNull::HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown)
{
	HandleGlobalKeys(nChar,bKeyDown,bAltDown);
}
