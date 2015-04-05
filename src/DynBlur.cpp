#include "DynBlur.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include <iostream>
#include <vector>
#include <cmath>
using std::cout;
using std::endl;
using std::vector;
//size : 0,1,2
DynBlur::DynBlur(int size){

	m_window_size = size * 4 + 1;

	int mask_size = 3;
	float val = 0;		
	float sigma = 20;
	float mean, sum;
	//initialize its mask
	vector<vector<float> > mask_value;
	mean = mask_size/2;
	sum = 0.0;

	for (int x = 0; x < mask_size; x++){ 
		mask_value.push_back(vector<float>());
	    for (int y = 0; y < mask_size; y++){
	    	val =  exp( -0.5 * (pow((x-mean)/sigma, 2.0) + pow((y-mean)/sigma,2.0)))/ (2 * M_PI * sigma * sigma);
	    	mask_value.back().push_back(val);
	       // Accumulate the kernel values
	     	sum += val;
	   	}
	}
	// Normalize the kernel
	for (int x = 0; x < mask_size; x++){
	    for (int y = 0; y < mask_size; y++){
	        mask_value[x][y] /= sum;
		}
	}
	m_mask = new Mask(mask_size,mask_size,mask_value);
};
DynBlur::~DynBlur(){
	delete m_mask;
};

void DynBlur::setStartPoint(int x, int y){
	m_startPointx = x;
	m_startPointy = y;
}
void DynBlur::applyToolOnCanvas(PixelBuffer* canvas){
	int mask_width = m_mask->getWidth();;
	int mask_height = m_mask->getHeight();
	int posx,posy;
	ColorData tmp;
	
	while(m_window_size > 1){
		// convolution about m_startPointx, m_startPointy
		for(int x = m_startPointx - m_window_size / 2; x < m_startPointx + m_window_size/2 + 1; x++){
	    	for(int y = m_startPointy - m_window_size / 2; y < m_window_size + m_window_size/2 + 1; y++){ 
		        tmp = ColorData(0.0,0.0,0.0);
		        //multiply every value of the filter with corresponding image pixel 
		        for(int mx = 0; mx < mask_width; mx++){
			        for(int my = 0; my < mask_height; my++){ 
			            posx = (x - mask_width / 2 + mx); 
			            posy = (y - mask_height / 2 + my);
			            // indexing out of window
			            if(posx < m_startPointx - m_window_size / 2 || posy < m_startPointy - m_window_size / 2 || posx >= m_startPointx + m_window_size/2 || posy >= m_window_size + m_window_size/2 + 1)	continue;
			            tmp = tmp + (canvas->getPixel(posx,posy) * m_mask->getValue(mx,my));
			        } 
			    }  
	        	canvas->setPixel(x,y,tmp.clampedColor());
	    	}
	  	}	
	  	m_window_size-=2;	
	}
    
}