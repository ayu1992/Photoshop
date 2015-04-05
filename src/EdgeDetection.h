#ifndef EDGE_DETECTION_H
#define EDGE_DETECTION_H
#include "ConvolutionTool.h"

class EdgeDetection: public ConvolutionTool{

public:
	
	EdgeDetection(int size);
	virtual ~EdgeDetection();
	
};
#endif