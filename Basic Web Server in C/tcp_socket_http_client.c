#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define IP "142.251.42.3" /* www.google.se */
#define PORT 80 /* http */

int main()
{
  int s;
  char buf[512];
  char *data;

  data = "HEAD / HTTP/1.0\n\n";

  struct sockaddr_in sock; 
  sock.sin_addr.s_addr = inet_addr(IP);/* Convert IP string to binary */
  sock.sin_port = htons(PORT);/* Convert port number to network byte order */
  sock.sin_family = AF_INET; /* Specify address family as IPv4 */

  s = socket(AF_INET, SOCK_STREAM, 0);

  if(s<0)
  {
    printf("socket() error\n");
    return -1;
  }

  if(connect(s, (struct sockaddr *)&sock, sizeof(struct sockaddr_in))!=0)
  {
    printf("connect() error\n");
    close(s);
    return -1;
  }

  write(s, data, strlen(data));
  read(s, buf, 511);
  close(s);
  printf("\n%s\n", buf);

  return 0;
}
