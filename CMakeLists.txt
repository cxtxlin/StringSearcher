cmake_minimum_required(VERSION 3.22)
project(RegexInFile)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS
        bi_istream_iterator.h
        )

set(SOURCES
        )

add_executable(RegexInFile main.cpp
        ${HEADERS}
        ${SOURCES}
        )
