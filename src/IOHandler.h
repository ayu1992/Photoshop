#ifndef IOHANDLER_H
#define IOHANDLER_H
#include <iostream>
#include "PngReader.h"
#include "JpegReader.h"
#include "PixelBuffer.h"

class IOHandler{

public:
	IOHandler();
	~IOHandler();

	PixelBuffer* readImage(std::string filename);
	void writeImage(std::string filename,  PixelBuffer* src);

private:
	PngReader m_pngReader;
	JpegReader m_jpegReader;
};
#endif