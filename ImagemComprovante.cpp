// OpenCVWebcamTest.cpp

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<conio.h>           // may have to modify this line if not using Windows

///////////////////////////////////////////////////////////////////////////////////////////////////


bool myfunction2(std::vector<cv::Point> i, std::vector<cv::Point> j) {
	return cv::contourArea(i) > cv::contourArea(j);
}



int main() {
	

	cv::Mat image;
	image = cv::imread("c:\\cordova\\page.jpg", 1);



	cv::Mat imgGrayscale;       // grayscale of input image
	cv::Mat imgBlurred;         // intermediate blured image
	cv::Mat imgCanny;           // Canny edge image
	cv::Mat dil;

	std::vector<std::vector<cv::Point>> contours;
	

	cv::cvtColor(image, imgGrayscale, CV_BGR2GRAY);                   // convert to grayscale


	cv::GaussianBlur(imgGrayscale,              // input image
		imgBlurred,                // output image
		cv::Size(5, 5),            // smoothing window width and height in pixels
		1.8);                      // sigma value, determines how much the image will be blurred

	cv::Canny(imgBlurred,                       // input image
		imgCanny,                         // output image
		50,                               // low threshold
		100);                             // high threshold


	//dilate(imgCanny, dil, cv::Mat(), cv::Point(-1, -1));

	findContours(imgCanny, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);


	
	
	printf("%d", contours.size());


	std::vector<cv::Point> ponto;

	
	std::sort(contours.begin(), contours.end(), myfunction2);

	for (int i = 0; i < contours.size(); i++) {

		double peri = cv::arcLength(contours[i], true);
		
		cv::approxPolyDP(contours[i], ponto, 0.02 * peri, true);

		if (ponto.size() == 4) {
			
				printf("VIVA USTRA %d\n", contours[i].size());
				cv::Scalar color = cv::Scalar(0,0, 255);
				cv::drawContours(image, contours, i, color, 3);
				break;
		}


	}

	cv::Rect myROI(10, 10, 100, 100);
	

	cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Display Image", image);

	cv::waitKey(0);

	return 0;

}










