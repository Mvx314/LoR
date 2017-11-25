#include "dxstdafx.h"
#include "../SrcInterface/GameStateTurn.h"

CGameStateTurn::CGameStateTurn()
{
}

CGameStateTurn::~CGameStateTurn()
{
}

void CGameStateTurn::Draw()
{
	g_Global.m_Universe->ProcessTurn();
	g_Global.m_CurrSelection = g_Global.m_NullObject;
	g_Global.m_CurrSelectionLocation = NULL;
	g_Global.SetState(GAME_MAIN,false);
}

void CGameStateTurn::HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown)
{
	HandleGlobalKeys(nChar,bKeyDown,bAltDown);
}
