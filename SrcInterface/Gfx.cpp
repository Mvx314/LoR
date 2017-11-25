#include "dxstdafx.h"
#include "../SrcGame/Global.h"
#include "../SrcInterface/Gfx.h"

CGfx::CGfx()
{
}
void CGfx::MakeQuad(double ix,double iy,double wt,double ht,double dp,
					DWORD x1c,DWORD x2c,DWORD x3c,DWORD x4c,bool alpha,
					IDirect3DTexture9* quadTexture,UINT animFrames,UINT currFrame)
{
	D3DXVECTOR4 x1((float)ix,		(float)iy,		(float)dp,1.0f);
	D3DXVECTOR4 x2((float)(ix+wt),	(float)iy,		(float)dp,1.0f);
	D3DXVECTOR4 x3((float)ix,		(float)(iy+ht),	(float)dp,1.0f);
	D3DXVECTOR4 x4((float)(ix+wt),	(float)(iy+ht),	(float)dp,1.0f);

	SIMPLEVERTEX v1 = { x1,x1c,D3DXVECTOR2(currFrame*1.0f/(float)animFrames,0.0f)};
	SIMPLEVERTEX v2 = { x2,x2c,D3DXVECTOR2((currFrame+1)*1.0f/(float)animFrames,0.0f)};
	SIMPLEVERTEX v3 = { x3,x3c,D3DXVECTOR2(currFrame*1.0f/(float)animFrames,1.0f)};
	SIMPLEVERTEX v4 = { x4,x4c,D3DXVECTOR2((currFrame+1)*1.0f/(float)animFrames,1.0f)};

	m_vertexData.push_back(v1);
	m_vertexData.push_back(v2);
	m_vertexData.push_back(v3);
	m_vertexData.push_back(v4);

	GFXOBJDATA datablock = {4,(UINT)m_vertexData.size()-4,alpha ? TQUADA : TQUAD,quadTexture,animFrames,0};
	m_gfxObjData.push_back(datablock);
}
void CGfx::MakeQuadWPartialTexture(double ix,double iy,double wt,double ht,double dp,DWORD x1c,DWORD x2c,DWORD x3c,DWORD x4c,bool alpha,
					IDirect3DTexture9* quadTexture,double row,double col,double maxrow,double maxcol)
{
	D3DXVECTOR4 x1((float)ix,		(float)iy,		(float)dp,1.0f);
	D3DXVECTOR4 x2((float)(ix+wt),	(float)iy,		(float)dp,1.0f);
	D3DXVECTOR4 x3((float)ix,		(float)(iy+ht),	(float)dp,1.0f);
	D3DXVECTOR4 x4((float)(ix+wt),	(float)(iy+ht),	(float)dp,1.0f);

	SIMPLEVERTEX v1 = { x1,x1c,D3DXVECTOR2((float)(col*1.0f/maxcol),(float)(row*1.0f/maxrow))};
	SIMPLEVERTEX v2 = { x2,x2c,D3DXVECTOR2((float)((col+1)*1.0f/maxcol),(float)(row*1.0f/maxrow))};
	SIMPLEVERTEX v3 = { x3,x3c,D3DXVECTOR2((float)(col*1.0f/maxcol),(float)((row+1)*1.0f/maxrow))};
	SIMPLEVERTEX v4 = { x4,x4c,D3DXVECTOR2((float)((col+1)*1.0f/maxcol),(float)((row+1)*1.0f/maxrow))};

	m_vertexData.push_back(v1);
	m_vertexData.push_back(v2);
	m_vertexData.push_back(v3);
	m_vertexData.push_back(v4);

	GFXOBJDATA datablock = {4,(UINT)m_vertexData.size()-4,alpha ? TQUADA : TQUAD,quadTexture,1,0};
	m_gfxObjData.push_back(datablock);
}
void CGfx::MakeLine(double x1,double y1,double x2,double y2,double dp,DWORD c1,DWORD c2)
{
	D3DXVECTOR4 x1a((float)x1,(float)y1,(float)dp,1.0f);
	D3DXVECTOR4 x2a((float)x2,(float)y2,(float)dp,1.0f);

	SIMPLEVERTEX v1 = { x1a,c1,D3DXVECTOR2(0.0f,0.0f)};
	SIMPLEVERTEX v2 = { x2a,c2,D3DXVECTOR2(0.0f,0.0f)};

	m_vertexData.push_back(v1);
	m_vertexData.push_back(v2);

	GFXOBJDATA datablock = {2,(UINT)m_vertexData.size()-2,LINE,NULL,0,0};
	m_gfxObjData.push_back(datablock);
}
void CGfx::MakeLine(POINT a,POINT b,double dp,DWORD c1,DWORD c2)
{
	MakeLine(a.x,a.y,b.x,b.y,dp,c1,c2);
}
void CGfx::MakeSquare(double ix,double iy,double wt,double ht,double dp,DWORD c1,DWORD c2,DWORD c3,DWORD c4)
{
	MakeLine(ix,	iy,		ix+wt,	iy,		dp,c1,c2);
	MakeLine(ix+wt,	iy,		ix+wt,	iy+ht,	dp,c2,c3);
	MakeLine(ix+wt,	iy+ht,	ix,		iy+ht,	dp,c3,c4);
	MakeLine(ix,	iy+ht,	ix,		iy,		dp,c4,c1);
}
ID3DXFont *CGfx::GetFont(UINT p_index)
{
	if(p_index < g_Global.m_pFonts.size()-1)
		return g_Global.m_pFonts[p_index];
	else
		return g_Global.m_pFonts.back();
}
void CGfx::RenderText(UINT p_depth)
{
	int l_row = 0;
	int l_col = 0;
	for (std::vector<CTextGroup>::iterator it = m_textGroups.begin();it != m_textGroups.end();++it)
	{
		int l_line = 0;
		for (std::vector<std::string>::iterator itl = it->m_lines.begin();itl != it->m_lines.end();++itl,++l_line)
		{
			int l_char = 0;
			for(std::string::iterator itls = itl->begin();itls != itl->end();++itls,++l_char)
			{
				UINT l_letter = ((*itls) < 0) ? (*itls)+256 : (*itls);
				if(isalpha(l_letter) && isupper(l_letter))
				{
					l_row = 0;
					l_col = (*itls)-'A';
				}
				else if(isalpha(l_letter) && islower(l_letter))
				{
					l_row = 1;
					l_col = (*itls)-'a';
				}
				else if(isalnum(l_letter))
				{
					l_row = 0;
					l_col = 'Z'-'A'+3+(*itls)-'0';
				}
				else switch(l_letter)
				{
				case 'Å':
					l_row = 0;
					l_col = 'Z'-'A';
					break;
				case 'Ä':
					l_row = 0;
					l_col = 'Z'-'A'+1;
					break;
				case 'Ö':
					l_row = 0;
					l_col = 'Z'-'A'+2;
					break;
				case 'å':
					l_row = 1;
					l_col = 'Z'-'A';
					break;
				case 'ä':
					l_row = 1;
					l_col = 'Z'-'A'+1;
					break;
				case 'ö':
					l_row = 1;
					l_col = 'Z'-'A'+2;
					break;
				case '.':
					l_row = 0;
					l_col = 'Z'-'A'+3+10;
					break;
				case ',':
					l_row = 0;
					l_col = 'Z'-'A'+3+10+1;
					break;
				case ':':
					l_row = 0;
					l_col = 'Z'-'A'+3+10+2;
					break;
				case '\'':
					l_row = 0;
					l_col = 'Z'-'A'+3+10+3;
					break;
				case '!':
					l_row = 0;
					l_col = 'Z'-'A'+3+10+4;
					break;
				case '?':
					l_row = 0;
					l_col = 'Z'-'A'+3+10+5;
					break;
				default:
					l_row = 1;
					l_col = 49;
					break;
				}
				MakeQuadWPartialTexture(l_char*8+it->m_position.x,l_line*12+it->m_position.y,24,40,it->m_depth,it->m_color,it->m_color,it->m_color,it->m_color,false,g_Textures.m_MyFont,l_row,l_col,2,50);
			}
		}
	}

/*	for (std::vector<CTextGroup>::iterator it = m_textGroups.begin();it != m_textGroups.end();++it)
	{
		if (it->m_depth != depth)
			continue;
		CDXUTTextHelper txtHelper(it->m_font,g_pTextSprite,1);
		txtHelper.Begin();
		txtHelper.SetForegroundColor(it->m_color);
		int j=0;
		for (std::vector<std::string>::iterator itl = it->m_lines.begin();itl != it->m_lines.end();++itl,++j)
		{
			txtHelper.SetInsertionPos(it->m_position.x,it->m_position.y+11*j);
			txtHelper.DrawFormattedTextLine(L"%S",itl->c_str());
		}
		txtHelper.End();
	}*/
}
void CGfx::PrepareVB()
{
	int j = 0;
	for(std::vector<SIMPLEVERTEX>::iterator it = m_vertexData.begin();it != m_vertexData.end();++it)
	{
// TODO
		if(j<m_iMaxVertices)
			m_Vertices[j++] = *it;
		else
			g_Global.LogInfo("Too many vertices!");
	}
	m_vertexData.clear();
}
HRESULT CGfx::Draw(IDirect3DDevice9* pd3dDevice)
{
	HRESULT hr;
    // Clear the render target and the zbuffer 
    V( pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0) );
	// Render the scene
	if( SUCCEEDED( pd3dDevice->BeginScene() ) )
	{
		pd3dDevice->SetFVF( D3DFVF_SIMPLEVERTEX );
		pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(SIMPLEVERTEX) );
		g_Gfx.RenderText(0);
		for(std::vector<GFXOBJDATA>::iterator it = m_gfxObjData.begin();it<m_gfxObjData.end();++it)
		{
			switch(it->type)
			{
			case TQUAD :
				pd3dDevice->SetTexture( 0, it->texture);
				pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
				pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
				pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
				pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,it->startvertex,2);
				break;
			case TQUADA :
				pd3dDevice->SetTexture( 0, it->texture);
				pd3dDevice->SetRenderState( D3DRS_ALPHAREF, (DWORD)0x00000001);
				pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );
				pd3dDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
