#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 1000
#define SERV_PORT 9999

void processing(int sock, struct sockaddr_in cliaddr)
{
  int n;
  char str[INET_ADDRSTRLEN];
  char *buf = (char*)malloc(MAXLINE);
  memset(buf,'\0', MAXLINE);
  while(1)
  {
    n = read(sock, buf, MAXLINE);
    if (n < 0)
    {
      perror("ERROR READ SOCKET");
      exit(-1);
    }
    else
    {
      printf("Connect from %s, %d\n",inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));
      write(sock, "Get message!", 20);
    }
  }
  free(buf);
}

int main()
{
  struct sockaddr_in servaddr, cliaddr;
  int listenfd, connfd, pid;
  socklen_t cliaddr_len = sizeof(cliaddr);
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd < 0)
  {
    perror("ERROR OPEN SOCKET");
    exit(-1);
  }

  memset(&servaddr, 0, sizeof(struct sockaddr_in));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(SERV_PORT);

  bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
  listen(listenfd, 2000);
  printf("server : wait for client\n");
  while (1)
  {
    connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &cliaddr_len);
    pid = fork();
    if (pid == -1)
    {
      perror("call to fork error");
      exit(-1);
    }
    else if (pid == 0)
    {
      close(listenfd);
      processing(connfd, cliaddr);
      exit(0);
    }
    else
    {
      close(connfd);
    }

  }

  return 0;
}
