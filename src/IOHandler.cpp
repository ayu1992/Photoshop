#include <iostream>
#include "IOHandler.h"
#include "PngReader.h"
#include "JpegReader.h"
#include "Util.h"

using std::cout;
using std::endl;

IOHandler::IOHandler(){};
IOHandler::~IOHandler(){};

PixelBuffer* IOHandler::readImage(std::string filename){
	if(hasSuffix(filename, ".png")){
		return m_pngReader.read_png_file(filename.c_str());
	}else if(hasSuffix(filename, ".jpg") || hasSuffix(filename, ".jpeg")){
		return m_jpegReader.read_jpeg_file(filename.c_str());	
	}else{
		cout<<"[IOHandler]Abort"<<endl;
	}
}

void IOHandler::writeImage(std::string filename,  PixelBuffer* src){
	if(hasSuffix(filename, ".png")){
		m_pngReader.write_png_file(filename.c_str(), src);
	}
	else if(hasSuffix(filename, ".jpg") || hasSuffix(filename, ".jpeg")){
		m_jpegReader.write_jpeg_file(filename.c_str(), src);	
	}else{
		cout<<"[IOHandler]Abort"<<endl;
	}
}
