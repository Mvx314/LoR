#pragma once

#include <vector>
//class CGfx;

class CTextGroup
{
private:
	UINT m_depth;
	POINT m_position;
	DWORD m_color;
	ID3DXFont *m_font;
	std::vector<std::string> m_lines;
public:
	CTextGroup();
	CTextGroup(UINT p_depth,POINT p_pos,DWORD p_color,ID3DXFont *p_font);
	CTextGroup(UINT p_depth,UINT p_x,UINT p_y,DWORD p_color,ID3DXFont *p_font);
	void SingleLine(const std::string &p_line);
	void SetDepth(UINT p_depth);
	void SetPosition(POINT p_pos);
	void SetColor(DWORD p_color);
	void SetFont(ID3DXFont *p_font);
	void AddLine(const std::string &p_line);
	UINT LineCount();
	void Clear();
	friend class CGfx;
};
