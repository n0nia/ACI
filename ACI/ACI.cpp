#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <math.h>
#include <algorithm>
#include <ctime>
#include <iomanip>

#include "Hough.h"
#include "FourierTransform.h"
#include "ProjectionProfiling.h"
#include "Utils.h"

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
    // variables for Hough
    Mat dst, cdst, cdstP;
    // variables for Fourier Transform
    Mat magI;
    // variables for Projection Profiling
    std::vector<int> pp;

    char filename[100];
    sprintf_s(filename, "E:\\master\\An2\\ACI\\Proiect\\ACI\\ACI\\in\\1.png");

    // Loads an image
    Mat src = imread(filename, IMREAD_GRAYSCALE);
    Mat src2 = src.clone();

    // Hough
    cdst = Hough::DiscretHoughTransform(src2, 10, 90, true);
    cdstP = Hough::ProbabilisticHoughTransform(src2, 10, 90, true);
    // Fourier
    magI = FourierTransform::FTTransform(src2);
    // Projection Profiling
    pp = ProjectionProfiling::PPTransform(src2);

    // Source Image
    imshow("Source", src);

    // Show results for Hough
    imshow("Spectrum magnitude", magI);

    // Show results for Fourier Transform
    imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst);
    imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);

    // Show results for Projection Profiling
    for (auto it : pp)
    {
        cout << it << " ";
    }

    // Rotate image
    Mat rotatedImg;
    RotateImage(src, rotatedImg, 10, cv::Scalar(0));
    imshow("Rotated image ", rotatedImg);

    // Create Square Image
    char filename2[100];
    sprintf_s(filename2, "E:\\master\\An2\\ACI\\Proiect\\ACI\\ACI\\in\\1.png");

    // Loads an image
    Mat src3 = imread(filename2, IMREAD_GRAYSCALE);
    Mat squareImg = CreateSquareImage(src3, cv::Scalar(255));
    imshow("Square image ", squareImg);

	// Wait and Exit
	waitKey();

    return 0;
}
