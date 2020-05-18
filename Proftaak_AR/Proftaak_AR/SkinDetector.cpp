#include "SkinDetector.h"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>

cv::Mat SkinDetector::skinColorDetection(cv::Mat frame)
{
	cv::Mat binaryImage;

	cv::Mat hsvImage;
	cvtColor(frame, hsvImage, CV_BGR2HSV);
	
	inRange(hsvImage, cv::Scalar(0, 10, 60), cv::Scalar(20, 150, 255), binaryImage);

	cv::Mat structuringElement = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3), cv::Point(-1, -1));

	for (int i = 0; i < 5; i++) {
		cv::dilate(binaryImage, binaryImage, structuringElement);
	}
	
	return binaryImage;
}