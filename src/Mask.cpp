#include "Mask.h"

Mask::Mask(int width, int height, const std::vector<std::vector<float> >& maskValue)
    : m_width(width), m_height(height), m_value(maskValue) {}

int Mask::getWidth(){
	return m_width;
}
int Mask::getHeight(){
	return m_height;
}
float Mask::getValue(int x, int y){
	return m_value[x][y];
}
const std::vector<std::vector<float> >& Mask::getMask(){
	return m_value;
}
