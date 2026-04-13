cmake_minimum_required(VERSION 3.10)

project(The_Light_Side_of_the_Moon)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src
                    src/API
                    src/Color
                    src/Film
                    src/Background
                    src/RunningOptions
                    src/Parser
                    ext/lib_tinyxml2
                    ext/lib_lodepng
                    ext/lib_ssdatas
                    ext/lib_ssmath)

add_executable(rt3
    src/main.cpp            
    src/API/API.cpp     
    src/Color/Color.cpp
    src/Film/Film.cpp
    src/Parser/Parser.cpp
    src/Background/Background.cpp
    src/RunningOptions/RunningOptions.cpp
    src/RunningOptions/PrintIMG.cpp
    ext/lib_tinyxml2/tinyxml2.cpp 
    ext/lib_lodepng/lodepng.cpp
    ext/lib_ssmath/ssmath.cpp
)
