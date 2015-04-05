#include "MotionBlur.h"
#include <iostream>
#include <cmath>
using std::vector;
using std::cout;
using std::endl;

	
MotionBlur::MotionBlur(int m_size){
	cout<<"[MotionBlur] Called wrong constructor" <<endl;
}
MotionBlur::MotionBlur(int m_size, int direction){
	m_size = (m_size < 1) ? 1 : m_size;
	
	m_size = (m_size % 2 == 1) ? m_size : m_size + 1 ;

	vector<vector<float> > mask_value;
	int factor = m_size;

	// TODO: better way to init 0?
	for (int x = 0; x < m_size; x++){ 
		mask_value.push_back(vector<float>());
		for (int y = 0; y < m_size; y++){
			mask_value.back().push_back(0);
		}
	}
	switch(direction){
		case 0:		// N/S
			for(int y = 0; y < m_size; y++){
				mask_value[m_size/2][y] = 1.0/factor;
			}
			break;
		case 1:		// 180 degrees
			for(int x = 0; x < m_size; x++){
				mask_value[x][m_size/2] = 1.0/factor;
			}
			break;
		case 2: 	// 135 degrees
			for(int x = 0; x < m_size; x++){ 
				mask_value[x][x] = 1.0/factor;
			}		
			break;
			break;
		case 3: 	// 45 degrees
			for(int x = m_size - 1; x >= 0; x--){
				mask_value[x][m_size - 1 - x] = 1.0/factor;
			}	
		default:	break;
	}
	m_mask = new Mask(m_size,m_size,mask_value);
}
MotionBlur::~MotionBlur(){};
