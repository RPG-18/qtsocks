set(SRC main.cpp
        Client.cpp
        Server.cpp
        Worker.cpp
)

set(HEADERS Client.h
            Server.h
            Worker.h
)
set(LIBS Qt5::Core
              Qt5::Network
)

if(ENABLE_EPOOL)
    set(LIBS ${LIBS}
             eventdispatcher_epoll
    )
endif()


add_executable(QtSocks ${SRC} ${HEADERS})
target_link_libraries(QtSocks ${LIBS})