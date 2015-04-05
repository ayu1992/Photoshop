//
//  PixelBuffer.h
//
//  Created by CSCI3081W Guru
//  Copyright (c) 2015 CSCI3081W Guru. All rights reserved.
//

#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

class ColorData;

class PixelBuffer 
{
public:
	// Constructors
	PixelBuffer(int w, int h, ColorData backgroundColor);
	~PixelBuffer();
	// Setters
	void setDimensions(int w, int h);
	void setPixel(int x, int y, const ColorData& newPixel);
	// Getters
	ColorData getPixel(int x, int y) const;
	ColorData const * const getData() const;
	int getHeight() const;
	int getWidth() const;
	// Member tasks
	void fillPixelBufferWithColor(ColorData initialPixels);
	
	// Static tasks
	static void copyPixelBuffer(PixelBuffer * sourceBuffer, PixelBuffer * destinationBuffer);
	
	ColorData getBackgroundColor();
private:
	// Array of pixel values
	ColorData * m_pixels;
	ColorData * m_backgroundColor;
	// Dimensions
	int m_width;
	int m_height;
	int m_channels;
};

#endif
