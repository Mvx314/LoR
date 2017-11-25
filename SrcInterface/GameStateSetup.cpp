#include "dxstdafx.h"
#include "../SrcInterface/GameStateSetup.h"

CGameStateSetup::CGameStateSetup()
{
}

CGameStateSetup::~CGameStateSetup()
{
}

void CGameStateSetup::Draw()
{
	// TODO
	g_Global.m_NumStars = 50;
	g_Global.m_NumEmpires = 8;
	g_Global.m_MapSize = g_Global.m_MapMultiplier*CGlobal::StarGridSize;
	if(g_Global.GenerateUniverse(g_Global.m_NumStars,g_Global.m_NumEmpires,g_Global.m_MapSize))
		g_Global.m_CurrPlayer = g_Global.m_Universe->GenerateEmpires();
	if(g_Global.m_CurrPlayer == NULL)
		g_Global.SetState(GAME_OVER,false);
	else
		g_Global.SetState(GAME_MAIN,false);
}

void CGameStateSetup::HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown)
{
	HandleGlobalKeys(nChar,bKeyDown,bAltDown);
}
