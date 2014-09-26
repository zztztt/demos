#include "event.h"
#include "net.h"

int call_back(void *arg, int sign) {
  printf("call back %d\n", sign);
  return 1;
}

int main() {
  int listenfd = TcpServerConnect("127.0.0.1", 9876);
  struct event *ev = event_create(10, &call_back);
  event_ctl_add(ev, listenfd, EVENT_READ);
  while(true) {
    event_poll(ev, 1000);
  }
  return -1;
}
