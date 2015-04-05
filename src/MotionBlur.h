#ifndef MOTIONBLUR_H
#define MOTIONBLUR_H
#include "ConvolutionTool.h"

class MotionBlur: public ConvolutionTool{

public:
	
	MotionBlur(int m_size);
	MotionBlur(int m_size, int direction);
	virtual ~MotionBlur();
	
};
#endif