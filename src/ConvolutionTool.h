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
	
	// family function (override)
	virtual void applyToolOnCanvas(PixelBuffer* canvas);
	
	protected:
		Mask* m_mask;
};

#endif

