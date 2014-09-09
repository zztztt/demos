#include "ZThread.h"

ZThread::ZThread() : _tid(0), _running(0), _detach(0) {}
ZThread::~ZThread() {
  if (_running == 1 && _detach == 0) {
    pthread_detach(_tid);
  }
  if (_running == 1) {
    pthread_cancel(_tid);
  }
}

static void* _run(void* arg) {
  ((ZThread*)arg)->run();
  return NULL;
}
int ZThread::start() {
  int result = pthread_create(&_tid, NULL, _run, this);
  if (result == 0) {
    _running = 1;
  }
  return result;
}

int ZThread::join() {
  int result = -1;
  if (_running == 1) {
    result = pthread_join(_tid, NULL);
    if (result != 0) {
      _detach = 0;
    }
  }
  return result;
}

int ZThread::detach() {
  int result = -1;
  if (_running == 1 && _detach == 0) {
    result = pthread_detach(_tid);
    if (result == 0) {
      _detach = 1;
    }
  }
  return result;
}

pthread_t ZThread::self() {
  return _tid;
}
