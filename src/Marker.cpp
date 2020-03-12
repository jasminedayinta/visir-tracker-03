#include "Marker.h"

void CMarker::markFaces(Mat& img, const std::vector<ptr_face_t>& vFaces)
{
	for (auto face : vFaces) {
		// ------ PUT YOUR CODE HERE -------
		// 1. Draw all faces using face->getArea();
		// 2. Print the text using face->getText();
		// 3. Print face id using face->getId();
	}
}

void markPoints(Mat& img, std::vector<Point2f> vPoints, Scalar color)
{
	for (auto& point : vPoints) 
		circle(img, point, 3, color, 2);
	
}

void markVecOFF(Mat& img, const Mat& hFlow, const Mat& vFlow) 
{
	// ------ PUT YOUR CODE HERE -------
}
