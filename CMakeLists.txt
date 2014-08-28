project(BomberPiProject) 
cmake_minimum_required(VERSION 2.8)

include(ExternalProject)
include(FindPkgConfig)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

SET(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
SET(INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

SET(CLIENT_SRC ${SRC}/Client/)
SET(CLIENT_INCLUDE ${INCLUDE}/Client/)

SET(SHARED_SRCS
    ${SRC}/Timer.cpp
    ${SRC}/State.cpp
    ${SRC}/StateManager.cpp
    ${SRC}/GameEventHandler.cpp
    ${SRC}/SDLEventHandler.cpp
)
SET(SHARED_HDRS
    ${INCLUDE}/Timer.hpp
    ${INCLUDE}/State.hpp
    ${INCLUDE}/StateManager.hpp
    ${INCLUDE}/GameEventHandler.hpp
    ${INCLUDE}/SDLEventHandler.hpp
)

SET(CLIENT_SRCS
    ${CLIENT_SRC}/Game.cpp
    ${CLIENT_SRC}/Window.cpp
    ${CLIENT_SRC}/Texture.cpp
    ${CLIENT_SRC}/TextureManager.cpp
)

SET(CLIENT_HDRS
    ${CLIENT_INCLUDE}/Game.hpp
    ${CLIENT_INCLUDE}/Window.hpp
    ${CLIENT_INCLUDE}/Texture.hpp
    ${CLIENT_INCLUDE}/TextureManager.hpp
)

add_executable(Client ${CLIENT_SRCS} ${CLIENT_HDRS} 
		      ${SHARED_SRCS} ${SHARED_HDRS})

ExternalProject_Add(GLM_Project
    PREFIX glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.5.4
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

add_dependencies(Client GLM_Project)

include_directories(${INCLUDE})
# GLM Headers in the glm/ path.
include_directories(SYSTEM ${CMAKE_CURRENT_BINARY_DIR}/glm/src/GLM_Project/)

# Add SDL2 and SDL_image
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(Client ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

# Add sigc++2
find_package(SigC++ REQUIRED)
if(${SIGC++_FOUND})
    target_link_libraries(Client ${SIGC++_LIBRARY})
    include_directories(${SIGC++_INCLUDE_DIR})
    message(STATUS ${SIGC++_INCLUDE_DIR})
elseif()
    message(STATUS "Did not find Sigc++2! Please install it before you try to compile again.")
endif()

# Activate C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")