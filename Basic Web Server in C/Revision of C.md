# Revision of C

<hr>

### Table of Contents

- How `rand` works 

- Pointers

- Pointers and Multi-Dimensional arrays

- Pointers and Dynamic Memory 

- Pointers as Function returns 

- Function Pointers

- `fork()`

- Ncurses

- select() 

- Common System API Types in C

- Sockets 
  
  - Types of Sockets 
  - Binding the Socket 
  - Connection of the Socket `connect()`
  - Difference between bind and connect
  - Typical Client-Server Scenario
  - Listening for Connections
  - Accepting Connections
  - Sending and Receiving Data
  - Closing the Socket

- Struct `sockaddr_in`

<hr>

## How `rand()` works:

1. **Pseudo-Random Number Generation**: The `rand()` function generates a sequence of numbers that appear random, but are actually deterministic. This means the sequence is based on an initial value called the seed.

2. **Seed Initialization**: In most implementations, the seed is initialized automatically by the system when the program starts. Often, this seed is based on the current time (in seconds) since the Unix epoch (January 1, 1970). This ensures that each time you run the program, the seed is different.

3. **Algorithm**: `rand()` typically uses a mathematical algorithm to generate the next number in the sequence based on the current seed. One common algorithm is a linear congruential generator (LCG), which uses the formula:
   next_value=(current_seed×a+c)modm
   where a, c, and m are constants chosen by the implementation.

### Why it's pseudo-random:

* **Deterministic Nature**: Since `rand()` relies on an initial seed and a deterministic algorithm, the sequence of numbers it generates is entirely determined by the seed and the algorithm. If you use the same seed, you'll get the same sequence of numbers every time.

* **Reproducibility**: This deterministic behavior is useful for debugging and testing because it allows programmers to reproduce issues that depend on random numbers.

### Why it gives the same value every time you run the file:

* **Seed Initialization**: If your program does not explicitly change the seed (by calling `srand()` with a different value), `rand()` will use the same seed every time the program runs.

* **Default Seed**: If the program does not call `srand()` explicitly, many C implementations initialize the seed based on a constant value (often 1). This results in the same sequence of numbers each time the program is executed.

### How to get different values:

* **Using `srand()`**: To get different sequences of random numbers in different runs of your program, you can use `srand()` to set a different seed before calling `rand()`. Common practice is to use `srand(time(NULL))`, which sets the seed based on the current time, ensuring a different sequence in each run. `We can also use getpid() which will act as a unique seed for srand(). srand(getpid())` 

<hr>

## Pointers

```
*Stack is a block of memory. One of the components of application memory.Whenever a main() function is invoked a **Stack frame**
is created which is somememory allocated to the execution of main function. Anything inside the main function that needs memory
will be given from the created **stack frame**.*

*If main functions call another function, space or another stack frame is given to that function. Just like properties of stack
which is LIFO, the newly created stack frame will be executed and below it will be paused untill it is finished or it returns
something*
```

### ***Basic Information of Pointers***

