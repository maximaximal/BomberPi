project(BomberPiProject) 
cmake_minimum_required(VERSION 2.8)

include(ExternalProject)
include(FindPkgConfig)

set(BOMBERPI_VERSION_MAJOR "0" CACHE STRING "Major-Version")
set(BOMBERPI_VERSION_MINOR "7" CACHE STRING "Minor-Version")
set(BOMBERPI_VERSION_PATCH "0" CACHE STRING "Patch-Version")
set(BOMBERPI_VERSION_TWEAK "0" CACHE STRING "Tweak-Version")
set(BOMBERPI_VERSION ${BOMBERPI_VERSION_MAJOR}.${BOMBERPI_VERSION_MINOR}.${BOMBERPI_VERSION_PATCH}.${BOMBERPI_VERSION_TWEAK})

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

SET(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
SET(INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

SET(BomberPiClient_SRC ${SRC}/Client/)
SET(BomberPiClient_INCLUDE ${INCLUDE}/Client/)

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

SET(BomberPiClient_SRCS
    ${BomberPiClient_SRC}/Game.cpp
    ${BomberPiClient_SRC}/Window.cpp
    ${BomberPiClient_SRC}/Texture.cpp
    ${BomberPiClient_SRC}/TextureManager.cpp
    ${BomberPiClient_SRC}/StateBomberman.cpp
    ${BomberPiClient_SRC}/StateMainMenu.cpp
    ${BomberPiClient_SRC}/EntityDropGenerator.cpp
    ${BomberPiClient_SRC}/BombermanMap.cpp
    ${BomberPiClient_SRC}/PlayerInputComponent.cpp
    ${BomberPiClient_SRC}/SpriteComponent.cpp
    ${BomberPiClient_SRC}/PositionComponent.cpp
    ${BomberPiClient_SRC}/VelocityComponent.cpp
    ${BomberPiClient_SRC}/BodyComponent.cpp
    ${BomberPiClient_SRC}/PlayerComponent.cpp
    ${BomberPiClient_SRC}/DestructableComponent.cpp
    ${BomberPiClient_SRC}/TimerComponent.cpp
    ${BomberPiClient_SRC}/AnimationComponent.cpp
    ${BomberPiClient_SRC}/BombComponent.cpp
    ${BomberPiClient_SRC}/BombLayerComponent.cpp
    ${BomberPiClient_SRC}/SpreadingComponent.cpp
    ${BomberPiClient_SRC}/DamageDealerComponent.cpp
    ${BomberPiClient_SRC}/HealthComponent.cpp
    ${BomberPiClient_SRC}/EntityTypeComponent.cpp
    ${BomberPiClient_SRC}/PowerupComponent.cpp
    ${BomberPiClient_SRC}/AIComponent.cpp
    ${BomberPiClient_SRC}/AIControlSystem.cpp
    ${BomberPiClient_SRC}/BombPlaceSystem.cpp
    ${BomberPiClient_SRC}/BombPlacePositionSystem.cpp
    ${BomberPiClient_SRC}/SpriteRenderingSystem.cpp
    ${BomberPiClient_SRC}/PlayerInputSystem.cpp
    ${BomberPiClient_SRC}/PlayerMovementSystem.cpp
    ${BomberPiClient_SRC}/TimerSystem.cpp
    ${BomberPiClient_SRC}/BombExplodeSystem.cpp
    ${BomberPiClient_SRC}/AnimationSystem.cpp
    ${BomberPiClient_SRC}/ExplosionSystem.cpp
    ${BomberPiClient_SRC}/ExplosionManagementSystem.cpp
    ${BomberPiClient_SRC}/CollisionSystem.cpp
    ${BomberPiClient_SRC}/DamageSystem.cpp
    ${BomberPiClient_SRC}/HealthSystem.cpp
    ${BomberPiClient_SRC}/KillEntityTypeSystem.cpp
    ${BomberPiClient_SRC}/Animation.cpp
    ${BomberPiClient_SRC}/Collision.cpp
    ${BomberPiClient_SRC}/EntityFactory.cpp
    ${BomberPiClient_SRC}/Player.cpp
    ${BomberPiClient_SRC}/Config.cpp
    ${BomberPiClient_SRC}/PlayerManager.cpp
    ${BomberPiClient_SRC}/WinChecker.cpp
    ${BomberPiClient_SRC}/Powerup.cpp
    ${BomberPiClient_SRC}/PowerupQueue.cpp
    ${BomberPiClient_SRC}/EmbeddedTilemap.cpp
    ${BomberPiClient_SRC}/EmbeddedChunk.cpp

    ${BomberPiClient_SRC}/PowerupCollisionResolver.cpp

    ${BomberPiClient_SRC}/KeyboardInputMethod.cpp

    ${BomberPiClient_SRC}/UI/PowerupQueue.cpp
)

SET(BomberPiClient_HDRS
    ${BomberPiClient_INCLUDE}/Game.hpp
    ${BomberPiClient_INCLUDE}/Window.hpp
    ${BomberPiClient_INCLUDE}/Texture.hpp
    ${BomberPiClient_INCLUDE}/TextureManager.hpp
    ${BomberPiClient_INCLUDE}/StateBomberman.hpp
    ${BomberPiClient_INCLUDE}/StateMainMenu.hpp
    ${BomberPiClient_INCLUDE}/EntityDropGenerator.hpp
    ${BomberPiClient_INCLUDE}/BombermanMap.hpp
    ${BomberPiClient_INCLUDE}/BombermanMapTile.hpp
    ${BomberPiClient_INCLUDE}/PlayerInputComponent.hpp
    ${BomberPiClient_INCLUDE}/SpriteComponent.hpp
    ${BomberPiClient_INCLUDE}/PositionComponent.hpp
    ${BomberPiClient_INCLUDE}/VelocityComponent.hpp
    ${BomberPiClient_INCLUDE}/BodyComponent.hpp
    ${BomberPiClient_INCLUDE}/PlayerComponent.hpp
    ${BomberPiClient_INCLUDE}/DestructableComponent.hpp
    ${BomberPiClient_INCLUDE}/TimerComponent.hpp
    ${BomberPiClient_INCLUDE}/AnimationComponent.hpp
    ${BomberPiClient_INCLUDE}/BombComponent.hpp
    ${BomberPiClient_INCLUDE}/BombLayerComponent.hpp
    ${BomberPiClient_INCLUDE}/SpreadingComponent.hpp
    ${BomberPiClient_INCLUDE}/DamageDealerComponent.hpp
    ${BomberPiClient_INCLUDE}/HealthComponent.hpp
    ${BomberPiClient_INCLUDE}/EntityTypeComponent.hpp
    ${BomberPiClient_INCLUDE}/PowerupComponent.hpp
    ${BomberPiClient_INCLUDE}/SpeedComponent.hpp
    ${BomberPiClient_INCLUDE}/AIComponent.hpp
    ${BomberPiClient_INCLUDE}/AIControlSystem.hpp
    ${BomberPiClient_INCLUDE}/SpriteRenderingSystem.hpp
    ${BomberPiClient_INCLUDE}/PlayerInputSystem.hpp
    ${BomberPiClient_INCLUDE}/PlayerMovementSystem.hpp
    ${BomberPiClient_INCLUDE}/BombPlaceSystem.hpp
    ${BomberPiClient_INCLUDE}/BombPlacePositionSystem.hpp
    ${BomberPiClient_INCLUDE}/TimerSystem.hpp
    ${BomberPiClient_INCLUDE}/BombExplodeSystem.hpp
    ${BomberPiClient_INCLUDE}/AnimationSystem.hpp
    ${BomberPiClient_INCLUDE}/ExplosionSystem.hpp
    ${BomberPiClient_INCLUDE}/ExplosionManagementSystem.hpp
    ${BomberPiClient_INCLUDE}/CollisionSystem.hpp
    ${BomberPiClient_INCLUDE}/DamageSystem.hpp
    ${BomberPiClient_INCLUDE}/HealthSystem.hpp
    ${BomberPiClient_INCLUDE}/KillEntityTypeSystem.hpp
    ${BomberPiClient_INCLUDE}/Animation.hpp
    ${BomberPiClient_INCLUDE}/Collision.hpp
    ${BomberPiClient_INCLUDE}/EntityFactory.hpp
    ${BomberPiClient_INCLUDE}/Player.hpp
    ${BomberPiClient_INCLUDE}/Config.hpp
    ${BomberPiClient_INCLUDE}/PlayerManager.hpp
    ${BomberPiClient_INCLUDE}/WinChecker.hpp
    ${BomberPiClient_INCLUDE}/Powerup.hpp
    ${BomberPiClient_INCLUDE}/PowerupQueue.hpp
    ${BomberPiClient_INCLUDE}/EmbeddedTilemap.hpp
    ${BomberPiClient_INCLUDE}/EmbeddedChunk.hpp

    ${BomberPiClient_INCLUDE}/PowerupCollisionResolver.hpp

    ${BomberPiClient_INCLUDE}/KeyboardInputMethod.hpp

    ${BomberPiClient_INCLUDE}/UI/PowerupQueue.hpp
)

add_executable(BomberPiClient ${BomberPiClient_SRCS} ${BomberPiClient_HDRS}
		      ${SHARED_SRCS} ${SHARED_HDRS})

ExternalProject_Add(GLM_Project
    PREFIX glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.5.4
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
)

add_dependencies(BomberPiClient GLM_Project)

include_directories(${INCLUDE})
# GLM Headers in the glm/ path.
include_directories(SYSTEM ${CMAKE_CURRENT_BINARY_DIR}/glm/src/GLM_Project/)

find_package(SDL2)
if(${SDL2_FOUND})
    target_link_libraries(BomberPiClient ${SDL2_LIBRARY})
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

find_package(SDL2image)
if(${SDL2IMAGE_FOUND})
    target_link_libraries(BomberPiClient ${SDL2IMAGE_LIBRARY})
    include_directories(${SDL2IMAGE_INCLUDE_DIRS})
endif()

find_package(SDL2ttf)
if(${SDL2TTF_FOUND})
    target_link_libraries(BomberPiClient ${SDL2TTF_LIBRARY})
    include_directories(${SDL2TTF_INCLUDE_DIRS})
endif()

# Add sigc++2
find_package(SigC++ REQUIRED)
if(${SIGC++_FOUND})
    target_link_libraries(BomberPiClient ${SIGC++_LIBRARY})
    include_directories(${SIGC++_INCLUDE_DIR})
elseif()
    message(STATUS "Did not find Sigc++2! Please install it before you try to compile again.")
endif()

# Add yaml-cpp
find_package(YamlCpp REQUIRED)
if(${YAMLCPP_FOUND})
    target_link_libraries(BomberPiClient ${YAMLCPP_LIBRARY})
    include_directories(${YAMLCPP_INCLUDE_DIR})
elseif()
    message(STATUS "Did not find Yaml-Cpp! Please install it before you try to compile again.")
endif()

# Add anax
ExternalProject_Add(anax_project
    PREFIX anax
    GIT_REPOSITORY https://github.com/miguelmartin75/anax.git 
    UPDATE_COMMAND git pull origin master
    INSTALL_COMMAND ""
    CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} -DBUILD_SHARED_LIBS=false
)

add_dependencies(BomberPiClient anax_project)

find_library(anax_library
    NAMES anax libanax libanax.a
    HINTS ${CMAKE_CURRENT_BINARY_DIR}/anax/src/anax_project-build/
    NO_DEFAULT_PATH
)

if(NOT ${anax_library} MATCHES "anax_library-NOTFOUND")
    target_link_libraries(BomberPiClient ${anax_library})
    include_directories(SYSTEM ${CMAKE_CURRENT_BINARY_DIR}/anax/src/anax_project/include/)
    message(STATUS "Anax Library: " ${anax_library})
else()
    message(STATUS "Please re-run cmake!")
endif()

find_package(Boost REQUIRED COMPONENTS system thread)

if(${Boost_FOUND})
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
    target_link_libraries(BomberPiClient ${Boost_LIBRARIES})
endif()

find_package(Libpiga REQUIRED)
if(${Libpiga_FOUND})
    target_link_libraries(BomberPiClient ${Libpiga_LIBRARIES})
    include_directories(${Libpiga_INCLUDE_DIRS})
endif()

find_package(Pihud REQUIRED)
if(${Pihud_FOUND})
    target_link_libraries(BomberPiClient ${Pihud_LIBRARIES})
    include_directories(${Pihud_INCLUDE_DIRS})
endif()

add_custom_command(TARGET BomberPiClient
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/distributor.py
                   POST_BUILD
                   COMMAND python
                   ARGS ${CMAKE_CURRENT_SOURCE_DIR}/distributor.py ${CMAKE_CURRENT_BINARY_DIR}/dist)

set_property(TARGET BomberPiClient PROPERTY VERSION ${BOMBERPI_VERSION})

install(TARGETS BomberPiClient EXPORT BomberPiClientTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
    RUNTIME DESTINATION bin)

# Data files
install(
    DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/Data
    DESTINATION ../var/bomberpi)

# Game package
install(
    FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Data/config.yml
        ${CMAKE_CURRENT_SOURCE_DIR}/Data/PackageSpecs.yml
        ${CMAKE_CURRENT_SOURCE_DIR}/Data/logo.png
        ${CMAKE_CURRENT_SOURCE_DIR}/Data/chooser-background.png
        ${CMAKE_CURRENT_SOURCE_DIR}/Data/LICENSE.txt
    DESTINATION ../var/piga/Games/BomberPi/)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A bomberman clone.")
set(CPACK_PACKAGE_VENDOR "Pigaco")
set(CPACK_PACKAGE_VERSION_MAJOR ${BOMBERPI_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${BOMBERPI_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${BOMBERPI_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK ${BOMBERPI_VERSION_TWEAK})
set(CPACK_DEBIAN_PACKAGE_NAME "bomberpi")
set(CPACK_DEBIAN_PACKAGE_HOMEPAHE "https://github.com/maximaximal/bomberpi")
set(CPACK_DEBIAN_PACKAGE_DEPENDS
"libstdc++6 (>= 4.9.2-10), piga-libpiga (>= 0.6.0), libsigc++-2.0-0c2a (>= 2.4.0-1), libsdl2-2.0-0 (>= 2.0.2), libsdl2-image-2.0-0 (>= 2.0.0), libsdl2-ttf-2.0-0 (>= 2.0.12), piga-libpihud (>= 0.6)")
set(CPACK_PACKAGE_NAME "bomberpi")
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Max Heisinger <mail@maximaximal.com>")
include(CPack)
# Activate C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -lrt ${CMAKE_CXX_FLAGS}")

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    list(APPEND ${CMAKE_CXX_FLAGS} "-Wall -std=c++11 ${CMAKE_CXX_FLAGS}")
endif()

