#include "Highlighter.h"
#include "Mask.h"
#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

Highlighter::Highlighter(int mask_size){

	// Check if the requested tool size is valid.
	if(mask_size < 0 || mask_size > 2){
		cout << "Invalid tool size: " << mask_size << ",failed to create tool instance" << endl;
		return;
	}
	
	//initialize its mask
	initTool(mask_size);
}

/* the matrix mask_value will be freed by Tool's destructor */
Highlighter::~Highlighter(){}

void Highlighter::initTool(int m_size){
	
	int mask_width, mask_height;
	vector<vector<float> > mask_value;
	
	// set mask dimensions
	switch(m_size){
		case 0:
			mask_width = 5;
			mask_height = 15;
			break;
		case 1:
			mask_width = 10;
			mask_height = 30;
			break;
		case 2:
			mask_width = 20;
			mask_height = 60;
			break;
		default:
			break;
	}
	
	// set intensity value for every entry in mask
	for (int i = 0; i < mask_height; i++) {
		mask_value.push_back(vector<float>());
		for (int j = 0; j < mask_width; j++) {
			mask_value.back().push_back(0.1);
		}
	}
	m_mask = new Mask(mask_width,mask_height,mask_value);				
}
