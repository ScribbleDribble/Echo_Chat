##Echo Chat

Echo Chat is a simple terminal chat application which focuses 
on user customisation. 
 
## Installation

1. Download and install the Boost ASIO library
2. Install SQLite3 for C++  
`sudo apt-get install libsqlite3-dev
`

## Running Echo

In the root directory of the project, run the following
commands in the terminal.

Build the project

`cmake CMakeLists.txt`

`make`

Run server 

`./server <port num> `

Compile client and run client 

`g++ client.cpp -o client -lpthread`

`./client <port num>`


## Summary
- Non-blocking communication.

- Threads used for accepting new connections.
