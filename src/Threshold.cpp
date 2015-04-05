#include "Threshold.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <iostream>
using std::cout;
using std::endl;

Threshold::Threshold(int size){};
Threshold::~Threshold(){};

void Threshold::applyThreshold(PixelBuffer * canvas, float th){
	for(int x = 0; x < canvas->getWidth(); x++){
		for(int y = 0; y < canvas->getHeight(); y++){
			ColorData c = canvas->getPixel(x,y);
			c.setRed(c.getRed() > th ? 1 : 0);
			c.setGreen(c.getGreen() > th ? 1 : 0);
			c.setBlue(c.getBlue() > th ? 1 : 0);
			c.setAlpha(c.getAlpha() > th? 1 : 0);
			canvas->setPixel(x,y,c);
		}
	}
}