//
// ConvolutionTool.h
//
// Provides interface and default convolution implementation for convolution based tools

#ifndef CONVOLUTIONTOOL_H
#define CONVOLUTIONTOOL_H
#include "Tool.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include "Mask.h"

class ConvolutionTool : public Tool{

public:

	ConvolutionTool();
	virtual ~ConvolutionTool();		
	
	// provides default convolution implementation 
	virtual void applyToolOnCanvas(PixelBuffer* canvas);
	
	protected:
		// stores a predefined mask
		Mask* m_mask;
};

#endif

