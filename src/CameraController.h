#pragma once

#include "types.h"

class CCameraCantroller {
public:
    CCameraCantroller(size_t buf_len) : m_vFrameBuffer(buf_len) {}
    ~CCameraCantroller(void) = default;

    void    init(void);
    void    start(void);
    Mat        getFrame(void);
    void    stop(void);


private:
    VideoCapture        m_camera;
    std::deque<Mat>     m_vFrameBuffer;
    std::mutex            m_mtx_FrameBuffer;

    size_t                m_inFrameCounter = 0;
    size_t                m_outFrameCounter = 0;
    size_t                pointer_in = 0;
    size_t                pointer_out = 0;
    
    // Producer
    std::thread m_thr_producer;
    bool        m_terminate_producer;
    
    // Counter
    std::thread m_thr_counter;
    bool        m_terminate_counter;


};
