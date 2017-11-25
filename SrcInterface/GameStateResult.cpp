#include "dxstdafx.h"
#include "../SrcInterface/GameStateResult.h"

CGameStateResult::CGameStateResult()
{
}

CGameStateResult::~CGameStateResult()
{
}

void CGameStateResult::Draw()
{
}

void CGameStateResult::HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown)
{
	HandleGlobalKeys(nChar,bKeyDown,bAltDown);
}
