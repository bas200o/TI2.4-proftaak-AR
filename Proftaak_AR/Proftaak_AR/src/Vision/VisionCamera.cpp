#include "VisionCamera.h"
#include "ColorDetection.h"
#include "blobdetectionavans.h"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>

RNG rng(12345);

#ifdef _DEBUG
const bool debugInfo = true;
#else
const bool debugInfo = false;
#endif

void Vision::VisionCamera::activateCamera()
{
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		std::cout << "Cannot open the video cam" << std::endl;
	}

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	std::cout << "Frame size : " << dWidth << " x " << dHeight << std::endl;

	if ( debugInfo )
	{
		cv::namedWindow("Camera source", CV_WINDOW_AUTOSIZE);
		cv::namedWindow("Red", CV_WINDOW_AUTOSIZE);
	}

	Mat frame, redDetection;
	ColorDetection detection;

	while (1)
	{
		bool bSuccess = cap.read(frame);

		if (!bSuccess)
		{
			std::cout << "Cannot read a frame from video stream" << std::endl;
			break;
		}

		//flip(frame, frame, 3);

		redDetection = detection.colorDetection(frame);

		if (debugInfo)
		{
			imshow("Red", redDetection);
			imshow("Camera source", frame);
		}

		float angle = calculateAngle(detection.trackObject(frame, redDetection));

		drawRegionOfInterest(dWidth, dHeight, frame);

		std::cout << "angle = " << angle << std::endl;

		if (callbackHandler != nullptr)
			callbackHandler->setAngle(angle);

		if (cv::waitKey(1) == 27)
		{
			std::cout << "esc key is pressed by user" << std::endl;
			destroyAllWindows();
			break;
		}
	}
}

void Vision::VisionCamera::setCallbackHandler(VisionCameraCallbackHandler* callbackHandler)
{
	this->callbackHandler = callbackHandler;
}

void Vision::VisionCamera::drawRegionOfInterest(double width, double height, cv::Mat frame)
{
	if (debugInfo)
	{
		cv::namedWindow("center of gravity", cv::WINDOW_AUTOSIZE);
		cv::imshow("center of gravity", frame);
	}
}

float Vision::VisionCamera::calculateAngle(std::vector<cv::Point2f> points)
{
	if (points.size() != 2)
	{
		if (debugInfo)
		{
			std::cout << "to many or to few points given. \nShould be 2 there are: " << points.size() << std::endl;
		}
		return 0.0f;
	}
	else 
	{
		if (debugInfo) 
		{
			std::cout << "point x1 , y1, x2, y2 " << points[0].x << " - " << points[0].y << " - " << points[1].x << " - " << points[1].y << std::endl;
		}

		float angle = 0.0f;
		if (points[0].x > points[1].x)
		{
			angle = (points[0].y - points[1].y) / (points[0].x - points[1].x);
		}
		else
		{
			angle = (points[1].y - points[0].y) / (points[1].x - points[0].x);
		}


		return angle;
	}
}