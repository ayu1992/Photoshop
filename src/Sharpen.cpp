#include "Sharpen.h"
#include <iostream>
using std::vector;
using std::cout;
using std::endl;


Sharpen::Sharpen(int m_size){

	// Check if the requested tool size is valid.
	m_size = (m_size < 1) ? 1 : m_size;
	
	m_size = (m_size % 2 == 1) ? m_size : m_size + 1 ;

	//initialize its mask
	vector<vector<float> > mask_value;
	int depth = m_size/2, layer = 1, label = -1;
	float sum = 0.0;
	//initialize to -1
	for (int x = 0; x < m_size; x++){ 
		mask_value.push_back(vector<float>());
		for (int y = 0; y < m_size; y++){
			mask_value.back().push_back(label);
			sum += label;
		}
	}

	label += 3;
	while(layer < depth){
		for(int x = layer; x < m_size - layer; x++){
			for(int y = layer; y < m_size - layer; y++){
				sum += (label - mask_value[x][y]);
				mask_value[x][y] = label;
			}
		}
		layer += 1;
		label += 3;
	}	

    // assign value in the center
    sum += (label - mask_value[depth][depth]);
    mask_value[depth][depth] = label;

	// Normalize the kernel
	for (int x = 0; x < m_size; x++){
    	for (int y = 0; y < m_size; y++){
        	mask_value[x][y] /= sum;
		}
	}

	m_mask = new Mask(m_size,m_size,mask_value);	
}

/* the matrix mask_value will be freed by Tool's destructor */
Sharpen::~Sharpen(){}
