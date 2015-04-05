#include "MaskBasedTool.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <iostream>
using std::cout;
using std::endl;

MaskBasedTool::MaskBasedTool(){

	// initialize 
	m_curSize = 0;
	m_mask = NULL;
}


MaskBasedTool::~MaskBasedTool(){
	delete m_mask;	
}

void MaskBasedTool::setStartPoint(int x, int y){
	m_startPoint_x = x;
	m_startPoint_y = y;
}

void MaskBasedTool::setCurrentColor(ColorData color_data){
	m_curColor = color_data;
}

void MaskBasedTool::applyToolOnCanvas(PixelBuffer* pixel_buffer){

	// check if the tool mask is valid
	if(m_mask == NULL){
		cout << "mask is null" << endl;
		return;
	}

	// apply mask values to pixel buffer, dot product wise
	for(int i = 0; i < m_mask->getWidth(); i++){
		for(int j = 0; j < m_mask->getHeight(); j++){

			// x,y coordinates of current pixel 
			int cur_x = m_startPoint_x + i - m_mask->getWidth() / 2;	
			int cur_y = m_startPoint_y + j - m_mask->getHeight() / 2;	
			
			// if this position is out of bounds, don't apply mask
			if(cur_x < 0 || cur_y < 0 || cur_x >= pixel_buffer->getWidth() || cur_y >= pixel_buffer->getHeight()){
				continue;
			}

			// get current pixel value (i.e.: background content)
			ColorData bgColor = pixel_buffer->getPixel(cur_x,cur_y);

			// update pixel value using interpolation on old and new values
			pixel_buffer->setPixel(cur_x,cur_y,getColor(m_curColor,bgColor,m_mask->getMask()[i][j]));
		}
	}
}
ColorData MaskBasedTool::getColor(ColorData currentColor, ColorData bgColor,float mask_val){
	float intensity = mask_val * bgColor.getLuminance();	
	return currentColor * intensity + bgColor * (1-intensity);
}