//					pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
//					pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
//					pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
//					pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
				pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,it->startvertex,2);
//					pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
				break;
			case QUAD :
				pd3dDevice->SetTexture( 0, NULL);
				pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
				pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
				pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
				pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,it->startvertex,2);
				break;
			case LINE :
				pd3dDevice->SetTexture( 0, NULL);
				pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
				pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
				pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
				pd3dDevice->DrawPrimitive( D3DPT_LINESTRIP,it->startvertex,1);
				break;
			default:
				break;

			}
		}
//		g_Gfx.RenderText(1);
		g_Gfx.m_textGroups.clear();
		V( pd3dDevice->EndScene() );
		m_gfxObjData.clear();
	}
	return hr;
}

/*void CGfx::AddVertex(double x,double y,double z,double w,DWORD col,double texx,double texy)
{
	if (iNumVertices < iMaxVertices)
	{
		Vertices[iNumVertices].position = D3DXVECTOR4(x,y,z,w);
		Vertices[iNumVertices].color = col;
		Vertices[iNumVertices].tex = D3DXVECTOR2(texx,texy);
		++iNumVertices;
	}
}
void CGfx::ReplaceVertex(UINT index,double x,double y,double z,double w,DWORD col,double texx,double texy)
{
	if (index >= 0 && index < iMaxVertices)
	{
		Vertices[index].position = D3DXVECTOR4(x,y,z,w);
		Vertices[index].color = col;
		Vertices[iNumVertices].tex = D3DXVECTOR2(texx,texy);
	}
}
void CGfx::MoveVertex(UINT index,double x,double y,double z,double w)
{
	if (index >= 0 && index < iMaxVertices)
	{
		Vertices[index].position += D3DXVECTOR4(x,y,z,w);
	}
}*/
/*
void CGfx::MakeStar(UINT index, double x, double y)
{
	if (index < iMaxVertices/4)
	{
		Vertices[4*index+0].position = D3DXVECTOR4(x, y, 0.5f, 1.0f);
		Vertices[4*index+0].color = 0xffffff00;
		Vertices[4*index+0].tex = D3DXVECTOR2(0,0);
		Vertices[4*index+1].position = D3DXVECTOR4(x+25.0f, y-25.0f, 0.5f, 1.0f);
		Vertices[4*index+1].color = 0xffff00ff;
		Vertices[4*index+1].tex = D3DXVECTOR2(1,0);
		Vertices[4*index+2].position = D3DXVECTOR4(x+25.0f, y+25.0f, 0.5f, 1.0f);
		Vertices[4*index+2].color = 0xff00ffff;
		Vertices[4*index+2].tex = D3DXVECTOR2(0,1);
		Vertices[4*index+3].position = D3DXVECTOR4(x+50.0f, y, 0.5f, 1.0f);
		Vertices[4*index+3].color = 0xff00ff00;
		Vertices[4*index+3].tex = D3DXVECTOR2(1,1);
	}
}
void CGfx::MoveStar(UINT index, double ix, double iy, double iz)
{
	if (index < iMaxVertices/4)
	{
		Vertices[4*index+0].position += D3DXVECTOR4(ix, iy, iz, 1.0f);
		Vertices[4*index+1].position += D3DXVECTOR4(ix, iy, iz/2, 1.0f);
		Vertices[4*index+2].position += D3DXVECTOR4(ix, iy, iz/3, 1.0f);
		Vertices[4*index+3].position += D3DXVECTOR4(ix, iy, iz/4, 1.0f);
	}
}
void CGfx::MoveStarTo(UINT index, double ix, double iy, double iz)
{
	MakeStar(index,ix,iy);
}
*/
