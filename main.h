#pragma once

#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>

#if _DEBUG
	#pragma comment (lib, "opencv_world470d.lib")
#else
	#pragma comment (lib, "opencv_world470.lib")
#endif

#define CMD_WHITE 0x0f

class videoManager {
private:
	const std::string videoPass = "media\\hart.avi";
	cv::VideoCapture video;
	int width = 0;
	int height = 0;
	cv::Mat image;
	COORD cmdPos;

	void setup();
public:
	videoManager();
	~videoManager();

	int GUIrender();
	void CMDRender();
};