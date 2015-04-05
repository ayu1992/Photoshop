#include "EdgeDetection.h"
#include <iostream>
#include <cmath>
using std::vector;
using std::cout;
using std::endl;

EdgeDetection::EdgeDetection(int size){

	vector<vector<float> > mask_value;
	int m_size = 3;

	for (int x = 0; x < m_size; x++){ 
			mask_value.push_back(vector<float>());
			for (int y = 0; y < m_size; y++){
				mask_value.back().push_back(-1);
			}
	}

	mask_value[m_size/2][m_size/2] = 8;

	m_mask = new Mask(m_size,m_size,mask_value);
}
EdgeDetection::~EdgeDetection(){};