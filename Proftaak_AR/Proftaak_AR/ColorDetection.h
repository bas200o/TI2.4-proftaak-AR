#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>

class ColorDetection 
{
public:
	cv::Mat redColorDetection(cv::Mat frame);
	void trackObject(cv::Mat frame, cv::Mat threshold);
	void checkIfInROI(cv::Rect rec, cv::Rect rec2, cv::Rect rec3, cv::Rect rec4);
};