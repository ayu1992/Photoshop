#include "Eraser.h"
#include "Mask.h"
#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

Eraser::Eraser(int mask_size){

	// Check if the requested tool size is valid.
	if(mask_size < 0 || mask_size > 2){
		cout << "Invalid tool size: " << mask_size << ",failed to create tool instance" << endl;
		return;
	}

	//initialize its mask
	initTool(mask_size);
}

/* The matrix mask_value will be freed by Tool's destructor */
Eraser::~Eraser(){}

/*Initalize a tool's mask according to requested size*/
void Eraser::initTool(int m_size){

	int mask_width, mask_height;
	vector<vector<float> > mask_value;
	
	// set mask dimensions
	switch(m_size){
		case 0:
			mask_width = 21;
			mask_height = 21;
			break;
		case 1:
			mask_width = 41;
			mask_height = 41;
			break;
		case 2:
			mask_width = 81;
			mask_height = 81;
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
ColorData Eraser::getColor(ColorData currentColor, ColorData bgColor,float mask_val){
	return ColorData(1.0,1.0,1.0);
}
