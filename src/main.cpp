#include "types.h"
#include "CameraController.h"

int main() {
	
	CCameraCantroller controller(16);

	controller.init();
	controller.start();
	
	// Main loop
	Mat img, mask;
	float attenuation = 0.5f;
	for(;;) {
		img = controller.getFrame();
		if (!img.empty()) {

			if (mask.empty()) img.copyTo(mask);

			for (int y = 0; y < img.rows; y++) {
				Vec3b* ptr = mask.ptr<Vec3b>(y);
				for (int x = 0; x < img.cols; x++) {
					float k = static_cast<float>(x) / img.cols;
					ptr[x] = Vec3b(k * 255, 0, 255 - k * 255);
				}
			}
			circle(mask, Point(mask.cols / 2, mask.rows / 2), 50, CV_RGB(100, 255, 100), 5);
			GaussianBlur(mask, mask, Size(17, 17), 50);
			putText(mask, "HCI", Point(100, 100), FONT_HERSHEY_SIMPLEX, 2, CV_RGB(255, 255, 255), 5);

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
	