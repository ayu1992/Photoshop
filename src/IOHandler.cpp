#include <iostream>
#include "IOHandler.h"
#include "PngHandler.h"
#include "JpegHandler.h"
#include "Util.h"

using std::cout;
using std::endl;

IOHandler::IOHandler(){};
IOHandler::~IOHandler(){};

PixelBuffer* IOHandler::readImage(std::string filename){

	// Dispatch work to the correct handler
	if(hasSuffix(filename, ".png")){
		return m_pngHandler.read_png_file(filename.c_str());
	}else if(hasSuffix(filename, ".jpg") || hasSuffix(filename, ".jpeg")){
		return m_jpegHandler.read_jpeg_file(filename.c_str());	
	}else{
		cout<<"[IOHandler]Abort"<<endl;
	}
}

void IOHandler::writeImage(std::string filename,  PixelBuffer* src){
	
	// Dispatch work to the correct handler
	if(hasSuffix(filename, ".png")){
		m_pngHandler.write_png_file(filename.c_str(), src);
	}
	else if(hasSuffix(filename, ".jpg") || hasSuffix(filename, ".jpeg")){
		m_jpegHandler.write_jpeg_file(filename.c_str(), src);	
	}else{
		cout<<"[IOHandler]Abort"<<endl;
	}
}
