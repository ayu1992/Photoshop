#ifndef SPRAYCAN_H
#define SPRAYCAN_H
#include "MaskBasedTool.h"

class SprayCan : public MaskBasedTool{

public:
	
	SprayCan(int mask_size);
	virtual ~SprayCan();

private:
	
	void initTool(int m_size); // Initializes mask
};

#endif
