#ifndef TOOL_H
#define TOOL_H
#include "PixelBuffer.h"
#include "ColorData.h"
class Tool{

public:
	//virtual destructor
	Tool(){};
	virtual ~Tool(){};

	// for all tools
	virtual void applyToolOnCanvas(PixelBuffer* canvas) = 0;
	
	// additional interface for mask based tools
	virtual void setStartPoint(int x, int y){};
	virtual void setCurrentColor(ColorData color){};

};
#endif