#include "dxstdafx.h"
#include "../SrcGame/Global.h"
#include "../SrcInterface/GameStateBase.h"
#include "../SrcInterface/GameStateMain.h"
#include "../SrcInterface/GameStateSetup.h"
#include "../SrcInterface/GameStateIntro.h"
#include "../SrcInterface/GameStateTurn.h"
#include "../SrcInterface/GameStateMenu.h"
#include "../SrcInterface/GameStateOptions.h"
#include "../SrcInterface/GameStateData.h"
#include "../SrcInterface/GameStateBattle.h"
#include "../SrcInterface/GameStateResult.h"
#include "../SrcInterface/GameStateOver.h"
#include "../SrcInterface/GameStateNull.h"
#include "../SrcInterface/MiscButtons.h"
#include <time.h>

// Globals
CGlobal g_Global;
CTextures g_Textures;
CGfx g_Gfx;
CMouseHandler g_MouseHandler;
CGameStateBase *g_GameState = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
//std::vector<ID3DXFont*> g_pFonts;
ID3DXSprite* g_pTextSprite = NULL;

CGlobal::CGlobal() :
	m_GameState (GAME_INTRO),
	m_LastGameState (GAME_NULL),
	m_Universe (NULL),
	m_NullObject (new CGameObjectNull()),
	m_CurrAnimFrame(0),
	m_HoldDelay(0),
	m_CurrPlayer(NULL),
	m_CurrSelection(m_NullObject),
