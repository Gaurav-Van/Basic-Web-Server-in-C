#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LISTENADDR "0.0.0.0"

char *error;

struct sHttpRequest {
  char method[8];
  char url[128];
};
typedef struct sHttpRequest httpreq;

struct sFile
{
  char filename[64];
  char *fc; /*file content*/
  int size;
};
typedef struct sFile File;

/*srv = server and cli = client*/

/*
 Basic Flow - Binds server socket with IP and PORT. Connects the client socket based on configurations used in server socket. 
              Listens to client request [which is stored in buf], parse it to get the appropriate data like methods, url and etc,.
              Based on that data perform routing [based on the URL extracted, check the url and allow the content to be visible on that url] 
              or sends out the response [ writes into the headers and response functions ]. 
 */

/*
 Functions Used 

 srv_init() = initializes the server socket and binds it with IP and PORT. So that it is ready for listenning.
 cli_accept() = connects the client socket based on the configurations set in server socket. Client then can send request which will be heard by server. 

 cli_read() = reads the data which was send by the client to the server in the request like method or url and writes it into buffer. 
 parse_http() = parses the http request to get the Method and URL which was send during the request. Uses the concept of pointers and pointer arithematic for parsing.
 
 http_headers() = function used to define the response headers and then write it into the client socket.
 http_response() = function used to write the response with appropriate content type and content length to the client socket. 

 readfile(): Reads the contents of a file into a `File` structure. It allocates memory for the file content and returns a pointer to the `File` structure. 
              If reading fails, it returns 0.
 sendfile()`: Sends the content of a file to the client socket. It writes the file content in chunks and returns 1 on success or 0 if an error occurs.

 cli_conn() = the main client connection where reading client request data and its parsing is called. After Method and URL is extracted from the request, The Method and URL 
              are checked and if conditions are true then the content on that URL is displayed.if not then 404 is sent. Content is sent using http_headers and http_response func.
              Content is sent using the write() function which writes the data to the client socket. 
              Its under fork() so that it can handle multiple requests

*/

int srv_init(int portno)
{
  int s;
  s = socket(AF_INET, SOCK_STREAM, 0);
  if(s<0)
  {
    error = "socket() error";
    return 0;
  }
  struct sockaddr_in srv;
  srv.sin_family = AF_INET;
  srv.sin_addr.s_addr = inet_addr(LISTENADDR);
  srv.sin_port = htons(portno);

  if(bind(s, (struct sockaddr *)&srv, sizeof(srv)))
  {
    error = "bind() error";
    close(s);
    return 0;
  }

  if(listen(s, 5))
  {
    error="listen() error";
    close(s);
    return 0;
  }

  return s;
}

int cli_accept(int s)
{
  int c;
  socklen_t addrlen;
  struct sockaddr_in cli;

  addrlen = sizeof(cli);
  memset(&cli, 0, sizeof(cli));
  c = accept(s, (struct sockaddr *)&cli, &addrlen);
  if(c<0)
  {
    error = "accept() error";
    return 0;
  }

  return c;
}

httpreq *parse_http(char *str)
{
  httpreq *req;
  char *flag;

  req = malloc(sizeof(httpreq));
  memset(req, 0, sizeof(httpreq));

  for(flag=str; *flag && *flag!=' '; flag++);

  if(*flag == ' ')
  {
    *flag = 0;
  }
  else
  {
    error = "parse_http() NOSPACE error";
    free(req);
    return 0;
  }

  strncpy(req->method, str, 7);

  flag = flag+1;
  str = flag;

  for(flag; *flag && *flag!=' '; flag++);

  if(*flag == ' ')
  {
     *flag = 0;
  }
  else
  {
     error = "parse_http() NOSPACE error";
     free(req);
     return 0;
  }

  strncpy(req->url, str, 127);

  return req;
}

char *cli_read(int client)
{
  static char buf[512];
  memset(buf, 0, 512);
  
  if(read(client, buf, 511)<0)
  {
    error = "read() error";
    return 0;
  }
  else 
  {
    return buf;
  }
}

void http_headers(int c, int code)
{
  char buf[512];
  int n;
  memset(buf, 0, 512);

  snprintf(buf, 511, 
           "HTTP/1.0 %d OK\n"
           "Server: httpd_web_server.c\n"
           "Cache-Control: no-store, no-cache, max-age=0, private\n"
           "Content-Language: en\n"
           "Expires: -1\n"
           "X-Frame-Options: SAMEORIGIN\n", code);
  n = strlen(buf);
  write(c, buf, n);
  return;
}

void http_response(int c, char *contenttype, char *data)
{
  char buf[512];
  int n;
  n = strlen(data);
  memset(buf, 0, 512);
  snprintf(buf, 511,
           "Content-Type: %s\n"
           "Content-Length: %d\n"
           "\n%s\n", contenttype, n, data);

  write(c, buf, strlen(buf));
  return; 
}

