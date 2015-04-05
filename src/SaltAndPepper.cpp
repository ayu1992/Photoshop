#include "SaltAndPepper.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

using std::cout;
using std::endl;

SaltAndPepper::SaltAndPepper(int size){};
SaltAndPepper::~SaltAndPepper(){};
void SaltAndPepper::applyToolOnCanvas(PixelBuffer* canvas){
	srand (time(NULL));

	for(int x = 0; x < canvas->getWidth(); x++){
		for(int y = 0; y < canvas->getHeight(); y++){
			int apply = (rand() % 10);
			if(apply < 0.2){
				float r = (float)(rand() % 10) / 10;		// r ranges from 0 ~ 1
				ColorData influence = ColorData(r,r,r);					
				canvas->setPixel(x,y, influence);	
			}	
		}
	}
}