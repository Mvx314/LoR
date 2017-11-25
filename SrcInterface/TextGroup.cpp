#include "dxstdafx.h"
#include "../SrcInterface/TextGroup.h"

CTextGroup::CTextGroup()
{
}
CTextGroup::CTextGroup(UINT p_depth,POINT p_pos,DWORD p_color,ID3DXFont *p_font) :
	m_depth (p_depth),
	m_position (p_pos),
	m_color (p_color),
	m_font (p_font)
{
}
CTextGroup::CTextGroup(UINT p_depth,UINT p_x,UINT p_y,DWORD p_color,ID3DXFont *p_font) :
	m_depth (p_depth),
	m_color (p_color),
	m_font (p_font)
{
	m_position.x = p_x;
	m_position.y = p_y;
}
void CTextGroup::SingleLine(const std::string& p_line)
{
	m_depth = 0;
	m_position.x = 1;
	m_position.y = 1;
	m_color = 0xffffffff;
	m_lines.push_back(p_line);
}
void CTextGroup::SetDepth(UINT p_depth)
{
	m_depth = p_depth;
}
void CTextGroup::SetPosition(POINT p_pos)
{
	m_position = p_pos;
}
void CTextGroup::SetColor(DWORD p_color)
{
	m_color = p_color;
}
void CTextGroup::SetFont(ID3DXFont *p_font)
{
	m_font = p_font;
}
void CTextGroup::AddLine(const std::string& p_line)
{
	m_lines.push_back(p_line);
}
UINT CTextGroup::LineCount()
{
	return (UINT)m_lines.size();
}
void CTextGroup::Clear()
{
	m_depth = 0;
	m_position.x = -1;
	m_position.y = -1;
	m_color = 0x00000000;
	m_font = NULL;
	m_lines.clear();
}
