#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 80
#define SERV_PORT 9999
int main ()
{
  struct sockaddr_in servaddr;
  char *buf = (char*)malloc(MAXLINE);
  int servfd, n;
  servfd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(SERV_PORT);
  connect(servfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
  while (fgets(buf,MAXLINE, stdin) != NULL)
  {
    write(servfd, buf, strlen(buf));
    n = read(servfd, buf, MAXLINE);
    if (n == 0)
    {
      perror("ERROR SERVER CLOSED");
      exit(-1);
    }
    else
    {
      printf("From server info is %s", buf);
    }
  }
  close(servfd);

  return 0;
}

