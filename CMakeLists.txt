cmake_minimum_required(VERSION 3.12)

project(MongodbOdl)

find_package(Boost 1.70 REQUIRED COMPONENTS
  date_time
  system
  filesystem
  iostreams
  iostreams
  thread
  serialization
  )

add_subdirectory(src)
add_subdirectory(library)
