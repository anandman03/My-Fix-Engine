cmake_minimum_required(VERSION 3.5.0)
project(FIX_ENGINE VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(fix_engine
    main.cpp
    src/FixEngine.cpp
    src/Utils.cpp
)

include(CTest)
enable_testing()
