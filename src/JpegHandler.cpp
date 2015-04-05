#include <cstdio>
#include <cstdlib>
#include "jpeglib.h"
#include <setjmp.h>
#include "JpegHandler.h"
#include "ColorData.h"  
#include "PixelBuffer.h"

JpegHandler::JpegHandler(){}
JpegHandler::~JpegHandler(){}

struct my_error_mgr {
  struct jpeg_error_mgr pub;	/* "public" fields */

  jmp_buf setjmp_buffer;	/* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

/*
 * Here's the routine that will replace the standard error_exit method:
 */

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = (my_error_ptr) cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}


PixelBuffer* JpegHandler::read_jpeg_file (const char* filename)
{

  struct jpeg_decompress_struct cinfo;
  struct my_error_mgr jerr;

  FILE * infile;		/* source file */
  JSAMPARRAY buffer;		/* Output row buffer */
  int row_stride;		/* physical row width in output buffer */
  int i;
  if ((infile = fopen(filename, "rb")) == NULL) {
    fprintf(stderr, "can't open %s\n", filename);
    return 0;
  }

  /* Step 1: allocate and initialize JPEG decompression object */

  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;
  /* Establish the setjmp return context for my_error_exit to use. */
  if (setjmp(jerr.setjmp_buffer)) {
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
    return 0;
  }

  /* Now we can initialize the JPEG decompression object. */
  jpeg_create_decompress(&cinfo);

  /* Step 2: specify data source (eg, a file) */

  jpeg_stdio_src(&cinfo, infile);

  /* Step 3: read file parameters with jpeg_read_header() */

  (void) jpeg_read_header(&cinfo, TRUE);

  /* Step 4: set parameters for decompression */

  /* Step 5: Start decompressor */

  (void) jpeg_start_decompress(&cinfo);

  /* JSAMPLEs per row in output buffer */	/*n*(R+G+B)*/
  row_stride = cinfo.output_width * cinfo.output_components;

  PixelBuffer* pb = new PixelBuffer(cinfo.output_width, cinfo.output_height, ColorData(0.0,0.0,0.0));
 
  /* Make a one-row-high sample array that will go away when done with image */
  buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

  /* Step 6: while (scan lines remain to be read) */
  /*           jpeg_read_scanlines(...); */
  int channels = (int)cinfo.output_components;

  while (cinfo.output_scanline < cinfo.output_height) {
    (void) jpeg_read_scanlines(&cinfo, buffer, 1);
    for( i = 0; i < row_stride - channels; i += channels) 
		pb->setPixel( i / channels, cinfo.output_height - 1 - cinfo.output_scanline, ColorData(((float)buffer[0][i])/255.0, ((float)buffer[0][i+1])/255.0, (float)buffer[0][i+2]/255.0, cinfo.output_components == 4 ? ((float)buffer[0][i+3]/255.0) : 1));
  }

  /* Step 7: Finish decompression */

  (void) jpeg_finish_decompress(&cinfo);

  /* Step 8: Release JPEG decompression object */

  /* This is an important step since it will release a good deal of memory. */
  jpeg_destroy_decompress(&cinfo);
  fclose(infile);

  return pb;
}

void JpegHandler::write_jpeg_file (const char* filename, PixelBuffer* src){

  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
 
  FILE * outfile;   /* target file */
  JSAMPROW row_pointer[1];  /* pointer to JSAMPLE row[s] */
  int row_stride;   /* physical row width in image buffer */

  cinfo.err = jpeg_std_error(&jerr);
  /* Now we can initialize the JPEG compression object. */
  jpeg_create_compress(&cinfo);

  if ((outfile = fopen(filename, "wb")) == NULL) {
    fprintf(stderr, "can't open %s\n", filename);
    exit(1);
  }
  jpeg_stdio_dest(&cinfo, outfile);

  //bit_depth = 8;
  cinfo.image_width = src->getWidth();  /* image width and height, in pixels */
  cinfo.image_height = src->getHeight();
  cinfo.input_components = 3;   /* # of color components per pixel */
  cinfo.in_color_space = JCS_RGB;   /* colorspace of input image */
  
  jpeg_set_defaults(&cinfo);
  
  //jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

  jpeg_start_compress(&cinfo, TRUE);

  row_stride = cinfo.image_width * 3; /* JSAMPLEs per row in image_buffer */
  //(*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
  row_pointer[0] = (unsigned char*) malloc(3*cinfo.image_width*sizeof(unsigned char));
  //row_pointer[0] = & image_buffer[cinfo.next_scanline * row_stride];
  for (int y=0; y < cinfo.image_height; y++){
    for (int x=0; x < cinfo.image_width; x++){
      ColorData c = src->getPixel(x, cinfo.image_height - 1 -y);
      row_pointer[0][3*x+0] = static_cast<unsigned char>(c.getRed() * 255);
      row_pointer[0][3*x+1] = static_cast<unsigned char>(c.getGreen() * 255);
      row_pointer[0][3*x+2] = static_cast<unsigned char>(c.getBlue() * 255);
    }
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }
  free(row_pointer[0]);
  jpeg_finish_compress(&cinfo);
  /* After finish_compress, we can close the output file. */
  fclose(outfile);
  jpeg_destroy_compress(&cinfo);
}