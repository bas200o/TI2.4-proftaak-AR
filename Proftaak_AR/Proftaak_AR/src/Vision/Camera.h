#pragma once
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>

class Camera
{
private:
	void drawRegionOfInterest(double width, double height, cv::Mat frame);
	float calculateAngle(std::vector<cv::Point2f> points);


public:
	void ActivateCamera();
};