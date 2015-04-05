#ifndef SATURATE_H
#define SATURATE_H
#include "Tool.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include <iostream>
using std::cout;
using std::endl;

class Saturate : public Tool{
public:
	Saturate(int size);
	~Saturate();

	void applySaturate(PixelBuffer* canvas, float level);
	virtual void applyToolOnCanvas(PixelBuffer* canvas){cout<<"wrong call"<<endl;};

};
#endif