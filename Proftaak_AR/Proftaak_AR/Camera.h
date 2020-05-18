#pragma once
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>

class Camera
{
private:
	void drawRegionOfInterest(int width, int height, cv::Mat frame);

public:
	void ActivateCamera();
};