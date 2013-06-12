/// @file PngOutput.h  @version 1.0 @date 08/21/2012
/// @author BlahGeek@Gmail.com
#ifndef H_PNG_OUTPUT_
#define H_PNG_OUTPUT_

#include "output.h"
#include <png.h>

class PngOutput: public Output{
	private:
		png_bytep * rows;
		png_structp png_ptr;
		FILE * fp;
		png_infop info_ptr;
	public:
		PngOutput(int width, int height, 
				const char * filename);
		void draw(int , int , Color);
		void finish();
};

#endif

