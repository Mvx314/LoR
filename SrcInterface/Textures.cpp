#include "dxstdafx.h"
#include "../SrcInterface/Textures.h"

CTextures::CTextures()
{
m_BackGround = NULL;
m_StarTexture = NULL;
m_PlanetTexture = NULL;
m_MiscBG = NULL;
m_Button = NULL;
m_ArrowUp = NULL;
m_ArrowDown = NULL;
m_ArrowLeft = NULL;
m_ArrowRight = NULL;
m_FleetTexture = NULL;
m_MyFont = NULL;
}
CTextures::~CTextures()
{
}
HRESULT CTextures::LoadTextures(IDirect3DDevice9* pd3dDevice)
{
	HRESULT hr;
	// MUISTA RELEASE !!!
	V_RETURN(LoadTransparentTexture(pd3dDevice,L"./gfx/BackGrnd.bmp",&m_BackGround));
	V_RETURN(LoadTransparentTexture(pd3dDevice,L"./gfx/StarText.bmp",&m_StarTexture));
	V_RETURN(LoadTransparentTexture(pd3dDevice,L"./gfx/StarText.jpg",&m_PlanetTexture));
	V_RETURN(LoadTransparentTexture(pd3dDevice,L"./gfx/miscbg.jpg",&m_MiscBG));
	V_RETURN(LoadTransparentTexture(pd3dDevice,L"./gfx/Button.bmp",&m_Button));
	V_RETURN(LoadTransparentTexture(pd3dDevice,L"./gfx/ArrowUp.bmp",&m_ArrowUp));
	V_RETURN(LoadTransparentTexture(pd3dDevice,L"./gfx/ArrowDown.bmp",&m_ArrowDown));
	V_RETURN(LoadTransparentTexture(pd3dDevice,L"./gfx/ArrowLeft.bmp",&m_ArrowLeft));
	V_RETURN(LoadTransparentTexture(pd3dDevice,L"./gfx/ArrowRight.bmp",&m_ArrowRight));
	V_RETURN(LoadTransparentTexture(pd3dDevice,L"./gfx/Fleet.bmp",&m_FleetTexture));
	V_RETURN(LoadTransparentTexture(pd3dDevice,L"./gfx/Myfont.bmp",&m_MyFont));
	return hr;
}
HRESULT CTextures::UnloadTextures()
{
	SAFE_RELEASE(m_MyFont);
	SAFE_RELEASE(m_FleetTexture);
	SAFE_RELEASE(m_ArrowRight);
	SAFE_RELEASE(m_ArrowLeft);
	SAFE_RELEASE(m_ArrowDown);
	SAFE_RELEASE(m_ArrowUp);
	SAFE_RELEASE(m_Button);
	SAFE_RELEASE(m_MiscBG);
	SAFE_RELEASE(m_PlanetTexture);
	SAFE_RELEASE(m_StarTexture);
	SAFE_RELEASE(m_BackGround);
	return S_OK;
}
HRESULT	CTextures::LoadTransparentTexture(IDirect3DDevice9* pd3dDevice,LPCWSTR pSrcFile,LPDIRECT3DTEXTURE9* ppTexture)
{
	HRESULT hr;
	V_RETURN(D3DXCreateTextureFromFileEx(pd3dDevice,pSrcFile,D3DX_DEFAULT,D3DX_DEFAULT,1,0,D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_ARGB(255,0,255,0),NULL,NULL,ppTexture));
	return hr;
}
