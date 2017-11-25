#include "dxstdafx.h"
#include "../SrcInterface/GameStateMenu.h"

CGameStateMenu::CGameStateMenu()
{
}

CGameStateMenu::~CGameStateMenu()
{
}

void CGameStateMenu::Draw()
{
}
void CGameStateMenu::HandleKeys(UINT nChar, bool bKeyDown, bool bAltDown)
{
	HandleGlobalKeys(nChar,bKeyDown,bAltDown);
	if( bKeyDown )
	{
		switch( nChar )
		{
			case VK_F5: g_Global.SetState(GAME_INTRO,false); break;
		}
	}
}
