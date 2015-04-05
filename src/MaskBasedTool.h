//
// MaskedBasedTool.h
//
// Provides interface and default dot-product implementation for mask based tools

#ifndef MASKEDBASEDTOOL_H
#define MASKEDBASEDTOOL_H
#include "Tool.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include "Mask.h"
#include <vector>

class MaskBasedTool : public Tool{

public:

	MaskBasedTool();
	virtual ~MaskBasedTool();		
	
	// override functions from Tool.h
	virtual void setStartPoint(int x, int y);			// Set start point of this tool to be (x, y).
	virtual void setCurrentColor(ColorData color_data);	// Set color of m_curTool to be colordata

	// provides default dot-product implementation 
	virtual void applyToolOnCanvas(PixelBuffer* canvas);
	
protected:					// Accessible to subclass

	int m_startPoint_x;		// start points
	int m_startPoint_y;
	
	int m_curSize;		    // current tool size
	ColorData m_curColor;	// current tool color
	
	Mask* m_mask;			// stores a 2D predefined mask

	// Helper function to calculate pixel values
	virtual ColorData getColor(ColorData currentColor, ColorData bgColor,float mask_val);	// Returns computed color
};

#endif
