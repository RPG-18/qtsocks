# Multi-threaded SOCKS4 server on Qt

Primitive multithreaded socks4 server on Qt.

## Requirements

* C++11 compiler support
* Qt5

## Build

    cd 
    mkdir build
    cmake ..
    make
    
## On Linux

    cmake -DENABLE_EPOOL=ON ..

## Run

    QtSocks -t 4 -p 8080