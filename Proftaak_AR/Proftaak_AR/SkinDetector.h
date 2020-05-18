#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>

class SkinDetector 
{
public:
	cv::Mat skinColorDetection(cv::Mat frame);
};