#ifndef SHARPEN_H
#define SHARPEN_H
#include "ConvolutionTool.h"

class Sharpen : public ConvolutionTool{

public:
	
	Sharpen(int m_size);
	virtual ~Sharpen();

};
#endif