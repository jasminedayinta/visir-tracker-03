#include "types.h"
#include "CameraController.h"
#include "Face.h"
#include "Marker.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/video.hpp"

/**Function headers*/
std::vector<ptr_face_t> faceDetector(Mat frame);
std::vector<Point2f> calcOpticalFlow(Mat old_gray, Mat frame_gray, std::vector<Point2f> p0);
std::vector<Point2f> featureExtraction(Mat frame);
std::vector<Point2f> faceArea(Mat frame, std::vector<ptr_face_t> vpFaces);

/**Global variables*/
CascadeClassifier face_cascade;

int main(int argc, const char** argv) {
    

    std::vector<Point2f> vPoints;
    std::vector<ptr_face_t> vpFaces;
    
    namedWindow("Camera");
    
    //Problem 3.3 Number 5
    // mouse callback function which fills vPoints with coordinates of mouse clicks
    setMouseCallback("Camera", [] (int event, int x, int y, int flags, void* userdata) {
        if (userdata && event == EVENT_LBUTTONDOWN) {
            std::vector<Point2f> *pvPoints = (std::vector<Point2f> *) userdata;
            pvPoints->push_back(Point2f(x, y));
        }
    }, (void*) &vPoints);
    
    CCameraCantroller controller(16);

    controller.init();
    controller.start();
    
    // Main loop
    Mat img, mask;
    float attenuation = 0.5f;
    int f = 0; //frame count
    
    Mat old_gray, current_gray;
    std::vector<Point2f> p0, p1;
    
    for(;;) {
        img = controller.getFrame();

        if (!img.empty()) {
            if (mask.empty()) mask = Mat(img.size(), img.type());
            mask.setTo(0);

            // ------ PUT YOUR CODE HERE -------
            vpFaces = faceDetector(img);
            CMarker::markFaces(mask, vpFaces);
            add(img, mask, img);
            
            //Problem 3.3 Number 4
            if (f == 1 && f % 10 == 0){
                vPoints = faceArea(img, vpFaces);
                p0 = vPoints;
                cvtColor(img, old_gray, COLOR_BGR2GRAY);
            } else {
                //update the previous frame and points
                old_gray = current_gray.clone()
                p0 = p1;
            }
            
            // ------ PUT YOUR CODE HERE -------
            
            if(f % 2 == 0){
                cvtColor(img, current_gray, COLOR_BGR2GRAY);
                p1 = calcOpticalFlow(old_gray, current_gray, p0);
                
                for(int i = 0; i < p1.size(); i++){
                    CMarker::markVecOFF(mask, img, p1[i], p0[i]);
                    add(img, mask, img);
                }
            }
            
            // vPoints = good features to track ()
            //CMarker::markPoints(mask, vPoints);
            // { hFlow, vFlow } = calculate optical flow (vPoints)
            CMarker::markGUI(mask);
            

            add(img, attenuation * mask, img);

            imshow("Camera", img);
        }
        int key = waitKey(5);
        if (key == 27 || key == 'q') break;
        if (key == 'a') attenuation *= 1.1f;
        if (key == 'z') attenuation *= 0.9f;
    }

    controller.stop();
    return 0;
}
    
//Problem 3.2 Number 1; modified from Assignment 1
std::vector<ptr_face_t> faceDetector( Mat frame ){
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    std::vector<ptr_face_t> c_face;

    //-- Detect faces
    std::vector<Rect> faces;
    face_cascade.detectMultiScale( frame_gray, faces );
    
    //CFace objects
    for (int i = 0; i < faces.size(); i++){
        std::shared_ptr<CFace> face (new CFace(face));
        c_face.push_back(std::move(face))
    }
    
    return c_face;
    
     //-- Show what you got
    //imshow( "Capture - Face detection", frame );
}

//Problem 3.3 Number 1, modified from Assignment 2
std::vector<Point2f> calcOpticalFlow(Mat old_gray, Mat frame_gray, std::vector<Point2f> p0) {
    
    std::vector<Point2f> p1;
    std::vector<Point2f> p2;

   vector<uchar> status;
    vector<float> err;
    TermCriteria criteria = TermCriteria((TermCriteria::COUNT) + (TermCriteria::EPS), 10, 0.03);
        
    // calculate optical flow
    calcOpticalFlowPyrLK(old_gray, frame_gray, p0, p1, status, err, Size(15,15), 2, criteria);
    
    for(int i = 0; i < p0.size(); i++)
    {
        // Select good points
        if(status[i] == 1) {
            p2.push_back(p1[i]);
        }
    }
    
    return p2;
}

//Feature Extraction from Assignment 2
vector<Point2f> featureExtraction(Mat frame){
    Mat img_frame;
    cvtColor(frame, img_frame, COLOR_BGR2GRAY); // Convert to grayscale
    std::vector<Point2f> corners;

    goodFeaturesToTrack(frame, corners, 200, 0.01, 10,
                        Mat(), 3, false, 0.04);
    
    return corners;
}

//Modified from featureExtraction using markFaces
std::vector<Point2f> faceArea(Mat frame, std::vector<ptr_face_t> vpFaces) {
    Mat img_frame;
    cvtColor(frane, img_frame, COLOR_BGR2GRAY); // Convert to grayscale
    std::vector<Point2f> corners;
    std::vector<Point2f> detectCorners;
    
    for (auto face : vpFaces){
        Mat frame_gray(frame(face->getArea()));
        
        goodFeaturesToTrack(frame_gray, detectCorners, 200, 0.01, 10,
        Mat(), 3, false, 0.04);
        
        for(int i = 0; i < detectCorners.size(); i++){
            detectCorners[i].x += face->getArea().x;
            detectCorners[i].y += face->getArea().y;
        }
    }
    
    return corners;
}
