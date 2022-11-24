#pragma once
#include "Utils.h"

class FourierTransform
{
private:
	static cv::Mat RearrangeImage(const cv::Mat&);
public:
	static cv::Mat FTTransform(const cv::Mat&);
};

