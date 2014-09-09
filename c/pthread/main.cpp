#include "ZThread.h"
#include <stdio.h>
#include <unistd.h>
class T1 : public ZThread {
  void run() {
    for(int i = 0; i < 100; ++i) {
      //sleep(1);
      printf("T1\n");
    }
  }
};
class T2 : public ZThread {
  void run() {
    for(int i = 0; i < 100; ++i) {
      //sleep(1);
      printf("T2\n");
    }
  }
};
int main() {
  T1 t1;
  T2 t2;
  t1.start();
  t2.start();
  t1.join();
  t2.join();
  return 0;
}
