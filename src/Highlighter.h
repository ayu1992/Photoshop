#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H
#include "MaskBasedTool.h"

class Highlighter : public MaskBasedTool{

public:
	
	Highlighter(int mask_size);
	virtual ~Highlighter();
	
private:

	void initTool(int m_size); // Initializes mask
};

#endif
