#include "SprayCan.h"
#include "Mask.h"
#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

SprayCan::SprayCan(int mask_size){

	// Check if the requested tool size is valid.
	if(mask_size < 0 || mask_size > 2){
		cout << "Invalid tool size: " << mask_size << ",failed to create tool instance" << endl;
		return;
	}
	
	//initialize its mask
	initTool(mask_size);
}

/* the matrix mask_value will be freed by Tool's destructor */
SprayCan::~SprayCan(){}

void SprayCan::initTool(int m_size){

	vector<vector<float> > mask_value;
	int mask_width, mask_height;
	
	// set mask dimensions
	switch(m_size){
		case 0:
			mask_width = 41;
			mask_height = 41;
			break;
		case 1:
			mask_width = 61;
			mask_height = 61;
			break;
		case 2:
			mask_width = 121;
			mask_height = 121;
			break;
		default:
			break;
	}
	
	// set intensity value for every entry in mask
	float val = 0.0;
	for (int i = 0; i < mask_height; i++) {
		mask_value.push_back(vector<float>());
		int center = (mask_width-1)/2;
		for (int j = 0; j < mask_width; j++) {
			int dist = (i - center) * (i - center) + (j - center) * (j - center);
			if (dist == 0) { 
			val = 0.2;
			} else if (dist < (mask_height * 3)) {
			  val = 0.15;
			} else if (dist < (mask_height * 5)) {
			  val = 0.10;
			} else if (dist < (mask_height * 7)) {
			  val = 0.05;
			} else if (dist < (mask_height * 10)) {
			  val = 0.01;
			}
			else{
				val = 0.0;
			}
			mask_value.back().push_back(val);
		}
	}
	m_mask = new Mask(mask_width,mask_height,mask_value);		
}
