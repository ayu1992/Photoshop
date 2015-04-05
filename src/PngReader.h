#ifndef PNGREADER_H
#define PNGREADER_H

#include <iostream>
#include "PixelBuffer.h"

class PngReader{

public:

	PngReader();
	~PngReader();			// linker error

	PixelBuffer *read_png_file(const char* filename);
	void write_png_file(const char* filename,  PixelBuffer* src);

};

#endif
