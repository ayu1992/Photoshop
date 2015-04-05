#include "Pen.h"
#include "Mask.h"
#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

Pen::Pen(int mask_size){

	// Check if the requested tool size is valid.
	if(mask_size < 0 || mask_size > 2){
		cout << "Invalid tool size: " << mask_size << ",failed to create tool instance" << endl;
		return;
	}
	
	//initialize its mask
	initTool(mask_size);
}

/* the matrix mask_value will be freed by Tool's destructor */
Pen::~Pen(){}

void Pen::initTool(int m_size){

	vector<vector<float> > mask_value;
	int mask_width, mask_height;

	// set mask dimensions
	switch(m_size){
		case 0:
			mask_width = 3;
			mask_height = 3;
			break;
		case 1:
			mask_width = 15;
			mask_height = 15;
			break;
		case 2:
			mask_width = 25;
			mask_height = 25;
			break;
		default:
			break;
	}
	
	// set intensity value for every entry in mask
	float val = 0;
	for (int i = 0; i < mask_height; i++) {
		mask_value.push_back(vector<float>());
		int center = (mask_width-1)/2;
		int n = (center+1)*(center+1);
		for (int j = 0; j < mask_width; j++) {
			int dist = (i - center) * (i - center) + (j - center) * (j - center);
			if (dist < 0.1*n) { 
			val = 1.0;
			} else{
			  val = 0.0;
			}
			mask_value.back().push_back(val);
		}
	}
	m_mask = new Mask(mask_width,mask_height,mask_value);						
}


