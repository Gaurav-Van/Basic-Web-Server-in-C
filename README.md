# Basic Web Server in C and Rust

The provided C program implements a simple HTTP web server that listens for client connections, processes HTTP requests, and serves files or responses based on the request. The server supports serving static image files and a basic HTML page. 
It is designed to handle multiple client connections by using the fork() system call.

**This implementation was created primarily as a practice exercise with sockets. As a result, the server is very basic and limited in functionality, focusing on fundamental socket concepts in C Language**

The provided Rust code implements a basic multithreaded HTTP web server using a custom thread pool for handling concurrent connections. The `ThreadPool` structure manages a pool of worker threads, each of which processes incoming jobs. The server listens on port 8080 for client connections and delegates request handling to the thread pool. Each connection is processed in a separate thread, which reads the request, determines the appropriate response based on the request path, and serves either an HTML page or handles a sleep delay for a simulated latency response. This approach demonstrates fundamental concepts of concurrent programming and basic HTTP handling in Rust.

**This implementation is derived from examples in the official Rust programming book, which showcases the practical use of threading and synchronization in Rust. The book's exercises aim to teach core Rust concepts such as concurrency, error handling, and channel-based communication**

<hr>

## Structure

```bash
.
└── Basic Web Server in C/
    ├── httpd-web-server/
    │   ├── img/
    │   │   └── test.png # image which is sent as a response on one of the routes
    │   ├── httpd_web_server # Output File 
    │   └── httpd_web_server.c # C File of the Code of Basic Web Server
    ├── tcp_http_client # Output File of tcp_socket_http_client 
    ├── tcp_http_server # Output File of tcp_socket_http_server
    ├── tcp_socket_http_client.c # C File which uses socket programming to connect client with the server and allows the flow of request
    ├── tcp_socket_http_server.c # C File which uses socket programming to bind server with IP Address and PORT and allows the server to listen
    └── Revision of C.md # Markdown file that contains information or notes on some intermediate topics of C language.

.
└── Basic Web Server in Rust /
    ├── web_server/
    │   ├── 404.html # html page as a response if request other than GET is received
    │   ├── index.html # html page as a response if GET request is received
    │   ├── Cargo.lock 
    │   ├── Cargo.toml
    │   └── src/
    │       ├── lib.rs
    │       └── bin/
    │           └── main.rs
    └── minigrep/
        ├── Cargo.lock
        ├── poem.txt # example file used in order to extract text from it using terminal
        ├── Cargo.toml
        └── src/
            ├── lib.rs
            └── main.rs
```

<hr>

## Key Components

#### C

- **Server Initialization (srv_init):** Initializes and binds the server socket to an IP address and port, preparing it for listening.

- **Client Connection (cli_accept):** Accepts incoming client connections, creating a new socket for each client.

- **HTTP Request Parsing (parse_http):** Parses the HTTP request to extract the HTTP method and URL.

- **Client Request Reading (cli_read):** Reads the HTTP request data from the client socket into a buffer.

- **HTTP Response Header (http_headers):** Constructs and sends the HTTP response headers to the client.

- **HTTP Response Body (http_response):** Sends the HTTP response body, including content type and length, to the client.

- **File Reading (readfile):** Reads the contents of a file into memory, handling file I/O operations.

- **Send File (sendfile):** Sends a file's contents to the client, including appropriate headers.

- **Client Connection Handling (cli_conn):** Handles the client connection, including reading the request, parsing it, and sending back the appropriate response based on the request URL.

- **Main Function (main):** Entry point of the server program, initializes the server, and continuously accepts and processes client connections.

#### Rust

* **ThreadPool Initialization (`ThreadPool::new`):** Initializes a thread pool with a specified number of worker threads. It sets up a channel for sending jobs to the workers and starts each worker thread to continuously receive and execute jobs from the channel.

* **Job Execution (`ThreadPool::execute`):** Adds a new job to the thread pool by sending it through the channel. Each job is a closure that the worker threads will execute.

* **Worker Thread (`Worker::new`):** Creates a new worker thread that waits for jobs from the shared receiver channel. Upon receiving a job, the worker executes it. The worker continues to run until it detects that the channel has been disconnected.

* **Job Handling (`handle_connection`):** Processes incoming client connections by reading the request data, parsing it to determine the appropriate response, and sending back the response, which includes serving static HTML files or handling delays for specific requests.

* **HTTP Request Parsing (`handle_connection`):** Extracts the HTTP request line from the buffer to determine the requested resource. It matches the request to predefined routes to generate the correct HTTP response.

* **File Reading (`handle_connection`):** Reads the content of requested files from the file system and prepares them for inclusion in the HTTP response.

* **HTTP Response Construction (`handle_connection`):** Constructs the HTTP response header and body, including content length and the actual file content, and sends it back to the client.

* **ThreadPool Shutdown (`ThreadPool::drop`):** Properly shuts down the thread pool by dropping the sender channel and joining all worker threads, ensuring that all threads complete their execution before the program exits.

* **Main Function (`main`):** Sets up the TCP listener on port 8080, initializes the thread pool, and continuously accepts incoming client connections, delegating each connection to the thread pool for processing.

* **Connection Handling (`handle_connection`):** Manages the lifecycle of each client connection, including reading the request, generating the response, and sending it to the client, all while being handled in a separate thread managed by the thread pool.

<hr>

## Topics

#### C

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

#### Rust

* Thread Pools
  * Thread Pool Initialization
  * Job Execution
  * Worker Threads
  * ThreadPool Shutdown
* Concurrency and Synchronization
  * Arc (Atomic Reference Counting)
  * Mutex (Mutual Exclusion)
* Channels
  * mpsc (Multi-Producer, Single-Consumer)
  * Sending and Receiving Messages
* Network Programming
  * TcpListener
  * TcpStream
  * Handling Incoming Connections
* File I/O
  * Reading Files
* HTTP Protocol Basics
  * Request Parsing
  * Response Construction
  * Status Lines and Headers
* Error Handling
  * Result Type
  * unwrap()

<hr>

## Typical Client-Server Scenario

* **Server:**
  * Create socket → Bind to address → Listen for connections → Accept connections.
* **Client:**
  * Create socket → Connect to server.
* **Communication:**
  * Use `send()` and `recv()` or `read()` and `write` to exchange data between the client and server after establishing the connection.

<hr>

 For C, all Thanks to <a href="https://www.youtube.com/@dr-Jonas-Birch">dr Jonas Birch</a>. His programming videos are some of the best I’ve seen on YouTube. His deep knowledge and clear teaching style makes him great. This web server is inspired by one of his project series. 

For Rust, The Official Rust Lang Book is really Good. 


