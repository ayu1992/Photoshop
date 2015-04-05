#include "Channels.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <iostream>
using std::cout;
using std::endl;

Channels::Channels(int size){};
Channels::~Channels(){};

void Channels::applyChannels(PixelBuffer * canvas, float r, float g, float b){

	for(int x = 0; x < canvas->getWidth(); x++){
		for(int y = 0; y < canvas->getHeight(); y++){
			ColorData c = canvas->getPixel(x,y);
			c.setRed(c.getRed() * r);
			c.setGreen(c.getGreen() * g);
			c.setBlue(c.getBlue() * b);
			canvas->setPixel(x,y,c.clampedColor());
		}
	}
}