#ifndef CHANNELS_H
#define CHANNELS_H
#include "Tool.h"
#include "PixelBuffer.h"
#include <iostream>
using std::cout;
using std::endl;

class Channels : public Tool{
public:
	Channels(int size);
	~Channels();

	void applyChannels(PixelBuffer * canvas, float r, float g, float b);
	virtual void applyToolOnCanvas(PixelBuffer* canvas){cout<<"wrong call"<<endl;};
};
#endif