#ifndef __zthread_h__
#define __zthread_h__

#include<pthread.h>

class ZThread {
  public:
    ZThread();
    virtual ~ZThread();
    int start();
    int join();
    int detach();
    pthread_t self();
    virtual void run() = 0;
  private:
    pthread_t _tid;
    int _running;
    int _detach;
};

#endif
