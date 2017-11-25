#pragma once

class CTextures
{
public:
	IDirect3DTexture9 *m_BackGround;
	IDirect3DTexture9 *m_StarTexture;
	IDirect3DTexture9 *m_PlanetTexture;
	IDirect3DTexture9 *m_MiscBG;
	IDirect3DTexture9 *m_Button;
	IDirect3DTexture9 *m_ArrowUp;
	IDirect3DTexture9 *m_ArrowDown;
	IDirect3DTexture9 *m_ArrowLeft;
	IDirect3DTexture9 *m_ArrowRight;
	IDirect3DTexture9 *m_FleetTexture;
	IDirect3DTexture9 *m_MyFont;
public:
	CTextures();
	~CTextures();
	HRESULT LoadTextures(IDirect3DDevice9* pd3dDevice);
	HRESULT UnloadTextures();
private:
	HRESULT LoadTransparentTexture(IDirect3DDevice9* pd3dDevice,LPCWSTR pSrcFile,LPDIRECT3DTEXTURE9* ppTexture); // Transparent
};
