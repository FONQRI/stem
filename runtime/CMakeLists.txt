cmake_minimum_required(VERSION 3.12)

project(stem_runtime)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


file(GLOB ControllersHeaders ./*.hpp ./*.h)
file(GLOB ControllersCpps ./*.cpp)


set (CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++17 -D__STRICT_ANSI__")

include_directories(${LIBBSONCXX_INCLUDE_DIRS} ${LIBMONGOCXX_INCLUDE_DIRS} ${ario_server_libs_INCLUDE_DIR})


if(NOT Boost_FOUND)
  message(FATAL "Boost Not Found")
endif()
include_directories(${Boost_INCLUDE_DIRS})
add_library(${PROJECT_NAME} STATIC  ${ControllersCpps} )
add_library(stem::runtime ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PUBLIC  ${PROJECT_SOURCE_DIR}/include
  )

target_link_libraries(${PROJECT_NAME}
  Boost::date_time
  Boost::system
  Boost::filesystem
  Boost::iostreams
  Boost::thread
  ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_LIBRARIES}

  ${CMAKE_THREAD_LIBS_INIT}
  # stl filesystem
  stdc++fs
  yaml-cpp
  log4cpp
  )
#  target_include_directories(${PROJECT_NAME}
#/
#    )


