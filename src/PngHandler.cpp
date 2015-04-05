#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <png.h>
#include "PngHandler.h"
#include "ColorData.h"  
#include "PixelBuffer.h"

PngHandler::PngHandler(){}
PngHandler::~PngHandler(){}

PixelBuffer* PngHandler::read_png_file(const char* file_name)
{
        // Declare variables
        int width, height, x, y, channels, number_of_passes;
        png_structp png_ptr;
        png_infop info_ptr; 
        png_byte color_type, bit_depth;
        png_bytep * row_pointers;

        unsigned int sig_read = 0; 
        /* open file and test for it being a png */
        FILE *fp = fopen(file_name, "rb");

        /* initialize stuff */
        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        
        info_ptr = png_create_info_struct(png_ptr);
        
        setjmp(png_jmpbuf(png_ptr));
       
        png_init_io(png_ptr, fp);
        //png_set_read_fn(png_ptr, (void *)user_io_ptr, user_read_fn);

        png_set_sig_bytes(png_ptr, sig_read);
    
        png_read_info(png_ptr, info_ptr);
      
        width = png_get_image_width(png_ptr, info_ptr);
        height = png_get_image_height(png_ptr, info_ptr);
        color_type = png_get_color_type(png_ptr, info_ptr);
        bit_depth = png_get_bit_depth(png_ptr, info_ptr);

        number_of_passes = png_set_interlace_handling(png_ptr);
        png_read_update_info(png_ptr, info_ptr);


        /* read file */
        setjmp(png_jmpbuf(png_ptr));
        
        row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
        for (y=0; y<height; y++)
                row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

        png_read_image(png_ptr, row_pointers);
   
        fclose(fp);

        if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB){
            channels = 3;
        }else if(png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGBA){
            channels = 4;
        }else{
            printf("png type not RGBA or RGB");
        }
            
        PixelBuffer* pb = new PixelBuffer(width, height, ColorData(0.0,0.0,0.0));
        for (y = 0; y < height; y++) {
                png_byte* row = row_pointers[y];
                for (x = 0; x < width; x++) {
                        png_byte* ptr = &(row[x*channels]);  
                        pb->setPixel( x, height - 1 - y, ColorData(ptr[0]/255.0, ptr[1]/255.0, ptr[2]/255.0, channels == 4 ? ptr[3]/255.0 : 1));
                }
        }
        return pb;

}

void PngHandler::write_png_file(const char* file_name,  PixelBuffer* src)
{
        // Declare variables
        int width, height, x, y, channels, number_of_passes;
        png_structp png_ptr;
        png_infop info_ptr; 
        png_byte color_type, bit_depth;
        png_bytep * row_pointers;

        /* create file */
        FILE *fp = fopen(file_name, "wb");

        /* initialize stuff */
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        info_ptr = png_create_info_struct(png_ptr);
        setjmp(png_jmpbuf(png_ptr));
                //abort_("[write_png_file] Error during init_io");

        png_init_io(png_ptr, fp);

        /* write header */
        setjmp(png_jmpbuf(png_ptr));

        width = src->getWidth();
        height = src->getHeight();
        channels = 4;
        bit_depth = 8;
        png_set_IHDR(png_ptr, info_ptr, width, height,
                     bit_depth, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

        png_write_info(png_ptr, info_ptr);


        /* write bytes */
        setjmp(png_jmpbuf(png_ptr));
                //abort_("[write_png_file] Error during writing bytes");
        row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
        for (y=0; y<height; y++){
            row_pointers[y] = (png_byte*) malloc(sizeof(png_byte) * width * channels);
            for (x = 0; x < width; x++) {
                png_byte* ptr = &(row_pointers[y][x*channels]);    
                ColorData c = src->getPixel(x, height - 1 -y);
                ptr[0] = static_cast<char>(c.getRed() * 255);
                ptr[1] = static_cast<char>(c.getGreen() * 255);
                ptr[2] = static_cast<char>(c.getBlue() * 255);
                ptr[3] = static_cast<char>(c.getAlpha() * 255);
            }
        }
        png_write_image(png_ptr, row_pointers);

        /* end write */
        setjmp(png_jmpbuf(png_ptr));

        png_write_end(png_ptr, NULL);

        /* cleanup heap allocation */
        for (y=0; y<height; y++)    free(row_pointers[y]);
        free(row_pointers);

        fclose(fp);
}



