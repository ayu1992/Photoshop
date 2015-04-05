#ifndef DYNBLUR_H
#define DYNBLUR_H
#include "Tool.h"
#include "Mask.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <vector>
class DynBlur
{
public:
	DynBlur(int size);
	~DynBlur();

	void setSize(int size);
	virtual void setStartPoint(int x, int y);
	virtual void applyToolOnCanvas(PixelBuffer* canvas);

	/* data */
private:
	int m_size;
	int m_startPointx, m_startPointy;
	std::vector<Mask *> m_masks; 
};
#endif