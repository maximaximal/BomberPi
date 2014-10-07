project(pihud)
cmake_minimum_required(VERSION 2.8)

include(FindPkgConfig)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SRCS
    ${SRC}/HudContainer.cpp
    ${SRC}/DirectionEvent.cpp
    ${SRC}/InputEvent.cpp
    ${SRC}/Event.cpp
    ${SRC}/Widget.cpp
    ${SRC}/Config.cpp
    ${SRC}/Font.cpp
)

set(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include/pihud/)
set(HDRS
    ${HDR}/HudContainer.hpp
    ${HDR}/Widget.hpp
    ${HDR}/Rect.hpp
    ${HDR}/Event.hpp
    ${HDR}/InputEvent.hpp
    ${HDR}/DirectionEvent.hpp
    ${HDR}/Config.hpp
    ${HDR}/pihud.hpp
    ${HDR}/Font.hpp
    ${HDR}/Label.hpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} ${SRCS} ${HDRS})

# Activate C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

# Add SDL2 and SDL_image
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

# Add sigc++2
find_package(SigC++ REQUIRED)
if(${SIGC++_FOUND})
    target_link_libraries(${PROJECT_NAME} ${SIGC++_LIBRARY})
    include_directories(${SIGC++_INCLUDE_DIR})
elseif()
    message(STATUS "Did not find Sigc++2! Please install it before you try to compile again.")
endif()
