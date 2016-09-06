#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "opencv2/photo.hpp"

#include <vector>

int ASDFG(int argc, char** argv) 
{
	// READ RGB color image and convert it to Lab
	cv::Mat bgr_image = cv::imread("c:\\cordova\\Screenshot_1.jpg");
	cv::Mat de_image;

	
	
	cv::imshow("image original", bgr_image);
	//cv::imshow("image CLAHE", de_image);
	
	cv::waitKey();

	return 0;
}