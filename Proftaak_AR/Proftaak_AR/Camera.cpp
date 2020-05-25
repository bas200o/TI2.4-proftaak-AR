#include "Camera.h"
#include "ColorDetection.h"
#include "Blobdetectionavans.h"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>

RNG rng(12345);

void Camera::ActivateCamera()
{
	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		std::cout << "Cannot open the video cam" << std::endl;
	}

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	std::cout << "Frame size : " << dWidth << " x " << dHeight << std::endl;

	cv::namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);

	Mat frame;
	
	Mat redDetection;
	ColorDetection detection;

	while (1)
	{
		bool bSuccess = cap.read(frame);

		flip(frame, frame, 3);

		if (!bSuccess)
		{
			std::cout << "Cannot read a frame from video stream" << std::endl;
			break;
		}

		imshow("MyVideo", frame);

		redDetection = detection.redColorDetection(frame);
		imshow("Red", redDetection);

		detection.trackObject(frame, redDetection);

		drawRegionOfInterest(dWidth, dHeight, frame);

		if (cv::waitKey(1) == 27)
		{
			std::cout << "esc key is pressed by user" << std::endl;
			break;
		}
	}
}

void Camera::drawRegionOfInterest(int width, int height, cv::Mat frame)
{
	int xCenter = (width - width / 2) / 2;
	int yCenter = (height - height / 2) / 2;
	int roiWidth = width / 2;
	int roiHeight = height / 2;

	//Draw a rectangle
	//cv::Rect rec(xCenter, yCenter, roiWidth, roiHeight);
	//rectangle(frame, rec, cv::Scalar(255), 1, 8, 0);

	cv::Rect recUpperLeft(0, 0, roiWidth, roiHeight);
	rectangle(frame, recUpperLeft, cv::Scalar(255), 1, 8, 0);

	cv::Rect recUpperRight(320, 0, roiWidth, roiHeight);
	rectangle(frame, recUpperRight, cv::Scalar(255), 1, 8, 0);

	cv::Rect recLowerLeft(0, 240, roiWidth, roiHeight);
	rectangle(frame, recLowerLeft, cv::Scalar(255), 1, 8, 0);

	cv::Rect recLowerRight(320, 240, roiWidth, roiHeight);
	rectangle(frame, recLowerRight, cv::Scalar(255), 1, 8, 0);

	//cv::Rect recLowerRight(320, 0, roiWidth, roiHeight);
	//rectangle(frame, recUpperRight, cv::Scalar(255), 1, 8, 0);

	//cv::Rect rec4(160, 120, 20, 20);
	//rectangle(frame, rec3, cv::Scalar(255), 1, 8, 0);

	ColorDetection check;
	check.checkIfInROI(recUpperLeft, recUpperRight, recLowerLeft, recLowerRight);

	cv::namedWindow("Step 2 draw Rectangle", cv::WINDOW_AUTOSIZE);
	cv::imshow("Step 2 draw Rectangle", frame);
}