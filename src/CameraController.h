#pragma once

#include "types.h"

class CCameraCantroller {
public:
	CCameraCantroller() {}
	~CCameraCantroller(void) = default;

	void start() {
		
		if (!m_camera.open(0)) {
			printf("Can't find a camera\n");
			exit(1);
		};

		
		m_terminate_producer = false;
		m_thr_producer = std::thread([&]() {
			Mat img;
			for (;;) {
				m_camera >> img;
				m_mtx_FrameBuffer.lock();
				m_vFrameBuffer.push_back(img.clone());
				m_mtx_FrameBuffer.unlock();
				
				std::this_thread::sleep_for(std::chrono::milliseconds(5));

				if (m_terminate_producer) break;
			}
		});

		m_terminate_cleaner = false;
		m_thr_cleaner = std::thread([&]() {
			for (;;) {
				m_mtx_FrameBuffer.lock();
				while (m_vFrameBuffer.size() > 32)
					m_vFrameBuffer.pop_front();
				m_mtx_FrameBuffer.unlock();

				std::this_thread::sleep_for(std::chrono::seconds(1));

				if (m_terminate_cleaner) break;
			}
		});

		m_terminate_counter = false;
	}
	
	Mat getFrame() {
		Mat res;
		m_mtx_FrameBuffer.lock();
		if (!m_vFrameBuffer.empty()) res = m_vFrameBuffer.front().clone();
		m_mtx_FrameBuffer.unlock();
		return res;
	}
	
	void stop() {
		m_terminate_producer = true;
		m_thr_producer.join();

		m_terminate_cleaner = true;
		m_thr_cleaner.join();

		m_terminate_counter = true;
		m_thr_counter.join();

		m_camera.release();
	}


private:
	VideoCapture	m_camera;
	std::deque<Mat> m_vFrameBuffer;
	std::mutex		m_mtx_FrameBuffer;
	
	// Producer
	std::thread m_thr_producer;
	bool		m_terminate_producer;

	// Cleaner
	std::thread m_thr_cleaner;
	bool		m_terminate_cleaner;
	
	// Counter
	std::thread m_thr_counter;
	bool		m_terminate_counter;


};