#pragma once

#include "types.h"
#include "Face.h"

class CMarker {
public:
	
	static void markFaces(Mat& img, const std::vector<ptr_face_t>& vFaces);
	static void markPoints(Mat& img, std::vector<Point2f> vPoints);
	static void markVecOFF(Mat& img, const Mat& hFlow, const Mat& vFlow);
};

