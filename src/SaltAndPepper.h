#ifndef SALTANDPEPPER_H
#define SALTANDPEPPER_H
#include "Tool.h"
#include "PixelBuffer.h"
#include <iostream>

class SaltAndPepper : public Tool
{
public:
	SaltAndPepper(int size);
	~SaltAndPepper();
	virtual void applyToolOnCanvas(PixelBuffer* canvas);
	/* data */
};
#endif