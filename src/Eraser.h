#ifndef ERASER_H
#define ERASER_H
#include "MaskBasedTool.h"

class Eraser : public MaskBasedTool{

public:
	
	Eraser(int mask_size);
	virtual ~Eraser();

private:
	
	void initTool(int m_size); // Initializes mask
	virtual ColorData getColor(ColorData currentColor, ColorData bgColor,float mask_val);
};

#endif
