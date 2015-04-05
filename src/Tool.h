//
// Tool.h
//
// An Abstract class, provides interface for all tools

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
	
	// additional interface for tools that require startpoints
	virtual void setStartPoint(int x, int y){};
	virtual void setCurrentColor(ColorData color){};

};
#endif