#include "net.h"

void setnonblocking(int fd) {
  int opts;
  opts = fcntl(fd, F_GETFL);
  if (opts < 0) {
    printf("fcntl(fd, F_GETFL)\n");
    return;
  }
  opts = opts | O_NONBLOCK;
  if (fcntl(fd, F_SETFL, opts) < 0) {
    printf("fcntl(fd, F_SETFL, opts)\n");
    return;
  }
}
int TcpServerConnect(char *addr, int port) {
  struct sockaddr_in servaddr;
  int listenfd;
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr(addr);
  servaddr.sin_port = htons(port);
  bind(listenfd, (sockaddr*) &servaddr, sizeof(servaddr));
  listen(listenfd, LISTENQ);
  return listenfd;
}
