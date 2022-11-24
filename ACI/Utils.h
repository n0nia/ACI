#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include <vector>

#include "Globals.h"

float ComputeVariance(std::vector<int>, float);
float ComputeMeanValue(std::vector<int>);

std::vector<int> ComputeVerticalHistogram(cv::Mat);

void RotateImage(const cv::Mat&, cv::Mat&, float, cv::Scalar);

cv::Mat CreateSquareImage(const cv::Mat&, const cv::Scalar&);
