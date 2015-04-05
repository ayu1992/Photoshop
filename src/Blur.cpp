#include "Blur.h"
#include <iostream>
#include <cmath>
using std::vector;
using std::cout;
using std::endl;

Blur::Blur(int m_size){

	// Check if the requested tool size is valid.
	m_size = (m_size < 1) ? 1 : m_size;
	
	// round m_size to nearest odd number
	m_size = (m_size % 2 == 1) ? m_size : m_size + 1 ;

	//initialize its mask
	vector<vector<float> > mask_value;

	// set intensity value for every entry in mask
	float val = 0;		
	float sigma = 20;
	float mean = m_size/2;
	float sum = 0.0; // For accumulating the kernel values

	for (int x = 0; x < m_size; x++){ 
		mask_value.push_back(vector<float>());
    	for (int y = 0; y < m_size; y++){
    		val =  exp( -0.5 * (pow((x-mean)/sigma, 2.0) + pow((y-mean)/sigma,2.0)))/ (2 * M_PI * sigma * sigma);
    		mask_value.back().push_back(val);
        // Accumulate the kernel values
        sum += val;
   		 }
	}
	// Normalize the kernel
	for (int x = 0; x < m_size; x++){
    	for (int y = 0; y < m_size; y++){
        	mask_value[x][y] /= sum;
		}
	}
	m_mask = new Mask(m_size,m_size,mask_value);

}
/* the matrix mask_value will be freed by Tool's destructor */
Blur::~Blur(){}



