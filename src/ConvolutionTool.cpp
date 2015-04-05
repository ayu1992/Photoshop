#include "ConvolutionTool.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <iostream>
using std::cerr;
using std::endl;

ConvolutionTool::ConvolutionTool():m_mask(NULL){}

ConvolutionTool::~ConvolutionTool(){
	delete m_mask;	
}

// Default implementation of 2D convolution
void ConvolutionTool::applyToolOnCanvas(PixelBuffer* pixel_buffer){

	// check if the tool mask is valid
	if(m_mask == NULL){
		cerr << "[ConvolutionTool] mask is null" << endl;
		return;
	}

	// Dimensions of the canvas and mask
	int width = pixel_buffer->getWidth();
	int height = pixel_buffer->getHeight();
	int mw = m_mask->getWidth();
	int mh = m_mask->getHeight();
	
	// Coordinates to access the canvas
	int posx,posy;

	// Declare variable to store intermediate results
	ColorData tmp;
	PixelBuffer tmpPb(width,height, ColorData(0.0,0.0,0.0));

	// 2D Convolution
	for(int x = 0; x < width; x++){
	    for(int y = 0; y < height; y++){ 
	       
	        tmp = ColorData(0.0,0.0,0.0);

	        // Multiply every value of the mask a corresponding image pixel 
	        for(int mx = 0; mx < mw; mx++){
		        for(int my = 0; my < mh; my++){ 
		            posx = (x - mw / 2 + mx); 
		            posy = (y - mh / 2 + my);

		            // If trying to access out of bounds indicies, skip
		            if(posx < 0 || posy < 0 || posx >= width || posy >= height)	continue;

		            // Accumulate values
		            tmp = tmp + (pixel_buffer->getPixel(posx,posy) * m_mask->getValue(mx,my));
		        } 
		    }  
	        tmpPb.setPixel(x,y,tmp.clampedColor());
	    }
	}    
	// Set result
	PixelBuffer::copyPixelBuffer(&tmpPb,pixel_buffer);
}