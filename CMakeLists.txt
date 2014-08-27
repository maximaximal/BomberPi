project(BomberPiProject) 
cmake_minimum_required(VERSION 2.8)

include(ExternalProject)

SET(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
SET(INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

SET(CLIENT_SRC ${SRC}/Client/)
SET(CLIENT_INCLUDE ${INCLUDE}/Client/)

SET(CLIENT_SRCS
    ${CLIENT_SRC}/Game.cpp
)

SET(CLIENT_HDRS
    ${CLIENT_INCLUDE}/Game.hpp
)

add_executable(Client ${CLIENT_SRCS} ${CLIENT_HDRS})

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