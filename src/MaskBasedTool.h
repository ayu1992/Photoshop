#ifndef MASKEDBASEDTOOL_H
#define MASKEDBASEDTOOL_H
#include "Tool.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include "Mask.h"
#include <vector>

class MaskBasedTool : public Tool{

// provides a default implementation for applyToolOnCanvas

public:

	MaskBasedTool();
	virtual ~MaskBasedTool();		
	
	// family function (override)
	virtual void setStartPoint(int x, int y);			// Set start point of this tool to be (x, y).
	virtual void setCurrentColor(ColorData color_data);	// Set color of m_curTool to be colordata

	virtual void applyToolOnCanvas(PixelBuffer* canvas);
	

	

protected:					// Accessible to subclass

	int m_startPoint_x;
	int m_startPoint_y;
	
	int m_curSize;		    // current tool size
	ColorData m_curColor;	// current tool color
	
	Mask* m_mask;
	
	virtual ColorData getColor(ColorData currentColor, ColorData bgColor,float mask_val);	// Returns computed color
};

#endif
