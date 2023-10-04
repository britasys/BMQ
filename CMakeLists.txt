cmake_minimum_required(VERSION 3.22.1)

##################################################################################
## Output Configurations                                                        ##
##################################################################################

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

##################################################################################
## CPP Configurations                                                           ##
##################################################################################

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

##################################################################################
## Application Configurations                                                   ##
##################################################################################

set(APP_NAME "cppagent")
set(APP_SOURCE_DIR ./src)
set(APP_EXTERNAL_DIR ./extern)

project(${APP_NAME} VERSION 1.0)

file(GLOB_RECURSE APP_SOURCE_FILES CONFIGURE_DEPENDS ${APP_SOURCE_DIR}/*.cpp ${APP_SOURCE_DIR}/*. hpp)

add_executable(${APP_NAME} ${APP_SOURCE_FILES})

##################################################################################
## External Libraries                                                           ##
##################################################################################

include(FetchContent)

## spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY      https://github.com/gabime/spdlog.git
    GIT_TAG             v1.12.0
    SOURCE_DIR          ../${APP_EXTERNAL_DIR}/spdlog
)
FetchContent_MakeAvailable(spdlog)
target_include_directories(${APP_NAME} PRIVATE ${spdlog_SOURCE_DIR}/include)

# cpp-httplib
FetchContent_Declare(
    cpp-httplib
    GIT_REPOSITORY      https://github.com/gabime/spdlog.git
    GIT_TAG             v1.12.0
    SOURCE_DIR          ../${APP_EXTERNAL_DIR}/cpp-httplib
)
FetchContent_MakeAvailable(cpp-httplib)
target_include_directories(${APP_NAME} PRIVATE ${cpp-httplib_SOURCE_DIR}/)

FetchContent_Declare(
    libzmq
    GIT_REPOSITORY      https://github.com/zeromq/libzmq.git
    GIT_TAG             v4.3.4
    SOURCE_DIR          ../${APP_EXTERNAL_DIR}/libzmq
)
FetchContent_MakeAvailable(libzmq)
target_link_libraries(${APP_NAME} PRIVATE libzmq)
target_include_directories(${APP_NAME} PRIVATE ${libzmq_SOURCE_DIR})

FetchContent_Declare(
    cppzmq
    GIT_REPOSITORY      https://github.com/zeromq/cppzmq.git
    GIT_TAG             v4.10.0
    SOURCE_DIR          ../${APP_EXTERNAL_DIR}/cppzmq
)
FetchContent_MakeAvailable(cppzmq)
target_include_directories(${APP_NAME} PRIVATE ${cppzmq_SOURCE_DIR})