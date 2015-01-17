project(BomberPiProject) 
cmake_minimum_required(VERSION 2.8)

include(ExternalProject)
include(FindPkgConfig)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

SET(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
SET(INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

SET(CLIENT_SRC ${SRC}/Client/)
SET(CLIENT_INCLUDE ${INCLUDE}/Client/)

SET(PIGA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/piga)

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
    ${INCLUDE}/InterfaceLogger.hpp
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
    ${CLIENT_SRC}/DamageDealerComponent.cpp
    ${CLIENT_SRC}/HealthComponent.cpp
    ${CLIENT_SRC}/EntityTypeComponent.cpp
    ${CLIENT_SRC}/PowerupComponent.cpp
    ${CLIENT_SRC}/BombPlaceSystem.cpp
    ${CLIENT_SRC}/BombPlacePositionSystem.cpp
    ${CLIENT_SRC}/SpriteRenderingSystem.cpp
    ${CLIENT_SRC}/PlayerInputSystem.cpp
    ${CLIENT_SRC}/PlayerMovementSystem.cpp
    ${CLIENT_SRC}/TimerSystem.cpp
    ${CLIENT_SRC}/BombExplodeSystem.cpp
    ${CLIENT_SRC}/AnimationSystem.cpp
    ${CLIENT_SRC}/ExplosionSystem.cpp
    ${CLIENT_SRC}/ExplosionManagementSystem.cpp
    ${CLIENT_SRC}/CollisionSystem.cpp
    ${CLIENT_SRC}/DamageSystem.cpp
    ${CLIENT_SRC}/HealthSystem.cpp
    ${CLIENT_SRC}/KillEntityTypeSystem.cpp
    ${CLIENT_SRC}/Animation.cpp
    ${CLIENT_SRC}/Collision.cpp
    ${CLIENT_SRC}/EntityFactory.cpp
    ${CLIENT_SRC}/Player.cpp
    ${CLIENT_SRC}/Config.cpp
    ${CLIENT_SRC}/PlayerManager.cpp
    ${CLIENT_SRC}/WinChecker.cpp
    ${CLIENT_SRC}/Powerup.cpp
    ${CLIENT_SRC}/PowerupQueue.cpp

    ${CLIENT_SRC}/PowerupCollisionResolver.cpp

    ${CLIENT_SRC}/KeyboardInputMethod.cpp

    ${CLIENT_SRC}/UI/PowerupQueue.cpp
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
    ${CLIENT_INCLUDE}/DamageDealerComponent.hpp
    ${CLIENT_INCLUDE}/HealthComponent.hpp
    ${CLIENT_INCLUDE}/EntityTypeComponent.hpp
    ${CLIENT_INCLUDE}/PowerupComponent.hpp
    ${CLIENT_INCLUDE}/SpriteRenderingSystem.hpp
    ${CLIENT_INCLUDE}/PlayerInputSystem.hpp
    ${CLIENT_INCLUDE}/PlayerMovementSystem.hpp
    ${CLIENT_INCLUDE}/BombPlaceSystem.hpp
    ${CLIENT_INCLUDE}/BombPlacePositionSystem.hpp
    ${CLIENT_INCLUDE}/TimerSystem.hpp
    ${CLIENT_INCLUDE}/BombExplodeSystem.hpp
    ${CLIENT_INCLUDE}/AnimationSystem.hpp
    ${CLIENT_INCLUDE}/ExplosionSystem.hpp
    ${CLIENT_INCLUDE}/ExplosionManagementSystem.hpp
    ${CLIENT_INCLUDE}/CollisionSystem.hpp
    ${CLIENT_INCLUDE}/DamageSystem.hpp
    ${CLIENT_INCLUDE}/HealthSystem.hpp
    ${CLIENT_INCLUDE}/KillEntityTypeSystem.hpp
    ${CLIENT_INCLUDE}/Animation.hpp
    ${CLIENT_INCLUDE}/Collision.hpp
    ${CLIENT_INCLUDE}/EntityFactory.hpp
    ${CLIENT_INCLUDE}/Player.hpp
    ${CLIENT_INCLUDE}/Config.hpp
    ${CLIENT_INCLUDE}/PlayerManager.hpp
    ${CLIENT_INCLUDE}/WinChecker.hpp
    ${CLIENT_INCLUDE}/Powerup.hpp
    ${CLIENT_INCLUDE}/PowerupQueue.hpp

    ${CLIENT_INCLUDE}/PowerupCollisionResolver.hpp

    ${CLIENT_INCLUDE}/KeyboardInputMethod.hpp

    ${CLIENT_INCLUDE}/UI/PowerupQueue.hpp
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
    CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
)

add_dependencies(Client GLM_Project)

include_directories(${INCLUDE})
# GLM Headers in the glm/ path.
include_directories(SYSTEM ${CMAKE_CURRENT_BINARY_DIR}/glm/src/GLM_Project/)

find_package(SDL2)
if(${SDL2_FOUND})
    target_link_libraries(Client ${SDL2_LIBRARY})
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

find_package(SDL2image)
if(${SDL2IMAGE_FOUND})
    target_link_libraries(Client ${SDL2IMAGE_LIBRARY})
    include_directories(${SDL2IMAGE_INCLUDE_DIRS})
endif()

find_package(SDL2ttf)
if(${SDL2TTF_FOUND})
    target_link_libraries(Client ${SDL2TTF_LIBRARY})
    include_directories(${SDL2TTF_INCLUDE_DIRS})
endif()

# Add sigc++2
find_package(SigC++ REQUIRED)
if(${SIGC++_FOUND})
    target_link_libraries(Client ${SIGC++_LIBRARY})
    include_directories(${SIGC++_INCLUDE_DIR})
elseif()
    message(STATUS "Did not find Sigc++2! Please install it before you try to compile again.")
endif()

# Add yaml-cpp
find_package(YamlCpp REQUIRED)
if(${YAMLCPP_FOUND})
    target_link_libraries(Client ${YAMLCPP_LIBRARY})
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
    CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
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

find_package(Boost REQUIRED COMPONENTS system thread)

if(${Boost_FOUND})
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
    target_link_libraries(Client ${Boost_LIBRARIES})
endif()

# Add piga
message(STATUS "Piga Dir: " ${PIGA_DIR})
add_subdirectory(${PIGA_DIR}/libpiga/ ${CMAKE_CURRENT_BINARY_DIR}/piga_dir/)
add_dependencies(Client piga)
include_directories(${LIBPIGA_INCLUDE_DIRECTORIES})
target_link_libraries(Client piga)

add_dependencies(Client piga)

#Add pihud
include_directories(${PIGA_DIR}/pihud/include)
find_library(pihud_library
    NAMES pihud libpihud libpihud.a libpihud.so
    HINTS ${CMAKE_CURRENT_BINARY_DIR}/piga_dir/pihud
    NO_DEFAULT_PATH
)
target_link_libraries(Client pihud)

# Activate C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -lrt ${CMAKE_CXX_FLAGS}")

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	list(APPEND ${CMAKE_CXX_FLAGS} "-Wall -std=c++11 ${CMAKE_CXX_FLAGS}")
endif()

