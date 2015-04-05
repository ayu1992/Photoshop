#include "Stamp.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

Stamp::Stamp(int size):m_stamp(NULL){

};
Stamp::~Stamp(){
	delete m_stamp;
};

void Stamp::setStamp(PixelBuffer* stamp){
	if(m_stamp)	delete m_stamp;
	m_stamp = stamp;
}
void Stamp::setStartPoint(int x, int y){
	m_startPointx = x;
	m_startPointy = y;
}
void Stamp::setCurrentColor(ColorData color){
	m_r = color.getRed();
	m_g = color.getGreen();
	m_b = color.getBlue();
}
void Stamp::applyToolOnCanvas(PixelBuffer * canvas){
	int c_width = canvas->getWidth();
	int c_height = canvas->getHeight();
	int s_width = m_stamp->getWidth();
	int s_height = m_stamp->getHeight();
	
	for(int i = 0; i < s_width; i++){
		for(int j = 0; j < s_height; j++){
			// position on canvas
			int cur_x = m_startPointx + i - s_width / 2;	
			int cur_y = m_startPointy + j - s_height / 2;

			if(cur_x < 0 || cur_y < 0 || cur_x >= canvas->getWidth() || cur_y >= canvas->getHeight()){
				continue;
			}

			ColorData c = m_stamp->getPixel(i,j);
			c.setRed(c.getRed() * m_r);
			c.setGreen(c.getGreen() * m_g);
			c.setBlue(c.getBlue() * m_b);
			canvas->setPixel(cur_x,cur_y,c);
		}
	}
}
