#include "Camera.h"
#include "RedColorDetector.h"
#include "Blobdetectionavans.h"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>

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
	Mat redDetectorFrame;

	SkinDetector redDetector;
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


		redDetectorFrame = redDetector.redColorDetection(frame);
		imshow("Red", redDetectorFrame);
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
	cv::Rect rec(xCenter, yCenter, (width / 2), (height / 2));

	rectangle(frame, rec, cv::Scalar(255), 1, 8, 0);

	cv::namedWindow("Step 2 draw Rectangle", cv::WINDOW_AUTOSIZE);
	cv::imshow("Step 2 draw Rectangle", frame);
}