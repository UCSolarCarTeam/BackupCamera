#include "videoStream.hpp"


VideoStream::VideoStream()
{
    bufferNumber_ = 1;
    updateImage_ = false;
    quit_ = false;
}

bool VideoStream::initSetting(SDL_Rect inputRect, int inputDevice, int cameraHeight, int cameraWidth)
{
    videoRect_ = inputRect;
    inputDevice_ = inputDevice;
    cap_ = VideoCapture(inputDevice_);
    cap_.set(CV_CAP_PROP_FRAME_WIDTH, cameraWidth);
    cap_.set(CV_CAP_PROP_FRAME_HEIGHT, cameraHeight);

    if (!cap_.isOpened())
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool VideoStream::update(GraphicsHandler* graphicsHandler)
{
    if (imageReady())
    {
        IplImage* img = NULL;
        img = getFrame();
        SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*)img->imageData,
                               img->width,
                               img->height,
                               img->depth * img->nChannels,
                               img->widthStep,
                               0xff0000, 0x00ff00, 0x0000ff, 0
                                                       );
        graphicsHandler->draw(surface, videoRect_, false, true);
        SDL_FreeSurface(surface);
        return true;
    }

    return false;
}

void VideoStream::signalToQuit()
{
    quit_ = true;
}

// This is the only function that is threaded
// The purpose of threading this is because `cap.read()`
// takes a while to read the camera. And while it's reading
// from the camera, we can spend time on the main thread calling
// `RenderCopyEx()` and `RenderPresent()`. This increases framerates.
//
// To avoid blocking on the threads using a mutex to read from the `threadImageX`
// We decided that it'd be worth introducing a small amount of latency, but making it
// pretty race proof by using triple buffering.
//
// In hindsight, http://lazyfoo.net/tutorials/SDL/42_texture_streaming/index.php might
// give a good solution to our problem with streaming.
void VideoStream::ThreadFunction()
{
    while (!quit_)
    {

        // This function takes a while to return
        // It is also the only reason why we have threading
        cap_.read(frame_);

        switch (bufferNumber_)
        {
            case 1:
                threadImage2_ = frame_;
                bufferNumber_ = 2;
                break;

            case 2:
                threadImage3_ = frame_;
                bufferNumber_ = 3;
                break;

            case 3:
                threadImage1_ = frame_;
                bufferNumber_ = 1;
                break;
        }

        updateImage_ = true;
    }
}

bool VideoStream::imageReady()
{
    return updateImage_;
}

IplImage* VideoStream::getFrame()
{
    updateImage_ = false;

    switch (bufferNumber_)
    {
        case 1:
            return &threadImage1_;

        case 2:
            return &threadImage2_;

        case 3:
            return &threadImage3_;

        default:
            //Shouldn't get here
            return NULL;
    }
}

void VideoStream::resizeVideoRect(SDL_Rect newRect)
{
    videoRect_ = newRect;
}
