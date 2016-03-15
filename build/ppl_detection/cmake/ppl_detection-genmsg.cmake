# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "ppl_detection: 2 messages, 0 services")

set(MSG_I_FLAGS "-Ippl_detection:/home/c3mx/robot/src/ppl_detection/msg;-Istd_msgs:/opt/ros/jade/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/jade/share/geometry_msgs/cmake/../msg;-Ivisualization_msgs:/opt/ros/jade/share/visualization_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(ppl_detection_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/c3mx/robot/src/ppl_detection/msg/Human.msg" NAME_WE)
add_custom_target(_ppl_detection_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ppl_detection" "/home/c3mx/robot/src/ppl_detection/msg/Human.msg" ""
)

get_filename_component(_filename "/home/c3mx/robot/src/ppl_detection/msg/Tracker.msg" NAME_WE)
add_custom_target(_ppl_detection_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ppl_detection" "/home/c3mx/robot/src/ppl_detection/msg/Tracker.msg" "ppl_detection/Human:std_msgs/Header"
)

#
#  langs = gencpp;geneus;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(ppl_detection
  "/home/c3mx/robot/src/ppl_detection/msg/Human.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ppl_detection
)
_generate_msg_cpp(ppl_detection
  "/home/c3mx/robot/src/ppl_detection/msg/Tracker.msg"
  "${MSG_I_FLAGS}"
  "/home/c3mx/robot/src/ppl_detection/msg/Human.msg;/opt/ros/jade/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ppl_detection
)

### Generating Services

### Generating Module File
_generate_module_cpp(ppl_detection
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ppl_detection
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(ppl_detection_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(ppl_detection_generate_messages ppl_detection_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/c3mx/robot/src/ppl_detection/msg/Human.msg" NAME_WE)
add_dependencies(ppl_detection_generate_messages_cpp _ppl_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/c3mx/robot/src/ppl_detection/msg/Tracker.msg" NAME_WE)
add_dependencies(ppl_detection_generate_messages_cpp _ppl_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ppl_detection_gencpp)
add_dependencies(ppl_detection_gencpp ppl_detection_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ppl_detection_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(ppl_detection
  "/home/c3mx/robot/src/ppl_detection/msg/Human.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ppl_detection
)
_generate_msg_eus(ppl_detection
  "/home/c3mx/robot/src/ppl_detection/msg/Tracker.msg"
  "${MSG_I_FLAGS}"
  "/home/c3mx/robot/src/ppl_detection/msg/Human.msg;/opt/ros/jade/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ppl_detection
)

### Generating Services

### Generating Module File
_generate_module_eus(ppl_detection
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ppl_detection
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(ppl_detection_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(ppl_detection_generate_messages ppl_detection_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/c3mx/robot/src/ppl_detection/msg/Human.msg" NAME_WE)
add_dependencies(ppl_detection_generate_messages_eus _ppl_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/c3mx/robot/src/ppl_detection/msg/Tracker.msg" NAME_WE)
add_dependencies(ppl_detection_generate_messages_eus _ppl_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ppl_detection_geneus)
add_dependencies(ppl_detection_geneus ppl_detection_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ppl_detection_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(ppl_detection
  "/home/c3mx/robot/src/ppl_detection/msg/Human.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ppl_detection
)
_generate_msg_lisp(ppl_detection
  "/home/c3mx/robot/src/ppl_detection/msg/Tracker.msg"
  "${MSG_I_FLAGS}"
  "/home/c3mx/robot/src/ppl_detection/msg/Human.msg;/opt/ros/jade/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ppl_detection
)

### Generating Services

### Generating Module File
_generate_module_lisp(ppl_detection
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ppl_detection
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(ppl_detection_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(ppl_detection_generate_messages ppl_detection_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/c3mx/robot/src/ppl_detection/msg/Human.msg" NAME_WE)
add_dependencies(ppl_detection_generate_messages_lisp _ppl_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/c3mx/robot/src/ppl_detection/msg/Tracker.msg" NAME_WE)
add_dependencies(ppl_detection_generate_messages_lisp _ppl_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ppl_detection_genlisp)
add_dependencies(ppl_detection_genlisp ppl_detection_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ppl_detection_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(ppl_detection
  "/home/c3mx/robot/src/ppl_detection/msg/Human.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ppl_detection
)
_generate_msg_py(ppl_detection
  "/home/c3mx/robot/src/ppl_detection/msg/Tracker.msg"
  "${MSG_I_FLAGS}"
  "/home/c3mx/robot/src/ppl_detection/msg/Human.msg;/opt/ros/jade/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ppl_detection
)

### Generating Services

### Generating Module File
_generate_module_py(ppl_detection
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ppl_detection
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(ppl_detection_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(ppl_detection_generate_messages ppl_detection_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/c3mx/robot/src/ppl_detection/msg/Human.msg" NAME_WE)
add_dependencies(ppl_detection_generate_messages_py _ppl_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/c3mx/robot/src/ppl_detection/msg/Tracker.msg" NAME_WE)
add_dependencies(ppl_detection_generate_messages_py _ppl_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ppl_detection_genpy)
add_dependencies(ppl_detection_genpy ppl_detection_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ppl_detection_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ppl_detection)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ppl_detection
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(ppl_detection_generate_messages_cpp std_msgs_generate_messages_cpp)
add_dependencies(ppl_detection_generate_messages_cpp geometry_msgs_generate_messages_cpp)
add_dependencies(ppl_detection_generate_messages_cpp visualization_msgs_generate_messages_cpp)

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ppl_detection)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ppl_detection
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
add_dependencies(ppl_detection_generate_messages_eus std_msgs_generate_messages_eus)
add_dependencies(ppl_detection_generate_messages_eus geometry_msgs_generate_messages_eus)
add_dependencies(ppl_detection_generate_messages_eus visualization_msgs_generate_messages_eus)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ppl_detection)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ppl_detection
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(ppl_detection_generate_messages_lisp std_msgs_generate_messages_lisp)
add_dependencies(ppl_detection_generate_messages_lisp geometry_msgs_generate_messages_lisp)
add_dependencies(ppl_detection_generate_messages_lisp visualization_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ppl_detection)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ppl_detection\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ppl_detection
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(ppl_detection_generate_messages_py std_msgs_generate_messages_py)
add_dependencies(ppl_detection_generate_messages_py geometry_msgs_generate_messages_py)
add_dependencies(ppl_detection_generate_messages_py visualization_msgs_generate_messages_py)
