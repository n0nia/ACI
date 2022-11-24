#include "ProjectionProfiling.h"

std::vector<int> ProjectionProfiling::PPTransform(cv::Mat points)
{
	std::vector<int> sumRows;
		
	sumRows = ComputeVerticalHistogram(points);

	return sumRows;
}
