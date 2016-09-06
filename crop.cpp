#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<conio.h>           




bool myfunction2(std::vector<cv::Point> i, std::vector<cv::Point> j) {
	return cv::contourArea(i) > cv::contourArea(j);
}


bool myfunctionOrder(cv::Point2f i, cv::Point2f j) {
	return i.y > j.y;
}



int main() {


	cv::Mat image;
	image = cv::imread("c:\\cordova\\carta.jpg", 1);



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


	std::vector<cv::Point2f> ponto;


	std::sort(contours.begin(), contours.end(), myfunction2);

	for (int i = 0; i < contours.size(); i++) {

		double peri = cv::arcLength(contours[i], true);

		cv::approxPolyDP(contours[i], ponto, 0.02 * peri, true);

		if (ponto.size() == 4) {

			printf("\nVIVA USTRA %d, %d\n", ponto[0].x, ponto[0].y);
			printf("\nVIVA USTRA %d, %d\n", ponto[1].x, ponto[1].y);
			printf("\nVIVA USTRA %d, %d\n", ponto[2].x, ponto[2].y);
			printf("\nVIVA USTRA %d, %d\n", ponto[3].x, ponto[3].y);

			cv::Scalar color = cv::Scalar(0, 0, 255);
			//cv::drawContours(image, contours, i, color, 3);
			break;
		}
	}


	cv::Point2f tl;
	cv::Point2f tr;
	cv::Point2f br;
	cv::Point2f bl;


	//ordena Pela Altura
	std::sort(ponto.begin(), ponto.end(), myfunctionOrder);

	printf("%f  %f  %f  %f  ", ponto[0].y, ponto[1].y, ponto[2].y, ponto[3].y);

	if (ponto[0].x < ponto[1].x) {
		tl = ponto[0];
		tr = ponto[1];
	}
	else {
		tl = ponto[1];
		tr = ponto[0];
	}


	if (ponto[2].x < ponto[3].x) {
		bl = ponto[2];
		br = ponto[3];
	}
	else {
		bl = ponto[2];
		br = ponto[3];
	}




	std::vector<cv::Point2f> pontosImagem;
	pontosImagem.push_back(bl);
	pontosImagem.push_back(br);
	pontosImagem.push_back(tr);
	pontosImagem.push_back(tl);


	float widthA = sqrt(pow((br.x - bl.x), 2) + pow((br.y - bl.y), 2));
	float widthB = sqrt(pow((tr.x - tl.x), 2) + pow((tr.y - tl.y), 2));
	float maxWidth = std::max(widthA, widthB);

	float heightA = sqrt(pow((tr.x - br.x), 2) + pow((tr.y - br.y), 2));
	float heightB = sqrt(pow((tl.x - bl.x), 2) + pow((tl.y - bl.y), 2));
	float maxHeight = std::max(heightA, heightB);



	std::vector<cv::Point2f> novosPontos;
	novosPontos.push_back(cv::Point2f(0.0f, 0.0f));
	novosPontos.push_back(cv::Point2f(maxWidth - 1.0f, 0.0f));
	novosPontos.push_back(cv::Point2f(maxWidth - 1.0f, maxHeight - 1.0f));
	novosPontos.push_back(cv::Point2f(0.0f, maxHeight - 1.0f));




	cv::Mat warpMatrix = cv::getPerspectiveTransform(pontosImagem, novosPontos);
	cv::Mat saida;


	cv::Size size(maxWidth, maxHeight);
	cv::warpPerspective(image, saida, warpMatrix, size, cv::INTER_LINEAR, cv::BORDER_CONSTANT);


	cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Display Image", image);


	cv::cvtColor(saida, saida, cv::COLOR_BGR2GRAY);
	cv::namedWindow("Image Saida", cv::WINDOW_AUTOSIZE);
	cv::imshow("Image Saida", saida);

	cv::waitKey(0);

	return 0;

}