cmake_minimum_required(VERSION 3.12)

project(Stem_exe)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


# Make sure our local CMake Modules path comes first
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake/Modules)

##seting file pathes
file(GLOB Cpps ./*.cpp ./*.qmodel ./*.md ./api/*.cpp)


set (CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++17 -D__STRICT_ANSI__")

find_package (Threads REQUIRED)
find_package (inja REQUIRED)


# adding mongo client library
find_package(libbsoncxx REQUIRED)
find_package(libmongocxx REQUIRED)
include_directories(${LIBBSONCXX_INCLUDE_DIRS} ${LIBMONGOCXX_INCLUDE_DIRS} )

if(NOT Boost_FOUND)
  message(FATAL "Boost not found")
endif()

  add_subdirectory(database)
#  add_subdirectory(controllers)
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable(${PROJECT_NAME} "main.cpp" ${Cpps} )
#  add_dependencies(${PROJECT_NAME} database)

  target_link_libraries(${PROJECT_NAME}
    Boost::date_time
    Boost::system
    Boost::filesystem
    Boost::iostreams
    Boost::thread
    #    Boost::mpi
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

    # database
    fonqri::database

    fonqri::library
    )
message("FONQRI TEST ")
message(fonqri::database)

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME OFF)
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
