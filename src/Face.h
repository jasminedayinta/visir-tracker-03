#pragma once

#include "types.h"

class CFace {
public:
	CFace(void) = default;
	~CFace(void) = default;

	// Setters
	// Getters
	
private:
	int 			m_id;
	std::string		m_text;
	Rect			m_area;
};

using ptr_face_t = std::shared_ptr<CFace>;
