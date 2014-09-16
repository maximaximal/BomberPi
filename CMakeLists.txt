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
    ${SRC}/SDLEventHandler.cpp
    ${SRC}/InputMap.cpp
)
SET(SHARED_HDRS
    ${INCLUDE}/Timer.hpp
    ${INCLUDE}/State.hpp
    ${INCLUDE}/StateManager.hpp
    ${INCLUDE}/SDLEventHandler.hpp
    ${INCLUDE}/PlayerInput.hpp
    ${INCLUDE}/InputMap.hpp
)

SET(CLIENT_SRCS
    ${CLIENT_SRC}/Game.cpp
    ${CLIENT_SRC}/Window.cpp
    ${CLIENT_SRC}/Texture.cpp
    ${CLIENT_SRC}/TextureManager.cpp
    ${CLIENT_SRC}/StateBomberman.cpp
    ${CLIENT_SRC}/EntityDropGenerator.cpp
    ${CLIENT_SRC}/BombermanMap.cpp
    ${CLIENT_SRC}/PlayerInputComponent.cpp
    ${CLIENT_SRC}/SpriteComponent.cpp
    ${CLIENT_SRC}/PositionComponent.cpp
    ${CLIENT_SRC}/VelocityComponent.cpp
    ${CLIENT_SRC}/BodyComponent.cpp
    ${CLIENT_SRC}/PlayerComponent.cpp
    ${CLIENT_SRC}/DestructableComponent.cpp
    ${CLIENT_SRC}/TimerComponent.cpp
    ${CLIENT_SRC}/AnimationComponent.cpp
    ${CLIENT_SRC}/BombComponent.cpp
    ${CLIENT_SRC}/BombLayerComponent.cpp
    ${CLIENT_SRC}/SpreadingComponent.cpp
    ${CLIENT_SRC}/BombPlaceSystem.cpp
    ${CLIENT_SRC}/BombPlacePositionSystem.cpp
    ${CLIENT_SRC}/SpriteRenderingSystem.cpp
    ${CLIENT_SRC}/PlayerInputSystem.cpp
    ${CLIENT_SRC}/PlayerMovementSystem.cpp
    ${CLIENT_SRC}/TimerSystem.cpp
    ${CLIENT_SRC}/BombExplodeSystem.cpp
    ${CLIENT_SRC}/AnimationSystem.cpp
    ${CLIENT_SRC}/ExplosionSystem.cpp
    ${CLIENT_SRC}/Animation.cpp
    ${CLIENT_SRC}/EntityFactory.cpp
)

SET(CLIENT_HDRS
    ${CLIENT_INCLUDE}/Game.hpp
    ${CLIENT_INCLUDE}/Window.hpp
    ${CLIENT_INCLUDE}/Texture.hpp
    ${CLIENT_INCLUDE}/TextureManager.hpp
    ${CLIENT_INCLUDE}/StateBomberman.hpp
    ${CLIENT_INCLUDE}/EntityDropGenerator.hpp
    ${CLIENT_INCLUDE}/BombermanMap.hpp
    ${CLIENT_INCLUDE}/BombermanMapTile.hpp
    ${CLIENT_INCLUDE}/PlayerInputComponent.hpp
    ${CLIENT_INCLUDE}/SpriteComponent.hpp
    ${CLIENT_INCLUDE}/PositionComponent.hpp
    ${CLIENT_INCLUDE}/VelocityComponent.hpp
    ${CLIENT_INCLUDE}/BodyComponent.hpp
    ${CLIENT_INCLUDE}/PlayerComponent.hpp
    ${CLIENT_INCLUDE}/DestructableComponent.hpp
    ${CLIENT_INCLUDE}/TimerComponent.hpp
    ${CLIENT_INCLUDE}/AnimationComponent.hpp
    ${CLIENT_INCLUDE}/BombComponent.hpp
    ${CLIENT_INCLUDE}/BombLayerComponent.hpp
    ${CLIENT_INCLUDE}/SpreadingComponent.hpp
    ${CLIENT_INCLUDE}/SpriteRenderingSystem.hpp
    ${CLIENT_INCLUDE}/PlayerInputSystem.hpp
    ${CLIENT_INCLUDE}/PlayerMovementSystem.hpp
    ${CLIENT_INCLUDE}/BombPlaceSystem.hpp
    ${CLIENT_INCLUDE}/BombPlacePositionSystem.hpp
    ${CLIENT_INCLUDE}/TimerSystem.hpp
    ${CLIENT_INCLUDE}/BombExplodeSystem.hpp
    ${CLIENT_INCLUDE}/AnimationSystem.hpp
    ${CLIENT_INCLUDE}/ExplosionSystem.hpp
    ${CLIENT_INCLUDE}/Animation.hpp
    ${CLIENT_INCLUDE}/EntityFactory.hpp
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

# Add anax
ExternalProject_Add(anax_project
    PREFIX anax
    GIT_REPOSITORY https://github.com/miguelmartin75/anax.git 
    UPDATE_COMMAND git pull origin master
    INSTALL_COMMAND ""
)

add_dependencies(Client anax_project)

find_library(anax_library
    NAMES anax libanax libanax_d libanax_d.so
    HINTS ${CMAKE_CURRENT_BINARY_DIR}/anax/src/anax_project-build/lib
    NO_DEFAULT_PATH
)

if(NOT ${anax_library} MATCHES "anax_library-NOTFOUND")
    target_link_libraries(Client ${anax_library})
    include_directories(SYSTEM ${CMAKE_CURRENT_BINARY_DIR}/anax/src/anax_project/include/)
    message(STATUS "Anax Library: " ${anax_library})
else()
    message(STATUS "Please re-run cmake!")
endif()

# Activate C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	list(APPEND ${CMAKE_CXX_FLAGS} "-Wall -std=x++11 ${CMAKE_CXX_FLAGS}")
endif()
