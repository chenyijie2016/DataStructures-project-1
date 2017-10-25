cmake_minimum_required(VERSION 3.8)
set(dir ${CMAKE_CURRENT_SOURCE_DIR}/bin)
project(project1)
set(SOURCE_FILES src/main.cpp src/DataStructure.cpp src/DataStructure.h src/Network.cpp src/Network.h src/CSVparser.cpp src/CSVparser.hpp src/HTMLparser.cpp src/HTMLparser.h)
include_directories(curllib/include src)
set(PROJECT_LINK_LIBS libcurl.a libwldap32.a libcurldll.a libws2_32.a)
link_directories(curllib/lib)
add_executable(main ${SOURCE_FILES})
target_link_libraries(main ${PROJECT_LINK_LIBS})
SET(EXECUTABLE_OUTPUT_PATH ${dir})
SET(CMAKE_CACHEFILE_DIR ${dir})


