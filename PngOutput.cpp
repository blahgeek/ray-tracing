/// @file PngOutput.cpp  @version 1.0 @date 08/21/2012
/// @author BlahGeek@Gmail.com

#include "PngOutput.h"
#include <cstdio>
#include <cassert>
#include <png.h>
#include <iostream>
using namespace std;

PngOutput::PngOutput(int width, int height, 
		const char * filename):Output(width, height){
	rows = new png_bytep[height];
	for(int i = 0 ; i < height; i ++)
		rows[i] = new png_byte[width * 3];

	fp = fopen(filename, "wb");
	png_ptr = png_create_write_struct(
			PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr = png_create_info_struct(png_ptr);
	assert(fp && png_ptr && info_ptr);
	png_init_io(png_ptr, fp);

	png_set_IHDR(png_ptr, info_ptr, width, height,
			8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	png_write_info(png_ptr, info_ptr);

}

void PngOutput::draw(int x, int y, Color color){
//	if(y == 0)
//		cerr << x << "/" << width << "   \r";
	png_byte * pos = rows[y] + x * 3;
	pos[2] = color.z > 255.0?255:uint8_t(color.z);
	pos[1] = color.y > 255.0?255:uint8_t(color.y);
	pos[0] = color.x > 255.0?255:uint8_t(color.x);
//	memcpy(rows[y]+ x * 3, &color, 3);
}

void PngOutput::finish(){
//	cerr << endl;
	png_write_image(png_ptr, rows);
	fclose(fp);
	png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	png_destroy_write_struct(&png_ptr, NULL);
	for(int i = 0 ; i < height; i ++)
		delete [] rows[i];
	delete [] rows;
}
