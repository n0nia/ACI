#pragma once
#include "Utils.h"

class Hough
{
public:
    static cv::Mat DiscretHoughTransform(const cv::Mat&, int, int, bool);
    static cv::Mat ProbabilisticHoughTransform(const cv::Mat&, int, int, bool);
};

