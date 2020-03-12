#include "CameraController.h"

void CCameraCantroller::init()
{
	if (!m_camera.open(0)) {
		printf("Can't find a camera\n");
		exit(1);
	};
}

void CCameraCantroller::start()
{
	m_terminate_producer = false;
	m_thr_producer = std::thread([&]() {
		Mat img;
		for (;;) {

			m_mtx_FrameBuffer.lock();			
			m_camera >> m_vFrameBuffer[pointer_in];
			pointer_in = (pointer_in + 1) % m_vFrameBuffer.size();
			m_mtx_FrameBuffer.unlock();
			m_counter_in++;

			std::this_thread::sleep_for(std::chrono::milliseconds(5));

			if (m_terminate_producer) break;
		}
	});

	m_terminate_counter = false;
	m_thr_counter = std::thread([&]() {
		for (;;) {
			
			// TODO: use precise time imterval instead of 1			
			static size_t frames_in = 0;
			float fps_in = static_cast<float>(m_counter_in - frames_in) / 1.0f;
			frames_in = m_counter_in;

			static size_t frames_out = 0;
			float fps_out = static_cast<float>(m_counter_out - frames_out) / 1.0f;
			frames_out = m_counter_out;


			printf("FPS: in: %.2f | out: %.2f\n", fps_in, fps_out);

			std::this_thread::sleep_for(std::chrono::seconds(1));
			if (m_terminate_counter) break;
		}
	});
}

Mat CCameraCantroller::getFrame()
{
	Mat res;
	while (m_vFrameBuffer.empty())
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

	// ------ PUT YOUR CODE HERE -------
	m_mtx_FrameBuffer.lock();
	if (!m_vFrameBuffer.empty()) {
		res = m_vFrameBuffer.front();
	}
	m_mtx_FrameBuffer.unlock();
	m_counter_out++;
	return res;
}

void CCameraCantroller::stop()
{
	m_terminate_producer = true;
	m_thr_producer.join();

	m_terminate_counter = true;
	m_thr_counter.join();
}


