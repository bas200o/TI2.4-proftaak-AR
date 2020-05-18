#include "RedColorDetector.h"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>

cv::Mat ColorDetector::redColorDetection(cv::Mat frame)
{
	cv::Mat hsvImage;
	cvtColor(frame, hsvImage, CV_BGR2HSV);

	cv::Mat mask;
	inRange(hsvImage, cv::Scalar(55, 165, 65), cv::Scalar(180, 255, 255), mask);

	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(-1, -1));

	for (int i = 0; i < 3; i++)
		cv::dilate(mask, mask, element);
	
	return mask;
}