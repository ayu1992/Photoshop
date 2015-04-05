#include "ConvolutionTool.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <iostream>
using std::cout;
using std::endl;

ConvolutionTool::ConvolutionTool(){
	// initialize 
	m_mask = NULL;
}

ConvolutionTool::~ConvolutionTool(){
	delete m_mask;	
}

// TODO: set luminance in this sucker
void ConvolutionTool::applyToolOnCanvas(PixelBuffer* pixel_buffer){

	// check if the tool mask is valid
	if(m_mask == NULL){
		cout << "mask is null" << endl;
		return;
	}

	int width = pixel_buffer->getWidth();
	int height = pixel_buffer->getHeight();
	int mw = m_mask->getWidth();
	int mh = m_mask->getHeight();
	
	int posx,posy;
	ColorData tmp;
	PixelBuffer tmpPb(width,height, ColorData(0.0,0.0,0.0));

	for(int x = 0; x < width; x++){
	    for(int y = 0; y < height; y++){ 
	       
	        tmp = ColorData(0.0,0.0,0.0);
	        //multiply every value of the filter with corresponding image pixel 
	        for(int mx = 0; mx < mw; mx++){
		        for(int my = 0; my < mh; my++){ 
		            posx = (x - mw / 2 + mx); 
		            posy = (y - mh / 2 + my);
		            if(posx < 0 || posy < 0 || posx >= width || posy >= height)	continue;
		            tmp = tmp + (pixel_buffer->getPixel(posx,posy) * m_mask->getValue(mx,my));
		        	
		        } 
		    }  
	        tmpPb.setPixel(x,y,tmp.clampedColor());
	    }
	}    
	PixelBuffer::copyPixelBuffer(&tmpPb,pixel_buffer);
}