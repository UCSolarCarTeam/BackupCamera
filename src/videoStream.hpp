#pragma once

#include "threadClass.hpp"
#include <cv.h>
#include "opencv2/opencv.hpp"
#include "graphics_handler.h"

using namespace cv;

class VideoStream : public I_ThreadClass
{
public:
    VideoStream();
    void signalToQuit();
    bool init_setting(SDL_Rect input_rect, int input_device, int camera_height, int camera_width);
    bool update(GraphicsHandler* graphics_handler_);
    IplImage* getFrame();
    void reboot_camera();
    void releaseCaptureDevice();
    void resizeVideoRect(SDL_Rect new_rect);

protected:
    void ThreadFunction();

    //TODO: old convention of m_ being member variable switch to tailing _.
private:
    IplImage m_threadImage1;
    IplImage m_threadImage2;
    IplImage m_threadImage3;
    Mat m_frame;
    SDL_Rect video_rect_;
    VideoCapture cap;

    bool imageReady();



    bool m_quit;
    bool m_updateImage;
    bool no_device;
    int m_input_device;
    int m_bufferNumber;
};
