#include "videoStream.hpp"


VideoStream::VideoStream()
{
    m_bufferNumber = 1;
    m_updateImage = false;
    m_quit = false;
}

bool VideoStream::init_setting(SDL_Rect input_rect, int input_device, int camera_height, int camera_width)
{
    video_rect_ = input_rect;
    m_input_device = input_device;
    cap = VideoCapture(m_input_device);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, camera_width);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, camera_height);

    if (!cap.isOpened())
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool VideoStream::update(GraphicsHandler* graphics_handler_)
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
        graphics_handler_->draw(surface, video_rect_, false, true);
        SDL_FreeSurface(surface);
        return true;
    }

    return false;
}

void VideoStream::signalToQuit()
{
    m_quit = true;
}

void VideoStream::ThreadFunction()
{
    while (!m_quit)
    {
        cap.read(m_frame);

        switch (m_bufferNumber)
        {
            case 1:
                m_threadImage2 = m_frame;
                m_bufferNumber = 2;
                break;

            case 2:
                m_threadImage3 = m_frame;
                m_bufferNumber = 3;
                break;

            case 3:
                m_threadImage1 = m_frame;
                m_bufferNumber = 1;
                break;
        }

        m_updateImage = true;
    }
}

bool VideoStream::imageReady()
{
    return m_updateImage;
}

IplImage* VideoStream::getFrame()
{
    m_updateImage = false;

    switch (m_bufferNumber)
    {
        case 1:
            return &m_threadImage1;

        case 2:
            return &m_threadImage2;

        case 3:
            return &m_threadImage3;

        default:
            //Shouldn't get here
            return NULL;
    }
}



void VideoStream::resizeVideoRect(SDL_Rect new_rect)
{
    video_rect_ = new_rect;
}
