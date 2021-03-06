cmake_minimum_required (VERSION 2.8.7)
project (logexpress)

#-Wall -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -std=c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/local/include/json-c -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")
#set(ROOT_DIR /home/wizehack/cpp_proj/logexpress/logexpressd/)
set(ROOT_DIR ./)
set(INCLUDE_DIR_CONF ${ROOT_DIR}/src/configmanagement)
set(INCLUDE_DIR_UTILS ${ROOT_DIR}/src/logmanagement)
set(INCLUDE_DIR_LOGMGR ${ROOT_DIR}/src/utils)
set(INCLUDE_DIR_CUI ${ROOT_DIR}/src/cui)
set(INCLUDE_DIR_ERROR ${ROOT_DIR}/src/error)
set(INCLUDE_DIR_LOG ${ROOT_DIR}/src/log)

include_directories(
    ${INCLUDE_DIR_CONF}
    ${INCLUDE_DIR_UTILS}
    ${INCLUDE_DIR_LOGMGR}
    ${INCLUDE_DIR_CUI}
    ${INCLUDE_DIR_ERROR}
    ${INCLUDE_DIR_LOG}
)

add_executable(
    logexpress 
    ${ROOT_DIR}/src/main.cpp 
    ${ROOT_DIR}/src/utils/logger.cpp
    ${ROOT_DIR}/src/utils/file.cpp
    ${ROOT_DIR}/src/cui/commandHandler.cpp
    ${ROOT_DIR}/src/cui/commandErrorHandler
    ${ROOT_DIR}/src/cui/commandConfOptionHandler.cpp
    ${ROOT_DIR}/src/cui/commandMessage.cpp
    ${ROOT_DIR}/src/cui/userInteractionManager.cpp
    ${ROOT_DIR}/src/configmanagement/confData.cpp
    ${ROOT_DIR}/src/configmanagement/configManager.cpp
    ${ROOT_DIR}/src/configmanagement/logMap.cpp
    ${ROOT_DIR}/src/error/errorHandler.cpp
    ${ROOT_DIR}/src/error/usageErrorHandler.cpp
    ${ROOT_DIR}/src/error/configErrorHandler.cpp
    ${ROOT_DIR}/src/error/errorMessage.cpp
    ${ROOT_DIR}/src/error/errorMessagePool.cpp
    ${ROOT_DIR}/src/log/logManager.cpp
    ${ROOT_DIR}/src/log/log.cpp
    ${ROOT_DIR}/src/log/udpServer.cpp
    ${ROOT_DIR}/src/log/messageQueue.cpp
    ${ROOT_DIR}/src/log/timer.cpp
)

# -ljson-c -lglib-2.0 
target_link_libraries(logexpress json-c glib-2.0)
