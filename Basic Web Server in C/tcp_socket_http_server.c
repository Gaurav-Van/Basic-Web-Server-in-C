#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 8181 /* http */

int main()
{
  int s, c;
  char buf[512];
  char *data;
  int reading_data_size;

  socklen_t addrlen;
  struct sockaddr_in srv, cli;
  addrlen = sizeof(cli);
  memset(&srv, 0, sizeof(srv));
  memset(&cli, 0, sizeof(cli));

  srv.sin_addr.s_addr = 0;/* Convert IP string to binary */
  srv.sin_port = htons(PORT);/* Convert port number to network byte order */
  srv.sin_family = AF_INET; /* Specify address family as IPv4 */

  s = socket(AF_INET, SOCK_STREAM, 0);

  if(s<0)
  {
    printf("socket() error\n");
    return -1;
  }

  if(bind(s, (struct sockaddr *)&srv, sizeof(srv)))
  {
    printf("bind() error\n");
    close(s);
    return -1;
  }

  if(listen(s, 5))
  {
    printf("listen()\n");
    close(s);
    return -1;
  }

  printf("Listening on 127.0.0.1:%d\n", PORT);

  c = accept(s, (struct sockaddr *)&cli, &addrlen);

  if(c<0)
  {
    printf("accept()\n");
    close(s);
    return -1;
  }

  printf("Client Connected\n");
  reading_data_size = read(c, buf, 511);
  write(1, buf, reading_data_size);
  printf("\n----------------------------------------\n");
  write(1, buf, reading_data_size);


  close(c);
  close(s);

  return 0;
}

