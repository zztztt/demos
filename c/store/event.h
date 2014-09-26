#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define EVENT_READ 1
#define EVENT_WRITE 2
#define EVENT_ERR 4

typedef int (*event_cb_t)(void *, int);
struct event {
  int fd;
  struct epoll_event *event;
  int nevent;
  event_cb_t cb;
};

struct event *event_create(int nevent, event_cb_t cb);
int event_ctl_add(event * ev, int fd, int mask);
int event_ctl_mod(event * ev, int fd, int mask);
int event_ctl_del(event * ev, int fd, int mask);
int event_poll(struct event *ev, int timeout);
void event_loop(event *ev);