![image](https://github.com/user-attachments/assets/b95ed1a3-c9a9-4a8e-90d7-923719be7792)

***IMPORTANT*** - Points at the starting or least significant bit and then continues from that point to the relevant size.*

![image](https://github.com/user-attachments/assets/fdbf494b-c892-40a8-8785-15a1826bdb52)

![image](https://github.com/user-attachments/assets/ad3138a2-0908-4b36-bd8d-549fd96a553e)

![image](https://github.com/user-attachments/assets/bf4bf72e-a024-4361-89e0-353693f5c55d)

### **_call by value_**

![image](https://github.com/user-attachments/assets/b6f40292-0704-438e-8085-2ba88ad8d83d)

### ***call by reference***

![image](https://github.com/user-attachments/assets/3699e514-ac2b-468d-98f1-940b00824b1e)

### ***Pointers and Arrays***

The name of an array in C behaves like a constant pointer to the first element of the array.

![image](https://github.com/user-attachments/assets/dcf237cf-0380-4517-867c-2261346aac28)

***Arrays as function arguments***: **When compiler sees the array as function argument, It does not copy the whole array, it creates a pointer variable of the same data type and copies the address of the first element of the array**. [ as array name points to the address of first element of the array]. Arrays are always passed as reference parameters

![image](https://github.com/user-attachments/assets/c48f8c32-4eb4-401c-a758-bc4706deb953)

### ***Pointers and Strings / Character Arrays***

![image](https://github.com/user-attachments/assets/c9cc9998-1bcf-4fcc-bafd-ba37c35035f9)

A string in C needs to end in a null character. `\0`. It counts only till `\0` That's why size of character array = size of string + 1. *Similar to relation of numb arrays and pointers, the name of the char array points to the location of first character of string. Char Arrays are always passed to function by reference.*

![image](https://github.com/user-attachments/assets/4f870559-6887-4fbc-b5d8-35cb1f700d40)

<hr>

### Pointers and Multi-Dimensional arrays

In the case of 2-D Arrays MxN, The pointer returns the address of 1-D array of N integers. 

![image](https://github.com/user-attachments/assets/b60a5101-a7dc-4e2e-bdeb-a17a632afdb4)

**IMPORTANT**

```
In `*B` what happens is = Simple B gives us the address of the first element of the 2D Array which is just an 1D array of 3 integers
which will be the address of the first byte of that 1-D address because thats how pointer works normally. Now `*` will gives us the
value at that address which is the entire array B[0] and we know the array name points to the memory address of the first element
which will gives us the value of 400.
```
![image](https://github.com/user-attachments/assets/1230c7df-cc62-41ab-a433-0dcabec3d433)

![image](https://github.com/user-attachments/assets/76a31912-f228-4899-8bd8-30e2d04d1c68)

<hr>

### Pointers and Dynamic Memory

![image](https://github.com/user-attachments/assets/a4a58f3d-100f-4afa-aef1-b4fc4e66047f)

```
When programs exceeds the limilted space provided to stack then it is known as stackoverflow. Example: Non-Conditional recursion.
**PROBLEM WITH STACK**: No control over dynamic allocation of memory of variables, Not able to manipulate the scope of the variable,
Fixed memory which does not grow. TO SOLVE THIS WE HAVE **HEAP** . Heap = dynamic memory or free store. HEAP is not dependent, anything
allocated on the heap is not automatically deallocated when the function completes like on the stack and we can control the whole lifetime
```

#### **HEAP**

For Dynamic allocation of the memory for variables and operations. Allocating memory at run time. 

- **malloc** 
   The `malloc` function in C allocates a block of memory on the heap and **returns a pointer** to the beginning of that block. The address returned by `malloc` is the starting point of the allocated memory.
  The `malloc` function in C returns a `void*` pointer. This is a generic pointer type that can be converted to any other pointer type without an explicit cast.
  when using malloc we need to free the unused memory, it does not do it by itself,. We do it by using `free()`
  
  ```c
  int *p;
  p = (int*)malloc(sizeof(int)); /*(int*) typecasting is done because malloc returns a void pointer*/
  /*to fill value in that location - dereferencing*/
  *p = 10;
  free(p); 
  
  /*Storing Arrays*/
  p = (int*)malloc(20*sizeof(int)); /*This gives block size for 20 integers and gives us the starting addr*/
  *p /*which is equal to p[0]*/
  *(p+1) /*which is equal to p[1]*/
  ```

- **calloc**

        Similar functionalities of malloc but with difference. 

        `void* calloc(size_t num, size_t size)`. `(int*)calloc(3, sizeof(int))`

        `malloc()` assigns single block of requested memory,  
        `calloc()` assigns multiple blocks of the requested memory

        `malloc()`  doesn't clear and initialize the allocated memory.  
        `calloc()`  initializes the allocated memory by zero.

        `malloc()` is fast.  
        `calloc()` is slower than malloc().

- **realloc**
  The `realloc` function in C is used to resize a previously allocated block of memory. This can be useful when you need to change the size of a dynamic array or buffer after it has been initially allocated.
  
  ```c
  void* realloc(void* ptr, size_t new_size);
  ```
  
  * **`ptr`**: A pointer to the previously allocated memory block that you want to resize. This pointer must have been previously allocated by `malloc`, `calloc`, or `realloc`. If `ptr` is `NULL`, `realloc` behaves like `malloc` and allocates a new block of memory.
  * **`new_size`**: The new size of the memory block in bytes.
  
  Resizing
  
  * **Increasing Size**: If the new size is larger than the old size, `realloc` will allocate a larger block and copy the old data to the new block. The extra memory is uninitialized.
  * **Decreasing Size**: If the new size is smaller than the old size, `realloc` will reduce the size of the block, possibly freeing some of the memory. The data in the truncated part is lost.

- **free**
  The `free` function in C is used to deallocate memory that was previously allocated with `malloc`, `calloc`, or `realloc`. It is a crucial part of memory management in C, ensuring that dynamically allocated memory is properly released and made available for future use.
  **IMPORTANT**
  
  - **Pointer Invalidity**: After calling `free`, the pointer `ptr` becomes *invalid* known as dangling pointer. Accessing or dereferencing a freed pointer results in undefined behavior. The pointer itself is not set to `NULL` by `free`, so you should manually set it to `NULL` if you want to avoid accidental use.
  
  - `free` is essential for preventing **memory leaks**. A memory leak occurs when a program allocates memory but fails to deallocate it, leading to wasted memory and potential performance issues.

<hr>

### Pointers as Function returns

**ONE TIP:** Check the execution order of functions on stack for debugging. Also check what happens if they are over, the memory of them from stacks gets removed and is on high risk of being consumed by other function and getting overwritten.

**AVOID**: Calling Pointers as function returns in top-down manner in stack calls. which means avoid calling pointers as function returns from someother function which exist above it in stack calls. Danger of being overwritten. 

![image](https://github.com/user-attachments/assets/1977c2bd-c9f7-428d-ba9d-5966f81d9d1d)

<hr>

### Function Pointers

Pointers locating to the `address or entry point of the function`

`Name of the function also returns the pointer`

![image](https://github.com/user-attachments/assets/188a2bdc-fe31-44d2-b617-8cbccf88090f)

![image](https://github.com/user-attachments/assets/7be4e9c7-2c6e-425d-b0f4-46deb4b68cc5)

![image](https://github.com/user-attachments/assets/7c254bef-53c6-43b1-a263-fd7951271fec)

<hr>

## `fork()`

The `fork()` function in C is a system call used to create a new process, which is known as the child process. When `fork()` is called, it creates a duplicate of the calling process (the parent). Both processes will execute the next instruction following the `fork()` call. 

* **Negative Value**: Indicates that the creation of the child process failed.
* **Zero**: Returned to the newly created child process.
* **Positive Value**: Returned to the parent process, representing the process ID (PID) of the child process

###### Process Creation

The `fork()` function results in two processes:

1. **Parent Process**: The original process that called `fork()`.
2. **Child Process**: The new process created by `fork()`.

Both processes have their own separate address spaces, meaning that changes made to variables in one process do not affect the other. This separation is crucial for process isolation and stability

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // This block executes in the child process
        printf("Hello from Child! PID: %d\n", getpid());
    } else {
        // This block executes in the parent process
        printf("Hello from Parent! PID: %d, Child PID: %d\n", getpid(), pid);
    }

    return 0;
}
```

<hr>

## Ncurses

Ncurses (New Curses) is a library for creating text-based user interfaces in C. It provides a set of functions for manipulating the terminal screen, handling user input, and creating windows and menus.

### 1. Screens

When compiling, you must link against the Ncurses library using the `-lncurses` flag. Which means include `library ncurses` command  = `gcc ncurses.c -o ncurses -lncurses`

- `initscr()`: Initializes the Ncurses screen and allocates memory for the `stdscr` window

- `printw()`: Prints a string to the current window at the current cursor position

- `refresh()`: Updates the physical screen to match the contents of the virtual screen buffer

- `getch()`: Waits for and returns the next character entered by the user

- `endwin()`: Restores the terminal to its original state and frees Ncurses resources

```c
int main(){
    char letter;

    initscr();
    printw("Press any key");
    refresh();

    letter = getch();
    clear();
    printw("You Pushed: %c", letter);
    refresh();

    getch();
    endwith();

    return 0;
}
```

### 2. X and Y

In Ncurses, the concepts of X and Y coordinates are fundamental for positioning the cursor and displaying content on the terminal screen.

**Origin**: The coordinate system in Ncurses starts at the top-left corner of the screen, which is designated as (0, 0).

- **`move(int y, int x)`**: Moves the cursor to the specified Y and X coordinates. For example, `move(10, 20)` moves the cursor to row 10 and column 20.

- **`getyx(WINDOW *win, int *y, int *x)`**: This function retrieves the current cursor position in a specified window, storing the Y and X coordinates in the provided variables

```c
int main()
{
    int x, y;
    initscr();
    clear();

    getyx(stdscr, y, x);
    printw("X = %d \n Y = %d", x, y);
    refresh();

    x=5;
    y=10;
    move(y, x);
    printw("Over Here");
    refresh();

    getch();
    endwin();

    return 0;
}
```

* **`mvprintw(int y, int x, const char *str)`**: This function combines moving the cursor and printing a string in one call. For example, `mvprintw(10, 20, "Hello World!");` places "Hello World!" at the specified position.

### 3. Arrow

In Ncurses, arrow keys are represented by special key codes that are returned by the `getch()` function when the corresponding arrow key is pressed. 

**Enabling Keypad Mode**

Before you can detect arrow keys, you need to enable keypad mode using the `keypad()` function:

```c
keypad(stdscr, TRUE);
```

After enabling keypad mode, you can use `getch()` to read user input. When an arrow key is pressed, `getch()` will return one of the following key codes:

* `KEY_UP`: Up arrow key
* `KEY_DOWN`: Down arrow key
* `KEY_LEFT`: Left arrow key
* `KEY_RIGHT`: Right arrow key

```c
#include <ncurses.h>
#include <string.h>

int main(){

        int key, x, y;
        char keyPressed[11];

        initscr();
        keypad(stdscr, TRUE);
        noecho();
        x = y = 25;
        strncpy(keyPressed, "DEFAULT", 12);

        while(key!= 'q'){

        clear();
        mvprintw(0, 0, "Press Left or Right or UP or Down arrow - exit by pressing: q");
        mvprintw(y, x, "O---|");
        move(1,0);
        printw("---------- KEY PRESSED %s ---------------", keyPressed);
        refresh();

        key = getch();

        if (key == KEY_LEFT){

        x--;
        strncpy(keyPressed, "LEFT KEY", 12);
        if(x<0) x=0;
        }

        else if(key == KEY_UP){
        y--;
        strncpy(keyPressed, "UP KEY", 12);
        if(y<2) y=2;
        }

        else if(key == KEY_DOWN){
        y++;
        strncpy(keyPressed, "DOWN KEY", 12);
        if(y>60) y=60;
        }

        else if(key == KEY_RIGHT){
        x++;
        strncpy(keyPressed, "RIGHT KEY", 12);
        if (x>50) x=50;
        }
}
endwin();
return 0;
```

<hr>

## `select()`

`select()` is a system call used to monitor multiple file descriptors to see if they are ready for I/O operations. It is commonly used in network programming and other scenarios where you need to handle multiple input/output streams concurrently without using threads or non-blocking I/O.

`select()` allows a program to wait for events on multiple file descriptors (such as sockets or files) and respond accordingly when any of them become ready for some kind of I/O operation. It can monitor:

* Read readiness
* Write readiness
* Exceptional conditions (e.g., errors)

```c
#include <sys/select.h>

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
```

* **`nfds`**: The highest file descriptor number in any of the sets, plus one. It tells `select()` the size of the file descriptor sets. For example, if you are monitoring file descriptors 0, 1, and 2, you would set `nfds` to 3.

* **`readfds`**: A pointer to a `fd_set` structure that specifies the file descriptors to be checked for readability. This structure is modified by `select()` to indicate which file descriptors are ready for reading.

* **`writefds`**: A pointer to a `fd_set` structure that specifies the file descriptors to be checked for writability. This structure is modified by `select()` to indicate which file descriptors are ready for writing.

* **`exceptfds`**: A pointer to a `fd_set` structure that specifies the file descriptors to be checked for exceptional conditions (such as out-of-band data). This structure is modified by `select()` to indicate which file descriptors have exceptions.

* **`timeout`**: A pointer to a `struct timeval` specifying the maximum time `select()` should wait for an event. If `timeout` is `NULL`, `select()` will block indefinitely until an event occurs. If `timeout` is set to zero, `select()` will return immediately, performing a non-blocking check.

### How `fd_set` Works

`fd_set` is essentially a set data structure / array that can hold a fixed number of file descriptors. Operations on `fd_set` are done using macros:

* **`FD_ZERO(fd_set *set)`**: Initializes the set to be empty.
* **`FD_SET(int fd, fd_set *set)`**: Adds the file descriptor `fd` to the set.
* **`FD_CLR(int fd, fd_set *set)`**: Removes the file descriptor `fd` from the set.
* **`FD_ISSET(int fd, fd_set *set)`**: Checks if the file descriptor `fd` is in the set.

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>

int main() {
    fd_set readfds;
    struct timeval timeout;
    int retval;

    // Initialize the set of file descriptors
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds); // Monitor stdin (file descriptor 0)

    // Set timeout to 5 seconds
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    // Call select
    retval = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

    if (retval == -1) {
        perror("select()");
        exit(EXIT_FAILURE);
    } else if (retval == 0) {
        printf("No data within five seconds.\n");
    } else {
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            printf("Data is available on stdin.\n");
        }
    }

    return 0;
}

```

<hr>

## Common System API Types in C

* **`pid_t`**
  
  * **Purpose**: Represents process IDs.
  * **Usage**: Used in system calls that deal with processes, such as `fork()`, `getpid()`, `wait()`, and `kill()`.
  * **Example**: `pid_t pid = fork();`

* **`size_t`**
  
  * **Purpose**: Represents the size of objects in memory.
  * **Usage**: Used for array indexing and in functions like `malloc()`, `sizeof()`, and `strlen()`.
  * **Example**: `size_t length = sizeof(array) / sizeof(array[0]);`

* **`off_t`**
  
  * **Purpose**: Represents file sizes and file offsets.
  * **Usage**: Used in file operations to specify and retrieve file positions, often with functions like `lseek()` and `fseek()`.
  * **Example**: `off_t offset = lseek(fd, 0, SEEK_END);`

* **`mode_t`**
  
  * **Purpose**: Represents file mode (permissions and file types).
  * **Usage**: Used in functions like `chmod()` and `umask()` to set or retrieve file permissions.
  * **Example**: `mode_t mode = S_IRUSR | S_IWUSR | S_IXUSR;`

* **`fd_set`**
  
  * **Purpose**: Used to represent sets of file descriptors for I/O multiplexing.
  * **Usage**: Used with `select()` to monitor multiple file descriptors for readability, writability, or exceptions.
  * **Example**: `FD_SET(fd, &readfds);`

* **`struct timeval`**
  
  * **Purpose**: Represents time intervals.
  * **Usage**: Used with `select()` to specify timeout periods.
  * **Example**: `timeout.tv_sec = 5; timeout.tv_usec = 0;`

* **`struct sockaddr` and its variants**
  
  * **Purpose**: Represents socket addresses.
  * **Usage**: Used in network programming with socket-related functions such as `bind()`, `connect()`, and `accept()`.
  * **Example**: `struct sockaddr_in addr;`

* **`ssize_t`**
  
  * **Purpose**: Represents the size of a data object or the result of a read/write operation.
  * **Usage**: Used in I/O functions like `read()` and `write()` to indicate the number of bytes read or written.
  * **Example**: `ssize_t bytes_read = read(fd, buffer, sizeof(buffer));`

<hr>

## Sockets

Socket programming in C is a method that enables communication between two nodes over a network. A socket serves as an endpoint for sending and receiving data, allowing applications to exchange information across different devices or processes.

### Types of Sockets

Sockets can be categorized based on the communication protocols they use:

* **Stream Sockets (SOCK_STREAM)**: These use TCP (Transmission Control Protocol) and provide a reliable, connection-oriented communication channel. They ensure that data is delivered in the same order it was sent
* **Datagram Sockets (SOCK_DGRAM)**: These use UDP (User Datagram Protocol) and are connectionless, meaning they do not guarantee the order or reliability of the data packets. This makes them faster but less reliable than stream sockets

```c
int socket(int domain, int type, int protocol);
```

* **domain**: Specifies the communication domain (e.g., `AF_INET` for IPv4).
* **type**: Specifies the socket type (e.g., `SOCK_STREAM` for TCP).
* **protocol**: Usually set to 0, allowing the system to choose the appropriate protocol

*return type* : A file descriptor for a new socket is returned. On error -1 is returned

### Binding the Socket `bind()`

For server applications, the socket must be bound to an **IP address and port number** using the `bind()` function. This associates the socket with a specific address and allows it to listen for incoming connections This is crucial for server applications that need to listen for incoming connections on a specific port. 

```c
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

### Connection of the Socket `connect()`

The `connect()` function in C is used to establish a connection between a client socket and a server socket. It is a crucial part of socket programming, particularly for TCP/IP communications.

The `connect()` function attempts to connect a socket (identified by its file descriptor) to a specified address, which is typically the address of a server. This is essential for client applications that need to communicate with a server over a network.

```c
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

* **sockfd**: This is the socket file descriptor that was created using the `socket()` function. It represents the endpoint for communication.

* **addr**: This is a pointer to a `sockaddr` structure that contains the address of the server to which the socket should connect. The structure typically includes the address family, port number, and IP address.
  
  ```
  The connect() function is designed to work with different types of socket addresses (not just IPv4). By using struct sockaddr, it provides a generic interface that can accommodate various address families
  ```

* **addrlen**: This specifies the size of the address structure pointed to by `addr`.

* **On success**, `connect()` returns `0`.

* **On failure**, it returns `-1`, and the global variable `errno` is set to indicate the error.

### Difference between bind and connect

* **`bind()`** associates a socket with a specific local address and port number. Binds the socket to a specific IP address and port number. Allows the socket to accept incoming connections. Allows a socket to accept incoming connections
* **`connect()`** establishes a connection between a client socket and a server socket by specifying the remote address and port. Establishes a connection between a client and server socket.

Note that the bind function binds the server to the specified port and allows it to accept connections from any IP address. When a client connects, it establishes a communication channel to the server, allowing it to send and receive data.

### Typical Client-Server Scenario

* **Server:**
  
  * Create socket → Bind to address → Listen for connections → Accept connections.

* **Client:**
  
  * Create socket → Connect to server.

* **Communication:**
  
  * Use `send()` and `recv()` to exchange data between the client and server after establishing the connection.

### Listening for Connections

The server uses the `listen()` function to indicate that it is ready to accept incoming connections. The function specifies the maximum number of pending connections that can be queued

```c
int listen(int sockfd, int backlog);
```

### Accepting Connections

When a client attempts to connect, the server calls the `accept()` function, which establishes a connection and returns a new socket descriptor for the communication with that specific client

```c
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

The `accept()` function is used to accept a connection on the socket specified by `sockfd`. When a connection is available, `accept()` creates a new socket with the same properties of `sockfd` and allocates a new file descriptor for the socket. The newly created socket is used to send and receive data with the connected peer. The `addr` argument is a pointer to a `sockaddr` structure that is filled in with the address of the connecting entity. The `addrlen` argument is a value-result argument: it should initially contain the amount of space pointed to by `addr`; on return it will contain the actual length (in bytes) of the address returned.

###### IMPORTANT

`c = accept(s, (struct sockaddr *)&cli, &addrlen);`  2nd param = This is a pointer to a `sockaddr` structure that will be filled with the address of the connecting client.  3rd param = On return, `accept()` will modify `addrlen` to contain the actual size of the returned address. Should be initialized to the size of the `cli` structure before calling `accept()`

### Sending and Receiving Data

Once a connection is established, data can be sent and received using the `send()` and `recv()` functions. These functions handle the transmission of data over the established socket:

```c
send(sockfd, message, length, flags);
recv(sockfd, buffer, buffer_size, flags);
```

* **sockfd**: The socket file descriptor.
* **message**: The data to send.
* **buffer**: Where received data will be stored.
* **length** and **buffer_size**: The sizes of the data being sent and received, respectively

#### `write()` and `read()`

* **`send()`**: This function is similar to `write()` but provides additional options for controlling how the data is sent (e.g., using flags).
* **`recv()`**: This function is similar to `read()` but also allows for more control over how data is received.

### Closing the Socket

After communication is complete, the socket should be closed using the `close()` function to free up resources

```c
int socket(int domain, int type, int protocol);

bind() /* IP address and port number** using the `bind() */
connect()
listen()
accept()
send() and recv()
close()
```

<hr>

## Struct `sockaddr_in`

This structure is used to store **information about an IPv4 socket address**, which includes the following members

* `sin_family`: The address family, typically set to `AF_INET` for IPv4.
* `sin_port`: The port number in network byte order (big-endian).
* `sin_addr`: An `in_addr` structure that holds the IPv4 address.
* `sin_zero`: An 8-byte padding field to make the structure the same size as `struct sockaddr`.

This structure is commonly used in socket programming with the `connect()`, `bind()`, and `sendto()` functions, among others. It allows you to specify the ***address information needed for network communication using IPv4.***

```
Create a Socket: Use the socket() function to create a socket.

Prepare the Address: Fill in a sockaddr_in structure (for IPv4) or sockaddr_in6 structure (for IPv6) with the server's address and port

Call connect(): Use the connect() function to establish the connection.
```

<hr>


