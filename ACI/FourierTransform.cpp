#include "FourierTransform.h"

cv::Mat FourierTransform::RearrangeImage(const cv::Mat& inputImg)
{
	cv::Mat outputImg = inputImg.clone();

	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = outputImg.cols / 2;
	int cy = outputImg.rows / 2;

	cv::Mat q0(outputImg, cv::Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	cv::Mat q1(outputImg, cv::Rect(cx, 0, cx, cy));  // Top-Right
	cv::Mat q2(outputImg, cv::Rect(0, cy, cx, cy));  // Bottom-Left
	cv::Mat q3(outputImg, cv::Rect(cx, cy, cx, cy)); // Bottom-Right

	cv::Mat tmp;                                     // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);                                  // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);

	return outputImg;
}
cv::Mat FourierTransform::FTTransform(const cv::Mat& src) 
{
	cv::Mat planes[] = { cv::Mat_<float>(src) / cv::Scalar(255), cv::Mat::zeros(src.size(), CV_32F) };
	cv::Mat complexI;
	cv::merge(planes, 2, complexI);         // Add to the expanded another plane with zeros
	cv::dft(complexI, complexI);            // this way the result may fit in the source matrix

	split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
	cv::Mat magI = planes[0];

	magI += cv::Scalar::all(1);                    // switch to logarithmic scale
	log(magI, magI);

	// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));
	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	magI = RearrangeImage(magI);

	normalize(magI, magI, 0, 1, cv::NORM_MINMAX); // Transform the matrix with float values into a
												  // viewable image form (float between values 0 and 1).
	return magI;
}