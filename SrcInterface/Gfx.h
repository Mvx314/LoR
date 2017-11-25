#pragma once
#include <vector>

class CTextGroup;

struct SIMPLEVERTEX 
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
	D3DXVECTOR2 tex;
};
enum GFXOBJTYPES 
{
	QUAD,
	TQUAD,  // textured quad
	TQUADA, // tq with alpha
	LINE
};
struct GFXOBJDATA 
{
	UINT vcount;
	UINT startvertex;
	GFXOBJTYPES type;
	IDirect3DTexture9 *texture;
	UINT animFrames;
	UINT currFrame;
};
#define D3DFVF_SIMPLEVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

class CGfx
{
public:
	static const UINT m_iMaxVertices = 10000;
//	UINT iNumVertices;
	SIMPLEVERTEX m_Vertices[m_iMaxVertices];
	std::vector<GFXOBJDATA> m_gfxObjData;
	std::vector<SIMPLEVERTEX> m_vertexData;
	std::vector<CTextGroup> m_textGroups;
public:
	CGfx();
//	UINT GetNumVertices() {return iNumVertices;};
//	void AddVertex(double,double,double,double,DWORD,double,double);
//	void ReplaceVertex(UINT,double,double,double,double,DWORD,double,double);
//	void MoveVertex(UINT,double,double,double,double);
	void MakeQuad(double ix,double iy,double wt,double ht,double dp,DWORD x1c,DWORD x2c,DWORD x3c,DWORD x4c,bool alpha,
					IDirect3DTexture9* quadTexture,UINT animFrames,UINT currFrame);
	void MakeQuadWPartialTexture(double ix,double iy,double wt,double ht,double dp,DWORD x1c,DWORD x2c,DWORD x3c,DWORD x4c,bool alpha,
					IDirect3DTexture9* quadTexture,double row,double col,double maxrow,double maxcol);
	void MakeLine(double x1,double y1,double x2,double y2,double dp,DWORD c1,DWORD c2);
	void MakeLine(POINT a,POINT b,double dp,DWORD c1,DWORD c2);
	void MakeSquare(double ix,double iy,double wt,double ht,double dp,DWORD c1,DWORD c2,DWORD c3,DWORD c4);
	ID3DXFont *GetFont(UINT p_index);
	void RenderText(UINT);
//	void RenderText(int);
	void PrepareVB();
	HRESULT Draw(IDirect3DDevice9*);
/*	void MakeStar(UINT,double,double);
	void MoveStar(UINT,double,double,double);
	void MoveStarTo(UINT,double,double,double);*/
};
