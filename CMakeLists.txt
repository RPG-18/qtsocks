set(PROJECT QtSocks)
project(${PROJECT} CXX)
cmake_minimum_required(VERSION 2.8.11)

option(ENABLE_EPOOL "" OFF)
if(ENABLE_EPOOL)
    add_definitions(-DENABLE_EPOOL)
    include_directories(3rdparty/qeventdispatcher_epoll)
endif()

set(Qt5_COMMPONETS Core Network
)

               
find_package(Qt5 COMPONENTS ${Qt5_COMMPONETS})

include_directories(${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Core_PRIVATE_INCLUDE_DIRS}
                    ${Qt5Network_INCLUDE_DIRS}
)
                    
add_definitions(${Qt5Core_DEFINITIONS}
                ${Qt5Network_DEFINITIONS}
)
                
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wextra -Wpedantic")

add_subdirectory(src)
if(ENABLE_EPOOL)
    add_subdirectory(3rdparty/qeventdispatcher_epoll)
endif()