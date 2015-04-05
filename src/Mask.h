#ifndef MASK_H
#define MASK_H
#include <vector>

class Mask{

public:

	Mask(int width, int height, const std::vector<std::vector<float> >& maskValue);
	//Getters
	int getWidth();
	int getHeight();
	const std::vector<std::vector<float> >& getMask();	// const: immutable
	float getValue(int x, int y);

	//friend Mask operator- (const Mask& a, const Mask& b);
private:
	
	int m_width;
	int m_height;
	std::vector<std::vector<float> > m_value;			// a matrix that stores mask values
};

#endif
