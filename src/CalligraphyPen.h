#ifndef CALLIGRAPHYPEN_H
#define CALLIGRAPHYPEN_H
#include "MaskBasedTool.h"		

class CalligraphyPen : public MaskBasedTool{

public:
	
	CalligraphyPen(int mask_size);
	virtual ~CalligraphyPen();

private:
	
	void initTool(int m_size);		// Initializes mask
};

#endif
