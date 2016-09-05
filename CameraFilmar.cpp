// OpenCVWebcamTest.cpp

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<conio.h>           // may have to modify this line if not using Windows


bool myfunction(std::vector<cv::Point> i, std::vector<cv::Point> j) {
	return cv::contourArea(i) > cv::contourArea(j);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
int ma___in() {
	cv::VideoCapture capWebcam(0);            // declare a VideoCapture object and associate to webcam, 0 => use 1st webcam

	if (capWebcam.isOpened() == false) {                                // check if VideoCapture object was associated to webcam successfully
		std::cout << "error: capWebcam not accessed successfully\n\n";      // if not, print error message to std out
		_getch();                                                           // may have to modify this line if not using Windows
		return(0);                                                          // and exit program
	}

	cv::Mat imgOriginal;        // input image
	cv::Mat imgGrayscale;       // grayscale of input image
	cv::Mat imgBlurred;         // intermediate blured image
	cv::Mat imgCanny;           // Canny edge image
	cv::Mat dil;

	std::vector<cv::Vec3f> v3fCircles;

	std::vector<std::vector<cv::Point>> contours;

	char charCheckForEscKey = 0;

	while (charCheckForEscKey != 27 && capWebcam.isOpened()) {            // until the Esc key is pressed or webcam connection is lost
		bool blnFrameReadSuccessfully = capWebcam.read(imgOriginal);            // get next frame

		if (!blnFrameReadSuccessfully || imgOriginal.empty()) {                 // if frame not read successfully
			std::cout << "error: frame not read from webcam\n";                 // print error message to std out
			break;                                                              // and jump out of while loop
		}

		cv::cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);                   // convert to grayscale


		cv::GaussianBlur(imgGrayscale,              // input image
			imgBlurred,                // output image
			cv::Size(5, 5),            // smoothing window width and height in pixels
			1.8);                      // sigma value, determines how much the image will be blurred

		cv::Canny(imgBlurred,                       // input image
			imgCanny,                         // output image
			50,                               // low threshold
			100);                             // high threshold

		//dilate(imgCanny, dil, cv::Mat(), cv::Point(-1, -1));

		findContours(dil, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
		

		findContours(imgCanny, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);




		printf("%d", contours.size());


		std::vector<cv::Point> ponto;


		std::sort(contours.begin(), contours.end(), myfunction);

		for (int i = 0; i < contours.size(); i++) {

			double peri = cv::arcLength(contours[i], true);

			cv::approxPolyDP(contours[i], ponto, 0.02 * peri, true);

			if (ponto.size() == 4) {

				printf("VIVA USTRA %f\n", cv::contourArea(contours[i]));
				cv::Scalar color = cv::Scalar(0, 0, 255);
				cv::drawContours(imgOriginal, contours, i, color, 3);
				break;
			}


		}




		printf("%d", contours.size());
		// declare windows
		cv::namedWindow("imgOriginal", CV_WINDOW_NORMAL);       // note: you can use CV_WINDOW_NORMAL which allows resizing the window
		cv::namedWindow("imgCanny", CV_WINDOW_NORMAL);          // or CV_WINDOW_AUTOSIZE for a fixed size window matching the resolution of the image
																// CV_WINDOW_AUTOSIZE is the default
		cv::imshow("imgOriginal", imgOriginal);                 // show windows
		cv::imshow("imgCanny", dil);                       //

		charCheckForEscKey = cv::waitKey(1);        // delay (in ms) and get key press, if any
	}   // end while

	return(0);
}









