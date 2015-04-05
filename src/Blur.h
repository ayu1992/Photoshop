#ifndef BLUR_H
#define BLUR_H
#include "ConvolutionTool.h"

class Blur: public ConvolutionTool{

public:
	
	Blur(int m_size);
	virtual ~Blur();
	
};
#endif