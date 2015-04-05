#ifndef PEN_H
#define PEN_H
#include "MaskBasedTool.h"

class Pen : public MaskBasedTool{

public:
	
	Pen(int mask_size);
	virtual ~Pen();

private:
	
	void initTool(int m_size);		// Initializes mask
};

#endif
