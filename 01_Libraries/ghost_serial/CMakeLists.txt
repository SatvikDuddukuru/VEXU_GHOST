cmake_minimum_required(VERSION 3.5)
project(ghost_serial)

#########################
#### Compile Options ####
#########################

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# set(CMAKE_BUILD_TYPE "DEBUG")
set(CMAKE_BUILD_TYPE "RELEASE")

if(CMAKE_BUILD_TYPE EQUAL "DEBUG")
  add_compile_options(-g -O0)
endif(CMAKE_BUILD_TYPE EQUAL "DEBUG")

add_compile_options(-DGHOST_DEBUG_VERBOSE)

# Device specific flag for code portability between Coprocessor, V5 Brain, and TM4C
add_definitions(-DGHOST_JETSON=1)
add_definitions(-DGHOST_V5_BRAIN=2)
add_definitions(-DGHOST_TM4C=3)

add_definitions(-DGHOST_DEVICE=1)

######################
#### Dependencies ####
######################
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_gtest REQUIRED)

find_package(rclcpp REQUIRED)
find_package(ghost_msgs REQUIRED)

include_directories(include)

####################
### Serial Utils ###
####################
add_library(serial_utils SHARED
  src/serial_utils/bitmasks.cpp
)
target_include_directories(serial_utils
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_export_targets(serial_utils HAS_LIBRARY_TARGET)
install(
  TARGETS serial_utils
  EXPORT serial_utils
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

####################
### COBS Library ###
####################
add_library(cobs SHARED
  src/cobs/cobs.cpp
)
target_include_directories(cobs
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_export_targets(cobs HAS_LIBRARY_TARGET)
install(
  TARGETS cobs
  EXPORT cobs
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

##################
### Msg Parser ###
##################
add_library(msg_parser SHARED
  src/msg_parser/msg_parser.cpp
)
target_link_libraries(msg_parser
  cobs
)
target_include_directories(msg_parser
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_export_targets(msg_parser HAS_LIBRARY_TARGET)
install(
  TARGETS msg_parser
  EXPORT msg_parser
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

######################
### Serial Library ###
######################
add_library(jetson_serial_base SHARED
  src/base_interfaces/generic_serial_base.cpp
  src/base_interfaces/jetson_serial_base.cpp
)
target_link_libraries(jetson_serial_base
  serial_utils  
  cobs
  msg_parser
)
target_include_directories(jetson_serial_base
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_export_targets(jetson_serial_base HAS_LIBRARY_TARGET)
install(
  TARGETS jetson_serial_base
  EXPORT jetson_serial_base
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

###############
### Testing ###
###############
ament_add_gtest(test_cobs test/test_cobs.cpp)
target_link_libraries(test_cobs
  cobs
  gtest
)
ament_add_gtest(test_msg_parser test/test_msg_parser.cpp)
target_link_libraries(test_msg_parser
  msg_parser
  gtest
)

###############
### Install ###
###############
install(
  DIRECTORY include/
  DESTINATION include
)

ament_package()
