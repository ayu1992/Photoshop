#ifndef THRESHOLD_H
#define THRESHOLD_H
#include "Tool.h"
#include "PixelBuffer.h"
#include <iostream>
using std::cout;
using std::endl;

class Threshold : public Tool
{
public:
	Threshold(int size);
	~Threshold();

	void applyThreshold(PixelBuffer * canvas, float th);
	virtual void applyToolOnCanvas(PixelBuffer* canvas){cout<<"wrong call"<<endl;};
	/* data */
};
#endif