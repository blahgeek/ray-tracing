/// @file PngOutput.h  @version 1.0 @date 08/21/2012
/// @author BlahGeek@Gmail.com
#ifndef H_PNG_OUTPUT_
#define H_PNG_OUTPUT_

#include "output.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>
using cv::imread;
using cv::imwrite;
using cv::Mat;
using std::string;

class PngOutput: public Output{
	private:
        string filename;
        Mat img;
	public:
		PngOutput(int width, int height, 
				const char * filename);
		void draw(int , int , Color);
		void finish();
};

#endif

