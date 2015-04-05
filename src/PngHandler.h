//
// PngHandler.h
//
// Handles PNG file I/O

#ifndef PNGHANDLER_H
#define PNGHANDLER_H

#include <iostream>
#include "PixelBuffer.h"

class PngHandler{

public:

	PngHandler();
	~PngHandler();			

	// Read in a PNG file
	PixelBuffer *read_png_file(const char* filename);

	// Write a PNG file
	void write_png_file(const char* filename,  PixelBuffer* src);

};

#endif
