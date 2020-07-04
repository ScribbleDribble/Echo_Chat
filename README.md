#Chat Application

Echo Chat is a simple terminal chat application which focuses 
on user customisation. 
 
## Installation

1. Download and install the Boost ASIO library
2. Install SQLite3 for C++  
`sudo apt-get install libsqlite3-dev
`

## Running The App

In the root directory of the project, run the following
commands in the terminal.

Build project by typing

`cmake CMakeLists.txt`

`make`

Run server by entering

`./server <port num> `

Compile client 

`g++ client.cpp -o client -lpthread`

Run client

`./client <port num>`

### Summary
Communication is non-blocking and
threads are used for accepting new connections.
