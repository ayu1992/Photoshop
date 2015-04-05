#ifndef JPEGREADER_H
#define JPEGREADER_H

#include "PixelBuffer.h"

class JpegReader{

public:

	JpegReader();
	~JpegReader();
	
	PixelBuffer *read_jpeg_file(const char* filename);
	void write_jpeg_file(const char* filename, PixelBuffer* src);

};

#endif
