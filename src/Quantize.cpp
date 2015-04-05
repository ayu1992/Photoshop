#include "Quantize.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include <iostream>
#include <cmath>
using std::cout;
using std::endl;


Quantize::Quantize(int size){};
Quantize::~Quantize(){};

void Quantize::applyQuantize(PixelBuffer * canvas, int bins){
	float values = 1.0 / (bins-1);

	for(int x = 0; x < canvas->getWidth(); x++){
		for(int y = 0; y < canvas->getHeight(); y++){
			ColorData c = canvas->getPixel(x,y);
			c.setRed( round(c.getRed() / values) * values );
			c.setGreen( round(c.getGreen() / values) * values);
			c.setBlue( round(c.getBlue() / values) * values);
			canvas->setPixel(x,y,c);
		}
	}
}