#include "Utils.h"

using namespace std;
using namespace cv;

float ComputeVariance(vector<int> sumRows, float med)
{
	float var = 0;
	for (size_t j = 0; j < sumRows.size(); j++)
		var += pow(sumRows[j] - med, 2);
	var /= sumRows.size();
	return var;
}

float ComputeMeanValue(vector<int> sumRows)
{
	float med = 0;
	for (size_t j = 0; j < sumRows.size(); j++)
		med += sumRows[j];
	med /= sumRows.size();
	return med;
}

vector<int> ComputeVerticalHistogram(Mat src)
{
	Mat row_sum;
	threshold(src, src, 150, 1, THRESH_BINARY);
	//compute row sums
	reduce(src, row_sum, 1, REDUCE_SUM, CV_32F);

	//copy sums from Mat to vector
	vector<int> sumRows(src.size().height);
	sumRows.assign((float*)row_sum.data, (float*)row_sum.data + row_sum.total());

	return sumRows;
}

void RotateImage(const Mat& image, Mat& out_image, float angle, cv::Scalar emptyColor)
{
	// grab the dimensions of the image and then determine the center
	int h = image.size().height;
	int w = image.size().width;
	Point2f center = Point2f(w / 2.0f, h / 2.0f);

	// grab the rotation matrix(applying the negative of the
	// angle to rotate clockwise), then grab the sine and cosine
	// (i.e., the rotation components of the matrix)
	Mat M = getRotationMatrix2D(center, angle, 1.0);
	double cos = abs(M.at<double>(0, 0));
	double sin = abs(M.at<double>(0, 1));

	// compute the new bounding dimensions of the image
	int nW = int((h * sin) + (w * cos));
	int nH = int((h * cos) + (w * sin));

	// adjust the rotation matrix to take into account translation
	M.at<double>(0, 2) += (nW / 2) - center.x;
	M.at<double>(1, 2) += (nH / 2) - center.y;

	// perform the actual rotation and return the image
	cv::warpAffine(image, out_image, M, cv::Size(nW, nH), cv::INTER_LINEAR, cv::BORDER_CONSTANT, emptyColor);
}

cv::Mat CreateSquareImage(const cv::Mat& inputImage, const cv::Scalar& bgcolor)
{
	cv::Mat outputImage;
	int max = inputImage.cols;
	if (max < inputImage.rows)
		max = inputImage.rows;
	cv::Size dstSize = { max,max };

	double h1 = dstSize.width * (inputImage.rows / (double)inputImage.cols);
	double w2 = dstSize.height * (inputImage.cols / (double)inputImage.rows);
	if (h1 <= dstSize.height)
		cv::resize(inputImage, outputImage, cv::Size(dstSize.width, h1));

	else
		cv::resize(inputImage, outputImage, cv::Size(w2, dstSize.height));

	int top = (dstSize.height - outputImage.rows) / 2;
	int down = (dstSize.height - outputImage.rows + 1) / 2;
	int left = (dstSize.width - outputImage.cols) / 2;
	int right = (dstSize.width - outputImage.cols + 1) / 2;

	cv::copyMakeBorder(outputImage, outputImage, top, down, left, right, cv::BORDER_CONSTANT, bgcolor);

	return outputImage;
}