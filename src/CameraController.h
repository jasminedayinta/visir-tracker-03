#pragma once

#include "types.h"

class CCameraCantroller {
public:
	CCameraCantroller(void) = default;
	~CCameraCantroller(void) = default;

	void init(void);
	void start(void);
	Mat getFrame(void) const;
	void stop(void);


private:
	VideoCapture		m_camera;
	std::deque<Mat> 	m_vFrameBuffer;
	mutable std::mutex	m_mtx_FrameBuffer;
	
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
