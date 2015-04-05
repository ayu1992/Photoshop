#include "Stamp.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include <iostream>
#include <vector>
#include <cmath>
using std::cout;
using std::endl;

DynBlur::DynBlur(int size){
	int size;
	float val = 0;		
	float sigma = 20;
	float mean, sum;
	m_mask = NULL;
	for(size = 1; size <= 11; size+=2){
		//initialize its mask
		vector<vector<float> > mask_value;
		mean = size/2;
		sum = 0.0;

		for (int x = 0; x < size; x++){ 
			mask_value.push_back(vector<float>());
	    	for (int y = 0; y < size; y++){
	    		val =  exp( -0.5 * (pow((x-mean)/sigma, 2.0) + pow((y-mean)/sigma,2.0)))/ (2 * M_PI * sigma * sigma);
	    		mask_value.back().push_back(val);
	        // Accumulate the kernel values
	        sum += val;
	   		 }
		}
		// Normalize the kernel
		for (int x = 0; x < size; x++){
	    	for (int y = 0; y < size; y++){
	        	mask_value[x][y] /= sum;
			}
		}
		m_mask.push_back(Mask(m_size,m_size,mask_value));
	}
};
DynBlur::~DynBlur(){
	for (int i = 0; i < m_mask.size(); i++) {
  		for (std::vector<Mask *>::iterator it = m_mask[i].begin(); it != m_mask[i].end(); ++it) delete *it;
	}
};

void DynBlur::setSize(int size){	// input 6 -> m_size = 7, index = 4 = m_size/2 + 1
	size = (size % 2 == 1) ? size : size + 1 ;
	m_size = size;
}
void DynBlur::setStartPoint(int x, int y){
	m_startPointx = x;
	m_startPointy = y;
}
void DynBlur::applyToolOnCanvas(PixelBuffer* canvas){
	int maskIndex = m_size / 2 + 1;			// which mask
	int width;
	int height;
	
	int posx,posy;
	ColorData tmp;
	PixelBuffer tmpPb(width,height, ColorData(0.0,0.0,0.0));
	
	for(maskIndex; maskIndex >= 0; maskIndex--){
		mask = m_mask[mask_Index];
		width = mask->getWidth();
		height = mask->getHeight();
		// convolution about m_startPointx, m_startPointy
		for(int x = 0; x < width; x++){
	    	for(int y = 0; y < height; y++){ 
	       
	        tmp = ColorData(0.0,0.0,0.0);
	        //multiply every value of the filter with corresponding image pixel 
	        for(int mx = 0; mx < width; mx++){
		        for(int my = 0; my < height; my++){ 
		            posx = (x - width / 2 + mx); 
		            posy = (y - height / 2 + my);
		            if(posx < 0 || posy < 0 || posx >= width || posy >= height)	continue;
		            tmp = tmp + (canvas->getPixel(posx,posy) * mask->getValue(mx,my));
		        } 
		    }  
	        canvas.setPixel((x - width / 2 + m_startPointx),(y - height / 2 + m_startPointy),tmp.clampedColor());
	    }
	}		
	}
    
}