//	m_CurrSelectionType(GO_NULL),
	m_CurrSelectionLocation(NULL),
	m_NumStars(50),
	m_MapMultiplier(3),
	m_MapSize(g_Global.m_MapMultiplier*CGlobal::StarGridSize),
	m_MinimapScale(10),
	m_StarGfxSize(30),
	m_FleetGfxSize(30),
	m_NumEmpires(8),
	m_Width(0),
	m_Height(0),
	m_TTWidth(100),
	m_TTHeight(100)
{
}
CGlobal::~CGlobal()
{
	delete m_NullObject;
	delete m_Universe;
	PrintLog();
}
bool CGlobal::GenerateUniverse(UINT p_numStars,UINT p_numEmpires,UINT p_mapSize)
{
	if(p_numStars < p_numEmpires)
	{
		LogInfo("Too many empires, not enough stars");
		return false;
	}
	m_Universe = new CUniverse();
	if(!m_Universe)
		return false;
	m_Universe->Settings(p_numStars,p_numEmpires,p_mapSize);
	do 
	{
	} while(!(m_Universe->Create()));
	POINT l_posA = {0,0};
	POINT l_posB = {p_mapSize*m_StarGfxSize,p_mapSize*m_StarGfxSize};
	CStarmap::SetViewportPos(l_posA,l_posB);
	return true;
}
GameStates CGlobal::GetState()
{
	return m_GameState;
}
GameStates CGlobal::SetState(const GameStates p_NewState,const bool p_SetNow)
{
	m_LastGameState = m_GameState;
	m_GameState = p_NewState;
	if(p_SetNow)
	{
		delete g_GameState;
		switch(p_NewState)
		{
		case GAME_MAIN :
			g_GameState = new CGameStateMain();
			break;
		case GAME_SETUP :
			g_GameState = new CGameStateSetup();
			break;
		case GAME_INTRO :
			g_GameState = new CGameStateIntro();
			break;
		case GAME_TURN :
			g_GameState = new CGameStateTurn();
			break;
		case GAME_MENU :
			g_GameState = new CGameStateMenu();
			break;
		case GAME_OPTIONS :
			g_GameState = new CGameStateOptions();
			break;
		case GAME_DATA :
			g_GameState = new CGameStateData();
			break;
		case GAME_BATTLE :
			g_GameState = new CGameStateBattle();
			break;
		case GAME_RESULT :
			g_GameState = new CGameStateResult();
			break;
		case GAME_OVER :
			g_GameState = new CGameStateOver();
			break;
		case GAME_NULL :
			g_GameState = new CGameStateNull();
			break;
		default:
			LogInfo("Unknown GameState");
			g_GameState = new CGameStateNull();
			break;
		}
	}
	return m_GameState;
}
void CGlobal::LogInfo(const std::string& p_What)
{
	std::stringstream str;
	str << p_What << " at time " << clock() << std::endl;
	m_logData.push_back(str.str());
}
void CGlobal::LogInfo(const std::string& p_What1,const int& p_What2,const std::string& p_What3)
{
	std::stringstream str;
	str << p_What1 << p_What2 << p_What3 << " at time " << clock() << std::endl;
	m_logData.push_back(str.str());
}
void CGlobal::LogInfo(const std::string& p_What1,const int& p_What2,const std::string& p_What3,
					  const int& p_What4,const std::string& p_What5)
{
	std::stringstream str;
	str << p_What1 << p_What2 << p_What3 << p_What4 << p_What5 << " at time " << clock() << std::endl;
	m_logData.push_back(str.str());
}
void CGlobal::PrintLog()
{
	std::ofstream of("errorlog.txt",std::ios::out | std::ios::app);
	for(std::vector<std::string>::iterator it = m_logData.begin();it != m_logData.end();++it)
		of << (*it);
	of.close();
}
void CGlobal::ShowBox(const wchar_t * p_title,const UINT p_x,const UINT p_y)
{
	wchar_t text[100];
	swprintf_s(text,100,L"(%d,%d)",p_x,p_y);
	MessageBox(NULL,text,p_title,MB_OK);
}
void CGlobal::ShowData(const std::string& p_text,const std::string& p_string,const bool p_reset)
{
	static std::map<std::string,std::string> l_items;
	l_items[p_text] = p_string;
	if(p_reset)
	{
		int i = 0;
		for(std::map<std::string,std::string>::iterator it = l_items.begin();it != l_items.end();++it,++i)
		{
			POINT l_pos = {0,i*10};
			CTextGroup l_info(0,l_pos,0xffffffff,g_Gfx.GetFont(2));
			l_info.AddLine(it->first+it->second);
			g_Gfx.m_textGroups.push_back(l_info);
		}
	}
}
void CGlobal::ShowData(const std::string& p_text,const double& p_num,const bool p_reset)
{
	ShowData(p_text,dtoa(p_num),p_reset);
}
void CGlobal::ShowData(const std::string& p_text,const int& p_num,const bool p_reset)
{
	ShowData(p_text,itoa(p_num),p_reset);
}
UINT CGlobal::GetRandInRange(const UINT p_start,const UINT p_end)
{
	UINT num;
	rand_s(&num);
	return (num%(p_end-p_start+1))+p_start;
}
double CGlobal::GetRandInRange(const double p_start,const double p_end)
{
	UINT l_num = GetRandInRange(0U,999);
	return ((p_end-p_start)*(l_num/1000.0f))+p_start;
}
std::string CGlobal::itoa(const int& p_value)
{
	std::ostringstream o;
	if(!(o << p_value))
		return std::string("ERROR");
	return o.str();
}
std::string CGlobal::dtoa(const double& p_value)
{
	std::ostringstream o;
	if(!(o << p_value))
		return std::string("ERROR");
	return o.str();
}
std::string CGlobal::Hexify(const int& p_value)
{
	std::ostringstream o;
	if(!(o << std::hex << p_value))
		return std::string("ERROR");
	return o.str();
}
double CGlobal::Scale(const double& p_value,const double& p_srcmin,const double& p_srcmax,
					const double& p_destmin,const double& p_destmax)
{
	assert(p_srcmin >= 0);
	assert(p_srcmax > p_srcmin);
	assert(p_destmin >= 0);
	assert(p_destmax > p_destmin);
	assert(p_value >= p_srcmin);
	assert(p_value <= p_srcmax);
	double l_ratio = (p_value-p_srcmin)/(p_srcmax-p_srcmin);
	double l_result = l_ratio*(p_destmax-p_destmin)+p_destmin;
	return l_result;
}
HRESULT CGlobal::LoadFonts(IDirect3DDevice9* pd3dDevice)
{
	HRESULT hr;
	ID3DXFont* l_pFont;
	m_pFonts.clear();
	V_RETURN(D3DXCreateFont(pd3dDevice,13,0,FW_BOLD,1,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,
						DEFAULT_PITCH | FF_DONTCARE,L"Arial",&l_pFont));
	m_pFonts.push_back(l_pFont);
	V_RETURN(D3DXCreateFont(pd3dDevice,14,0,FW_BOLD,1,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,
						DEFAULT_PITCH | FF_DONTCARE,L"Arial",&l_pFont));
	m_pFonts.push_back(l_pFont);
	V_RETURN(D3DXCreateFont(pd3dDevice,15,0,FW_BOLD,1,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,
						DEFAULT_PITCH | FF_DONTCARE,L"Arial",&l_pFont));
	m_pFonts.push_back(l_pFont);
	V_RETURN(D3DXCreateFont(pd3dDevice,16,0,FW_BOLD,1,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,
						DEFAULT_PITCH | FF_DONTCARE,L"Arial",&l_pFont));
	m_pFonts.push_back(l_pFont);
	V_RETURN(D3DXCreateFont(pd3dDevice,17,0,FW_BOLD,1,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,
						DEFAULT_PITCH | FF_DONTCARE,L"Arial",&l_pFont));
	m_pFonts.push_back(l_pFont);
	V_RETURN(D3DXCreateFont(pd3dDevice,19,0,FW_BOLD,1,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,
						DEFAULT_PITCH | FF_DONTCARE,L"Arial",&l_pFont));
	m_pFonts.push_back(l_pFont);
	V_RETURN(D3DXCreateFont(pd3dDevice,21,0,FW_BOLD,1,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,
						DEFAULT_PITCH | FF_DONTCARE,L"Arial",&l_pFont));
	m_pFonts.push_back(l_pFont);
	V_RETURN(D3DXCreateFont(pd3dDevice,25,0,FW_BOLD,1,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,
						DEFAULT_PITCH | FF_DONTCARE,L"Arial",&l_pFont));
	m_pFonts.push_back(l_pFont);
	return S_OK;
}
HRESULT CGlobal::ResetFonts()
{
	HRESULT hr;
	if(!m_pFonts.empty())
		for(std::vector<ID3DXFont *>::iterator it = m_pFonts.begin();it != m_pFonts.end();++it)
			V_RETURN((*it)->OnResetDevice());
	return S_OK;
}
void CGlobal::UnResetFonts()
{
	if(!m_pFonts.empty())
		for(std::vector<ID3DXFont *>::iterator it = m_pFonts.begin();it != m_pFonts.end();++it)
			(*it)->OnLostDevice();
}
void CGlobal::UnLoadFonts()
{
	for(std::vector<ID3DXFont *>::iterator it = m_pFonts.begin();it != m_pFonts.end();++it)
		SAFE_RELEASE(*it);
}
