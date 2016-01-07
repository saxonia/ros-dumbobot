# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(WARNING "Invoking generate_messages() without having added any message or service file before.
You should either add add_message_files() and/or add_service_files() calls or remove the invocation of generate_messages().")
message(STATUS "ros_dumbobot: 0 messages, 0 services")

set(MSG_I_FLAGS "-Istd_msgs:/opt/ros/jade/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/jade/share/geometry_msgs/cmake/../msg;-Inav_msgs:/opt/ros/jade/share/nav_msgs/cmake/../msg;-Iactionlib_msgs:/opt/ros/jade/share/actionlib_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(ros_dumbobot_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



#
#  langs = gencpp;geneus;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services

### Generating Module File
_generate_module_cpp(ros_dumbobot
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_dumbobot
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(ros_dumbobot_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(ros_dumbobot_generate_messages ros_dumbobot_generate_messages_cpp)

# add dependencies to all check dependencies targets

# target for backward compatibility
add_custom_target(ros_dumbobot_gencpp)
add_dependencies(ros_dumbobot_gencpp ros_dumbobot_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros_dumbobot_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages

### Generating Services

### Generating Module File
_generate_module_eus(ros_dumbobot
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_dumbobot
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(ros_dumbobot_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(ros_dumbobot_generate_messages ros_dumbobot_generate_messages_eus)

# add dependencies to all check dependencies targets

# target for backward compatibility
add_custom_target(ros_dumbobot_geneus)
add_dependencies(ros_dumbobot_geneus ros_dumbobot_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros_dumbobot_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services

### Generating Module File
_generate_module_lisp(ros_dumbobot
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_dumbobot
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(ros_dumbobot_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(ros_dumbobot_generate_messages ros_dumbobot_generate_messages_lisp)

# add dependencies to all check dependencies targets

# target for backward compatibility
add_custom_target(ros_dumbobot_genlisp)
add_dependencies(ros_dumbobot_genlisp ros_dumbobot_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros_dumbobot_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages

### Generating Services

### Generating Module File
_generate_module_py(ros_dumbobot
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_dumbobot
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(ros_dumbobot_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(ros_dumbobot_generate_messages ros_dumbobot_generate_messages_py)

# add dependencies to all check dependencies targets

# target for backward compatibility
add_custom_target(ros_dumbobot_genpy)
add_dependencies(ros_dumbobot_genpy ros_dumbobot_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros_dumbobot_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_dumbobot)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_dumbobot
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(ros_dumbobot_generate_messages_cpp std_msgs_generate_messages_cpp)
add_dependencies(ros_dumbobot_generate_messages_cpp geometry_msgs_generate_messages_cpp)
add_dependencies(ros_dumbobot_generate_messages_cpp nav_msgs_generate_messages_cpp)

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_dumbobot)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_dumbobot
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
add_dependencies(ros_dumbobot_generate_messages_eus std_msgs_generate_messages_eus)
add_dependencies(ros_dumbobot_generate_messages_eus geometry_msgs_generate_messages_eus)
add_dependencies(ros_dumbobot_generate_messages_eus nav_msgs_generate_messages_eus)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_dumbobot)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_dumbobot
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(ros_dumbobot_generate_messages_lisp std_msgs_generate_messages_lisp)
add_dependencies(ros_dumbobot_generate_messages_lisp geometry_msgs_generate_messages_lisp)
add_dependencies(ros_dumbobot_generate_messages_lisp nav_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_dumbobot)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_dumbobot\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_dumbobot
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(ros_dumbobot_generate_messages_py std_msgs_generate_messages_py)
add_dependencies(ros_dumbobot_generate_messages_py geometry_msgs_generate_messages_py)
add_dependencies(ros_dumbobot_generate_messages_py nav_msgs_generate_messages_py)
