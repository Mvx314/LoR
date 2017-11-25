#pragma once
#include "../SrcInterface/TextGroup.h"

class CTextGroup;

class CToolTip
{
private:
	CTextGroup m_data;
public:
	CToolTip();
	~CToolTip();
	void AddLine(const std::string &p_line);
	void Draw();
};
