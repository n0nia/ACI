#include "Hough.h"

cv::Mat Hough::DiscretHoughTransform(const cv::Mat& points, int threshold, int offset, bool draw)
{
	cv::Mat dst, cdst;
	//cv::cvtColor(points, dst, cv::COLOR_GRAY2BGR);

	cv::Canny(points, dst, 50, 200, 3);
	cv::cvtColor(dst, cdst, cv::COLOR_GRAY2BGR);

	// Standard Hough Line Transform
	std::vector<cv::Vec3f> lines; // will hold the results of the detection
	HoughLines(dst, lines, 1, CV_PI / 180, 150, 0, 0); // runs the actual detection

	if (!draw)
		return dst;

	// Draw the lines
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		cv::Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 2000 * (-b));
		pt1.y = cvRound(y0 + 2000 * (a));
		pt2.x = cvRound(x0 - 2000 * (-b));
		pt2.y = cvRound(y0 - 2000 * (a));
		line(cdst, pt1, pt2, cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
	}

	return cdst;
}

cv::Mat Hough::ProbabilisticHoughTransform(const cv::Mat& points, int threshold, int offset, bool draw)
{
	cv::Mat dst, cdstP;
	//cv::cvtColor(points, dst, cv::COLOR_GRAY2BGR);

	cv::Canny(points, dst, 50, 200, 3);
	cv::cvtColor(dst, cdstP, cv::COLOR_GRAY2BGR);

	// Probabilistic Line Transform
	std::vector<cv::Vec4i> linesP; // will hold the results of the detection
	HoughLinesP(dst, linesP, 1, CV_PI / 180, 50, 50, 10); // runs the actual detection

	if (!draw)
		return dst;

	// Draw the lines
	for (size_t i = 0; i < linesP.size(); i++)
	{
		cv::Vec4i l = linesP[i];
		line(cdstP, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
	}

	return cdstP;
}