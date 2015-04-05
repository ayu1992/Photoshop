#ifndef STAMP_H
#define STAMP_H
#include "Tool.h"
#include "ColorData.h"
#include "PixelBuffer.h"

class Stamp : public Tool
{
public:
	Stamp(int size);
	~Stamp();

	void setStamp(PixelBuffer* stamp);
	virtual void setStartPoint(int x, int y);
	virtual void setCurrentColor(ColorData color);
	virtual void applyToolOnCanvas(PixelBuffer* canvas);

	/* data */
private:
	PixelBuffer* m_stamp;
	int m_startPointx;
	int m_startPointy;
	float m_r,m_g,m_b;
};
#endif