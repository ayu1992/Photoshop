#ifndef DYNBLUR_H
#define DYNBLUR_H
#include "Tool.h"
#include "Mask.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <vector>
class DynBlur : public Tool
{
public:
	DynBlur(int size);
	~DynBlur();

	virtual void setStartPoint(int x, int y);
	virtual void applyToolOnCanvas(PixelBuffer* canvas);

	/* data */
private:
	int m_window_size;
	int m_startPointx, m_startPointy;
	Mask * m_mask; 	// a 3x3 mask
};
#endif