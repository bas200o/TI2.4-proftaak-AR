#include "ColorDetection.h"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>

double x = 0.0;
double y = 0.0;

cv::Mat ColorDetection::redColorDetection(cv::Mat frame)
{
	cv::Mat hsvImage;
	cvtColor(frame, hsvImage, CV_RGB2HSV);

	cv::Mat mask;
	inRange(hsvImage, cv::Scalar(115, 155, 87), cv::Scalar(152, 255, 176), mask);

	cv::Mat erodeElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(-1, -1));
	cv::Mat dilateElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(8, 8), cv::Point(-1, -1));

	cv::erode(mask, mask, erodeElement);

	for (int i = 0; i < 4; i++)
		cv::dilate(mask, mask, dilateElement);
	
	return mask;
}

void ColorDetection::trackObject(cv::Mat frame, cv::Mat threshold)
{
	cv::Mat temp;
	threshold.copyTo(temp);
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	findContours(temp, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	std::vector<cv::Moments> mu(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		mu[i] = moments(contours[i], false);
	}

	std::vector<cv::Point2f> mc(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		x = mu[i].m10 / mu[i].m00;
		y = mu[i].m01 / mu[i].m00;
		//mc[i] = cv::Point2f(x, y);

		//image, Center of circle, radius, color, thickness, line type, shift
		circle(frame, cv::Point2f(x, y), 20, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
		//std::cout << "Coordinates: " << cv::Point(x, y) << std::endl;
	}
}

void ColorDetection::checkIfInROI(cv::Rect rec, cv::Rect rec2, cv::Rect rec3, cv::Rect rec4)
{
	if (rec.contains(cv::Point2f(x, y)) && rec3.contains(cv::Point2f(x, y))) {
		std::cout << "Go right" << std::endl;
	}

	if (rec2.contains(cv::Point2f(x, y)) && rec4.contains(cv::Point2f(x, y))) {
		std::cout << "Go left" << std::endl;
	}

	/*if (rec.contains(cv::Point2f(x, y))) {
		std::cout << "UpperLeft" << std::endl;
	}

	if (rec2.contains(cv::Point2f(x, y))) {
		std::cout << "UpperRight" << std::endl;
	}

	if (rec3.contains(cv::Point2f(x, y))) {
		std::cout << "LowerLeft" << std::endl;
	}

	if (rec4.contains(cv::Point2f(x, y))) {
		std::cout << "LowerRight" << std::endl;
	}*/
}
