#ifndef I_THREADCLASS_H
#define I_THREADCLASS_H

#include <thread>

class I_ThreadClass
{
public:
    I_ThreadClass() { }
    virtual ~I_ThreadClass() { }

    bool StartThread()
    {
        if (pthread_create(&threadTracker_, NULL, ThreadReference, this) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void WaitForThreadToExit()
    {
        pthread_join(threadTracker_, NULL);
    }

protected:
    /** Anything inheriting this class must define this function */
    virtual void ThreadFunction() = 0;

private:
    static void* ThreadReference(void* threadId)
    {
        ((I_ThreadClass*)threadId)->ThreadFunction();
        return NULL;
    }

    pthread_t threadTracker_;
};
#endif
