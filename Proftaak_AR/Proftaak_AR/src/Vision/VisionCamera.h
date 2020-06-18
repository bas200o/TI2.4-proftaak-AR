#pragma once
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>

namespace Vision
{
	class VisionCameraCallbackHandler
	{
	public:
		virtual void setAngle(float angle) = 0;
	};

	class VisionCamera
	{
	private:
		VisionCameraCallbackHandler* callbackHandler;

	private:
		void drawRegionOfInterest(double width, double height, cv::Mat frame);
		float calculateAngle(std::vector<cv::Point2f> points);

	public:
		void activateCamera();
		void setCallbackHandler(VisionCameraCallbackHandler* callbackHandler);
	};
}