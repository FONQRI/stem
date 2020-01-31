cmake_minimum_required(VERSION 3.12)

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

add_subdirectory(src)
add_subdirectory(library)
