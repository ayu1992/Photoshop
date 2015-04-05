//
// JpegHandler.h
//
// Handles PNG file I/O

#ifndef JPEGHANDLER_H
#define JPEGHANDLER_H

#include "PixelBuffer.h"

class JpegHandler{

public:

	JpegHandler();
	~JpegHandler();
	
	// Read in a JPEG/JPG file
	PixelBuffer *read_jpeg_file(const char* filename);

	// Writes a JPEG/JPG file
	void write_jpeg_file(const char* filename, PixelBuffer* src);

};

#endif
