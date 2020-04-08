#include "Marker.h"

//Problem 3.2 Number 2, modified from Assignment 1 detectAndDisplay()
void CMarker::markFaces(Mat& img, const std::vector<ptr_face_t>& vFaces)
{
    for (auto face : vFaces) {
        // ------ PUT YOUR CODE HERE -------
        // 1. Draw all faces using face->getArea();
        // 2. Print the text using face->getText();
        // 3. Print face id using face->getId();
        
        Rect area = face->getArea();
        std::string text = face->getText();
        int id = face->getId();
        std::string ID = std::to_string(id);
        
        Point center( area.x + area.width/2, area.y + area.height/2 );
        Point top( area.x , area.y);
        Point bottom( area.x , area.y + area.height);
        ellipse( img, center, Size( area.width/2, area.height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4 );
        putText(img, ID, top, FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 4);
    }
}

void CMarker::markPoints(Mat& img, const std::vector<Point2f>& vPoints, Scalar color)
{
    for (auto& point : vPoints)
        circle(img, point, 3, color, 2);
}

//Problem 3.3 Number 2
void CMarker::markVecOFF(Mat& img, Mat& circ, Point2f p0, Point2f p1)
{
    // ------ PUT YOUR CODE HERE -------
    line(img, p0, p1, Scalar(255,255,255), 3);
    circle(circ, p0, 5, Scalar(255,200,0), 1)
}

void CMarker::markGUI(Mat& img)
{
    // ------ PUT YOUR CODE HERE -------
    // Implement yout ouw GUI
    // Show fps
    for (int y = 0; y < img.rows; y++) {
        Vec3b* ptr = img.ptr<Vec3b>(y);
        for (int x = 0; x < img.cols; x++) {
            float k = static_cast<float>(x) / img.cols;
            ptr[x] = Vec3b(k * 255, 0, 255 - k * 255);
        }
    }
    circle(img, Point(img.cols / 2, img.rows / 2), 50, CV_RGB(100, 255, 100), 5);
    GaussianBlur(img, img, Size(17, 17), 50);
    putText(img, "HCI", Point(100, 100), FONT_HERSHEY_SIMPLEX, 2, CV_RGB(255, 255, 255), 5);
}
