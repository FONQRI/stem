cmake_minimum_required(VERSION 3.12)

project(ario_server_libs)

file(GLOB Cpps ./lib/*.cpp)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++17 -D__STRICT_ANSI__")

find_package (Threads REQUIRED)

# adding mongo client library
find_package(libbsoncxx REQUIRED)
find_package(libmongocxx REQUIRED)
include_directories(${LIBBSONCXX_INCLUDE_DIRS} ${LIBMONGOCXX_INCLUDE_DIRS} )

if(Boost_FOUND)


  include_directories(${Boost_INCLUDE_DIRS})
  add_library(${PROJECT_NAME} ${Cpps} )

  # Add a library with the above sources
  add_library(fonqri::library ALIAS ${PROJECT_NAME})

  target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    )

  target_include_directories( ${PROJECT_NAME}
      PUBLIC ${PROJECT_SOURCE_DIR}/include
  )

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
    )
endif(Boost_FOUND)

