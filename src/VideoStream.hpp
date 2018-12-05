#pragma once

#include "ThreadClass.hpp"
#include <cv.h>
#include "opencv2/opencv.hpp"
#include "GraphicsHandler.h"

using namespace cv;

class VideoStream : public I_ThreadClass
{
public:
    VideoStream();
    void signalToQuit();
    bool initSetting(SDL_Rect inputRect, int inputDevice, int cameraHeight, int cameraWidth);
    bool update(GraphicsHandler* graphicsHandler);
    IplImage* getFrame();
    void rebootCamera();
    void resizeVideoRect(SDL_Rect newRect);

protected:
    void ThreadFunction();

    //TODO: old convention of m_ being member variable switch to tailing _.
private:
    bool imageReady();

    IplImage threadImage1_;
    IplImage threadImage2_;
    IplImage threadImage3_;
    Mat frame_;
    SDL_Rect videoRect_;
    VideoCapture cap_;
    bool quit_;
    bool updateImage_;
    bool noDevice_;
    int inputDevice_;
    int bufferNumber_;
};