File *readfile(char *filename)
{
  char buf[512];
  char *p;
  int n, x, fd;
  File *f;

  fd = open(filename, O_RDONLY);
  if(fd<0)
  {
    printf("\n\n Cannot OPEN FILE");
    return 0;
  }

  f = malloc(sizeof(struct sFile));
  if(!f)
  {
    printf("\n\n Cannot Allocate Data 'f = malloc()'");
    close(fd);
    return 0;
  }

  strncpy(f->filename, filename, 63);
  f->fc = malloc(512);

  x=0;
  while(1)
  {
    memset(buf, 0, 512);
    n = read(fd, buf, 512);
    if(!n)
    {
      break;
    }
    else if(x==-1)
    {
      close(fd);
      free(f->fc);
      free(f);
      return 0;
    }
    memcpy((f->fc)+x, buf, n);
    x += n;
    f->fc = realloc(f->fc, (512+x));
  }
  f->size = x;
  close(fd);
  return f;
}

int sendfile(int c, char *contenttype, File *file)
{
  char buf[512];
  char *p;
  int n, x;

  if(!file)
  {
    return 0;
  }

  memset(buf, 0, 512);
  snprintf(buf, 511, 
           "Content-Type: %s\n"
           "Content-Length: %d\n\n",
           contenttype, file->size);

  n = strlen(buf);
  write(c, buf, n);

  n = file->size;
  p = file->fc;
  while(1)
  {
    x = write(c, p, (n < 512)?n:512);
    if(x<1)
    {
      return 0;
    }

    n  = n - x;
    if(n<1)
    {
      break;
    }
    else 
   {
      p = p+x;
   }
  }

  return 1;
}

void cli_conn(int server, int client)
{
  httpreq *req;
  char *p;
  char *res;
  char path[180];
  File *f;

  p = cli_read(client);
  if(!p)
  {
    fprintf(stderr, "%s\n", error);
    close(client);
    return;
  }

  req = parse_http(p);
  if(!req)
  {
    fprintf(stderr,"%s\n", error);
    free(req);
    close(client);
    return;
  }

  if(!strcmp(req->method, "GET") && !strncmp(req->url, "/img/", 5))
  {
    if(strstr(req->url, ".."))
    {
      http_headers(client, 300);
      res = "Access Denied";
      http_response(client, "text/plain", res);
    }
    memset(path, 0, 180);
    snprintf(path, 179, "/home/capybara/C/httpd-web-server%s", req->url);
    printf("Requested file path: %s\n", path);
    f = readfile(path);
    if(!f)
    {
      res = "Image File not Found";
      http_headers(client, 404);
      http_response(client, "text/plain", res); 
    }
    else
    {
      if(!sendfile(client, "image/png", f))
      {
        res = "HTTP SERVER ERROR";
        http_headers(client, 500);
        http_response(client, "text/plain", res);
      }
      else 
      {
        printf("IMAGE FOUND\n\n");
        http_headers(client, 200);
      }
    }
  }
  else if(!strcmp(req->method, "GET") && !strcmp(req->url, "/app/image"))
  {
    res = "<html><head><title>Web Server in C</title></head><body><img src='/img/test.png' alt='image'><p>THIS ROUTE SENDS THE IMAGE TO THE USER</p></body></html>";
    http_headers(client, 200);
    http_response(client, "text/html", res);
  }
  else if(!strcmp(req->method, "GET") && !strcmp(req->url, "/app/webpage"))
  {
    res = "<html><head><title>Web Server in C</title></head><body><h1>Welcome to My Web Server</h1><p>This is a simple web server implemented in C.</p></body></html>";
    http_headers(client, 200);
    http_response(client, "text/html", res);
  }
  else 
  {
    res = "File not Found /app/webpage";
    http_headers(client, 404);
    http_response(client, "text/plain", res);
  }

  free(req);
  close(client);

  return;
}


int main(int argc, char *argv[])
{
  int s, c;
  char *port;
  
  if(argc < 2)
  {
    fprintf(stderr, "Required: %s <listening port> \n", argv[0]);
    return -1;
  }
  else
  {
    port = argv[1];
  }

  s = srv_init(atoi(port));
  if(!s)
  {
    fprintf(stderr, "%s\n", error);
    return -1;
  }
  printf("Listening on %s:%d\n", LISTENADDR, atoi(port));

  while(1)
  {
    c = cli_accept(s);
    if(!c)
    {
      fprintf(stderr, "%s\n", error);
      continue;
    }
    printf("Incoming Connection\n");
    if(!fork())
    {
      /*for the main process: return the new process id 
       * for the new process: return 0*/
      cli_conn(s, c);
    }
  }

}
