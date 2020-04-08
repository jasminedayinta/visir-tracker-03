#pragma once

#include "types.h"
#include "Face.h"

class CMarker {
public:
    // draws faces into the image
    static void markFaces(Mat& img, const std::vector<ptr_face_t>& vFaces);
    
    // draws the points (e.g. from GoodFeaturesToTrack) into the image
    static void markPoints(Mat& img, const std::vector<Point2f>& vPoints, Scalar color = CV_RGB(255, 165, 0));
    
    // draws vectors of the vector Optical Flow Field () into the image
    void CMarker::markVecOFF(Mat& img, Mat& circ, Point2f p0, Point2f p1)
    
    // draws GUI
    static void markGUI(Mat& img);
};

