//
// IOHandler.h
//
// Handles image file I/O and PixelBuffer conversion

#ifndef IOHANDLER_H
#define IOHANDLER_H
#include <iostream>
#include "PngHandler.h"
#include "JpegHandler.h"
#include "PixelBuffer.h"

class IOHandler{

public:

	IOHandler();
	~IOHandler();

	// Reads an image file and stores content in a PixelBuffer
	PixelBuffer* readImage(std::string filename);

	// Write the contents in a PixelBuffer to an image file
	void writeImage(std::string filename,  PixelBuffer* src);

private:
	
	// Handlers for specific file formats
	PngHandler m_pngHandler;
	JpegHandler m_jpegHandler;
};
#endif