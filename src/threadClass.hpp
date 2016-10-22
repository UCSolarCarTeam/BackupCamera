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
        if (pthread_create(&thread_tracker, NULL, ThreadReference, this) == 0)
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
        pthread_join(thread_tracker, NULL);
    }



protected:
    /** Anything inheriting this class must define this function */
    virtual void ThreadFunction() = 0;

private:
    static void* ThreadReference(void* thread_id)
    {
        ((I_ThreadClass*)thread_id)->ThreadFunction();
        return NULL;
    }

    pthread_t thread_tracker;
};
#endif
