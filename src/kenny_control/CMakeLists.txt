cmake_minimum_required(VERSION 3.5)
project(kenny_control)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

################################################################################
# Find ament packages and libraries for ament and system dependencies
################################################################################
find_package(ament_cmake REQUIRED)
find_package(controller_manager REQUIRED)
# find_package(joint_state_controller REQUIRED)
find_package(robot_state_publisher REQUIRED)

################################################################################
# Install
################################################################################
install(DIRECTORY config launch include src
  DESTINATION share/${PROJECT_NAME}
)

################################################################################
# Macro for ament package
################################################################################
ament_package()
