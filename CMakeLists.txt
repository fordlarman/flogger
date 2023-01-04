cmake_minimum_required(VERSION 3.14)
project(wx1Test)

set(CMAKE_CXX_STANDARD 14)

set(wxWidgets_ROOT_DIR </usr/local/include/wx-3.1>)
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base  REQUIRED)
include(${wxWidgets_USE_FILE})

set(SOURCE_FILES main.cpp)
add_executable(wx1Test ${SOURCE_FILES})

target_link_libraries(wx1Test ${wxWidgets_LIBRARIES})