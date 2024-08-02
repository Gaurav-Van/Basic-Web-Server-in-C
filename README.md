# Basic Web Server in C
This C program implements a simple HTTP web server that listens for client connections, processes HTTP requests, and serves files or responses based on the request. The server supports serving static image files and a basic HTML page. 
It is designed to handle multiple client connections by using the fork() system call.

**This implementation was created primarily as a practice exercise with sockets. As a result, the server is very basic and limited in functionality, focusing on fundamental socket concepts in C Language**

<hr>

## Structure

``` bash
Basic Web Server in C/
│
├── httpd-web-server/
│   ├── img/
|   |   |── test.png     # image which is sent as a response on one of the routes 
|   | 
│   |── httpd_web_server    # Output File 
|   |── httpd_web_server.c  # C File of the Code of Basic Web Server
|
├── tcp_http_client     # Output File of tcp_socket_http_client 
│── tcp_http_server     # Output File of tcp_socket_http_server
│── tcp_socket_http_client.c   # C File which uses socket programming to connect client with the server and allows the flow of request
└── tcp_socket_http_server.c   # C File which uses socket programming to bind server with IP Address and PORT and allows the server to listen for requests

Revision of C.md   # Markdown file that contains information or notes on some intermediate topics of C language.

```

<hr>

## Key Components
1. **Server Initialization (srv_init):** Initializes and binds the server socket to an IP address and port, preparing it for listening.<br><br>
2. **Client Connection (cli_accept):** Accepts incoming client connections, creating a new socket for each client.<br><br>
3. **HTTP Request Parsing (parse_http):** Parses the HTTP request to extract the HTTP method and URL.<br><br>
4. **Client Request Reading (cli_read):** Reads the HTTP request data from the client socket into a buffer.<br><br>
5. **HTTP Response Header (http_headers):** Constructs and sends the HTTP response headers to the client.<br><br>
6. **HTTP Response Body (http_response):** Sends the HTTP response body, including content type and length, to the client.<br><br>
7. **File Reading (readfile):** Reads the contents of a file into memory, handling file I/O operations.<br><br>
8. **Send File (sendfile):** Sends a file's contents to the client, including appropriate headers.<br><br>
9. **Client Connection Handling (cli_conn):** Handles the client connection, including reading the request, parsing it, and sending back the appropriate response based on the request URL.<br><br>
10. **Main Function (main):** Entry point of the server program, initializes the server, and continuously accepts and processes client connections.

<hr>

## Topics 
* Pointers
* Pointers and Multi-Dimensional arrays
* Pointers and Dynamic Memory
* Pointers as Function returns
* Function Pointers
* `fork()`
* Common System API Types in C
* Sockets
  * Types of Sockets
  * Binding the Socket
  * Connection of the Socket `connect()`
  * Difference between bind and connect
  * Typical Client-Server Scenario
  * Listening for Connections
  * Accepting Connections
  * Sending and Receiving Data
  * Closing the Socket
* Struct `sockaddr_in`

<hr>

## Typical Client-Server Scenario 
* **Server:**
  * Create socket → Bind to address → Listen for connections → Accept connections.
* **Client:**
  * Create socket → Connect to server.
* **Communication:**
  * Use `send()` and `recv()` or `read()` and `write` to exchange data between the client and server after establishing the connection.

<hr>

All Thanks to <a href="https://www.youtube.com/@dr-Jonas-Birch">dr Jonas Birch</a>. His programming videos are some of the best I’ve seen on YouTube. His deep knowledge and clear teaching style makes him great. This web server is inspired by one of his 
project series. 

