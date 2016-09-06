#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<conio.h>           




bool myfunction3(std::vector<cv::Point> i, std::vector<cv::Point> j) {
	
	
	std::vector<cv::Point> ponto;
	std::vector<cv::Point> ponto1;

	double peri = cv::arcLength(i, true);
	cv::approxPolyDP(i, ponto, 0.02 * peri, true);


	double peri1 = cv::arcLength(j, true);
	cv::approxPolyDP(j, ponto1, 0.02 * peri1, true);



	return cv::contourArea(ponto) > cv::contourArea(ponto1);
}


bool myfunctionOrder1(cv::Point2f i, cv::Point2f j) {
	return i.y > j.y;
}



int asdfg() {


	cv::Mat image;
	image = cv::imread("c:\\cordova\\seguro.jpg", 1);



	cv::Mat imgGrayscale;
	cv::Mat imgBlurred;
	cv::Mat imgCanny;
	cv::Mat dil;

	std::vector<std::vector<cv::Point>> contours;


	cv::cvtColor(image, imgGrayscale, CV_BGR2GRAY);


	cv::GaussianBlur(imgGrayscale,
		imgBlurred,
		cv::Size(5, 5),
		1.8);

	cv::Canny(imgBlurred,
		imgCanny,
		50,
		100);

	findContours(imgCanny, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);


	std::vector<cv::Point> ponto;


	std::sort(contours.begin(), contours.end(), myfunction3);

	for (int i = 0; i < contours.size(); i++) {

		double peri = cv::arcLength(contours[i], true);

		cv::approxPolyDP(contours[i], ponto, 0.02 * peri, true);
		std::vector<std::vector<cv::Point>> bosta;
			
		printf("abacate %f   %d\n", cv::contourArea(ponto), ponto.size());
		bosta.push_back(ponto);
		cv::Scalar color = cv::Scalar(0, 0, 255);
		cv::drawContours(image, bosta, 0, color, 3);
		break;		
		
	}

	cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Display Image", image);


	

	cv::waitKey(0);

	return 0;

}