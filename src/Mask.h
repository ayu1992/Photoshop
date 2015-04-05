//
// Mask.h
//
// Defines a 2D mask

#ifndef MASK_H
#define MASK_H
#include <vector>

class Mask{

public:

	Mask(int width, int height, const std::vector<std::vector<float> >& maskValue);
	//Getters
	int getWidth();
	int getHeight();
	const std::vector<std::vector<float> >& getMask();	
	float getValue(int x, int y);

private:
	
	int m_width;										// mask dimensions
	int m_height;
	std::vector<std::vector<float> > m_value;			// a 2D matrix that stores intensity values
};

#endif
