cmake_minimum_required(VERSION 3.12)
PROJECT(mongo_rest_interface)

find_package(Boost 1.70 REQUIRED COMPONENTS
  date_time
  system
  filesystem
  iostreams
  iostreams
  thread
  serialization
  program_options
  log
  )

#for boost.log
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)


find_package (Threads REQUIRED)
find_package (inja REQUIRED)

#find_package(dragon REQUIRED)
# adding mongo client library
find_package(libbsoncxx REQUIRED)
find_package(libmongocxx REQUIRED)

add_subdirectory(runtime)
add_subdirectory(database)
add_subdirectory(server)
add_subdirectory(stem)
