#ifndef QUANTIZE_H
#define QUANTIZE_H
#include "Tool.h"
#include "PixelBuffer.h"
#include <iostream>
using std::cout;
using std::endl;

class Quantize : public Tool
{
public:
	Quantize(int size);
	~Quantize();

	void applyQuantize(PixelBuffer * canvas, int bins);
	virtual void applyToolOnCanvas(PixelBuffer* canvas){cout<<"wrong call"<<endl;};
	/* data */
};

#endif