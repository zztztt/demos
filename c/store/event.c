#include "event.h"
struct event *event_create(int nevent, event_cb_t cb) {
  struct event *ev;
  struct epoll_event *epev;
  int fd;
  fd = epoll_create(nevent);
  if (fd < 0) {
    printf("[ERROR] call epoll_create error\n");
    return NULL;
  }
  // 
  epev = (epoll_event*)malloc(sizeof(*epev) * nevent);
  if (epev != NULL) {
    memset(epev, 0, sizeof(*epev) * nevent);
  } else {
    printf("[ERROR] epoll epev malloc error\n");
    close(fd);
    return NULL;
  }
  //
  ev = (event*)malloc(sizeof(*ev));
  if (ev == NULL) {
    printf("[ERROR] event malloc  error\n");
    free(ev);
    close(fd);
    return NULL;
  }
  ev->fd = fd;
  ev->event = epev;
  ev->nevent = nevent;
  ev->cb = cb;
  printf("[DEBUG] event create fd %d with nevent %d\n", ev->fd, ev->nevent);
  return ev;
}

int event_poll(struct event *ev, int timeout) {
  int fd = ev->fd;
  struct epoll_event *epev = ev->event;
  int nevent = ev->nevent;
  if (ev->cb == NULL) {
    printf("[ERROR] event callback is null\n");
    return -1;
  }
  for (;;) {
    int i, nsd;
    nsd = epoll_wait(fd, epev, nevent, timeout);
    printf("epoll wait on %d with %d events returned %d events\n", fd, nevent, nsd);
    if (nsd > 0) {
      for (i = 0; i < nsd; ++i) {
        struct epoll_event *epev_i = &ev->event[i];
        uint32_t events = 0;
        printf("[DEBUG] epoll triggered");
        if (epev_i->events & EPOLLERR) {
          events |= EVENT_ERR;
        } 
        if (epev_i->events & (EPOLLIN | EPOLLHUP)) {
          events |= EVENT_READ;
        }
        if (epev_i->events & EPOLLOUT) {
          events |= EVENT_WRITE;
        }
        ev->cb(epev_i->data.ptr, events);
      }
      return nsd;
    } else if (nsd == 0) {
      if (timeout == -1) {
        return -1;
      }
    } else {
      return -1;
    }
  }

}

int event_ctl_add(event *ev, int fd, int mask) {
  struct epoll_event epev;
  epev.data.fd = fd;
  if (mask & EVENT_READ) epev.events |= EPOLLIN|EPOLLET;
  if (mask & EVENT_WRITE) epev.events |= EPOLLOUT;
  epoll_ctl(ev->fd, EPOLL_CTL_ADD, fd, &epev);
  return 1;
}
int event_ctl_mod(event *ev, int fd, int mask) {
  struct epoll_event epev;
  epev.data.fd = fd;
  if (mask & EVENT_READ) epev.events |= EPOLLIN;
  if (mask & EVENT_WRITE) epev.events |= EPOLLOUT;
  epoll_ctl(ev->fd, EPOLL_CTL_MOD, fd, &epev);
  return 1;
}
int event_ctl_del(event *ev, int fd, int mask) {
  struct epoll_event epev;
  epev.data.fd = fd;
  if (mask & EVENT_READ) epev.events |= EPOLLIN;
  if (mask & EVENT_WRITE) epev.events |= EPOLLOUT;
  epoll_ctl(ev->fd, EPOLL_CTL_DEL, fd, &epev);
  return 1;
} 
void event_loop(event *ev) {
  while(true) {
    event_poll(ev, 20);
  }
}

