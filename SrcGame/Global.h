#pragma once
#include "dxstdafx.h"
#pragma warning(1:4061)
#pragma warning(1:4296)
//#pragma warning(1:4365) // signed/unsigned
//#pragma warning(1:4640) // thread safety
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include "../SrcGame/Universe.h"
#include "../SrcGame/Starmap.h"
#include "../SrcInterface/Gfx.h"
#include "../SrcInterface/MouseHandler.h"
#include "../SrcInterface/TextGroup.h"
#include "../SrcInterface/Textures.h"

enum GameStates
{
	GAME_NULL,
	GAME_MAIN,
	GAME_MENU,
	GAME_OPTIONS,
	GAME_SETUP,
	GAME_INTRO,
	GAME_DATA,
	GAME_TURN,
	GAME_BATTLE,
	GAME_RESULT,
	GAME_OVER
};
extern LPDIRECT3DVERTEXBUFFER9 g_pVB;
//extern std::vector<ID3DXFont*> g_pFonts;
extern ID3DXSprite* g_pTextSprite;
extern class CGlobal g_Global;
extern class CTextures g_Textures;
extern class CGfx g_Gfx;
extern class CMouseHandler g_MouseHandler;
extern class CGameStateBase *g_GameState;

class CUniverse;
class CEmpire;
class CGameObject;

class CGlobal
{
private:
	GameStates m_GameState;
	GameStates m_LastGameState;
	std::vector<std::string> m_logData;
public:
	CUniverse *m_Universe;
	std::vector<ID3DXFont*> m_pFonts;
	static const UINT StarGridSize = 16;
	UINT m_CurrAnimFrame;
	UINT m_HoldDelay;
	CEmpire *m_CurrPlayer;
	CGameObject *m_CurrSelectionLocation;
	CGameObject *m_NullObject;
	CGameObject *m_CurrSelection;
	UINT m_NumStars;
	UINT m_MapMultiplier;
	UINT m_MapSize;
	UINT m_MinimapScale;
	UINT m_StarGfxSize;
	UINT m_FleetGfxSize;
	UINT m_NumEmpires;
	UINT m_Width;
	UINT m_Height;
	UINT m_TTWidth;
	UINT m_TTHeight;
public:
	CGlobal();
	~CGlobal();
	bool GenerateUniverse(UINT,UINT,UINT);
	GameStates GetState();
	GameStates SetState(const GameStates p_NewState,const bool p_SetNow);

	// logging
	void LogInfo(const std::string&);
	void LogInfo(const std::string&,const int&,const std::string&);
	void LogInfo(const std::string&,const int&,const std::string&,const int&,const std::string&);
	void PrintLog();
	void ShowBox(const wchar_t * p_title,const UINT,const UINT);
	void ShowData(const std::string&,const std::string&,const bool p_reset);
	void ShowData(const std::string&,const double&,const bool p_reset);
	void ShowData(const std::string&,const int&,const bool p_reset);

	// utilities
	UINT GetRandInRange(const UINT p_start,const UINT p_end);
	double GetRandInRange(const double p_start,const double p_end);
	std::string itoa(const int& p_value);
	std::string dtoa(const double& p_value);
	std::string Hexify(const int& p_value);
	double Scale(const double& p_value,const double& p_srcmin,const double& p_srcmax,
					const double& p_destmin,const double& p_destmax);

	HRESULT LoadFonts(IDirect3DDevice9* pd3dDevice);
	HRESULT ResetFonts();
	void UnResetFonts();
	void UnLoadFonts();
};
