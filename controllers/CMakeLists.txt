cmake_minimum_required(VERSION 3.12)

project(controllers)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


file(GLOB ControllersHeaders ./collection/*/*.hpp ./collection/*/*.h ./user/*.hpp ./user/*.h)
file(GLOB ControllersCpps ./user/*.cpp ./collection/*/*.cpp)


set (CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++17 -D__STRICT_ANSI__")

find_package (Threads REQUIRED)

# adding mongo client library
find_package(libbsoncxx REQUIRED)
find_package(libmongocxx REQUIRED)
include_directories(${LIBBSONCXX_INCLUDE_DIRS} ${LIBMONGOCXX_INCLUDE_DIRS} )


find_package(Boost 1.70 REQUIRED COMPONENTS
  date_time
  system
  filesystem
  iostreams
  iostreams
  thread
  serialization
  )


if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_library(${PROJECT_NAME} ${ControllersHeaders} ${ControllersCpps} )
  target_link_libraries(${PROJECT_NAME}
    Boost::date_time
    Boost::system
    Boost::filesystem
    Boost::iostreams
    Boost::thread
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_SYSTEM_LIBRARY}
    ${MPI_CXX_LIBRARIES}
    ${Boost_LIBRARIES}

    ${CMAKE_THREAD_LIBS_INIT}
    ${LIBBSONCXX_LIBRARIES}
    ${LIBMONGOCXX_LIBRARIES}

    h2o
    ssl
    crypto
    uv
    pthread
    z
    # stl filesystem
    stdc++fs
    database
    )

endif(Boost_FOUND)

