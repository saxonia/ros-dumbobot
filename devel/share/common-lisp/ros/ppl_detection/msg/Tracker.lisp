; Auto-generated. Do not edit!


(cl:in-package ppl_detection-msg)


;//! \htmlinclude Tracker.msg.html

(cl:defclass <Tracker> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (human
    :reader human
    :initarg :human
    :type (cl:vector ppl_detection-msg:Human)
   :initform (cl:make-array 0 :element-type 'ppl_detection-msg:Human :initial-element (cl:make-instance 'ppl_detection-msg:Human))))
)

(cl:defclass Tracker (<Tracker>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Tracker>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Tracker)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ppl_detection-msg:<Tracker> is deprecated: use ppl_detection-msg:Tracker instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Tracker>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ppl_detection-msg:header-val is deprecated.  Use ppl_detection-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'human-val :lambda-list '(m))
(cl:defmethod human-val ((m <Tracker>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ppl_detection-msg:human-val is deprecated.  Use ppl_detection-msg:human instead.")
  (human m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Tracker>) ostream)
  "Serializes a message object of type '<Tracker>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'human))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'human))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Tracker>) istream)
  "Deserializes a message object of type '<Tracker>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'human) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'human)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'ppl_detection-msg:Human))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Tracker>)))
  "Returns string type for a message object of type '<Tracker>"
  "ppl_detection/Tracker")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Tracker)))
  "Returns string type for a message object of type 'Tracker"
  "ppl_detection/Tracker")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Tracker>)))
  "Returns md5sum for a message object of type '<Tracker>"
  "3ddcc20a6bcdf88fc6a57af1ba99d938")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Tracker)))
  "Returns md5sum for a message object of type 'Tracker"
  "3ddcc20a6bcdf88fc6a57af1ba99d938")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Tracker>)))
  "Returns full string definition for message of type '<Tracker>"
  (cl:format cl:nil "Header header~%Human[] human~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: ppl_detection/Human~%int32 tracking_no~%float32 pos_x~%float32 pos_y~%float32 pos_z~%float32 distance~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Tracker)))
  "Returns full string definition for message of type 'Tracker"
  (cl:format cl:nil "Header header~%Human[] human~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: ppl_detection/Human~%int32 tracking_no~%float32 pos_x~%float32 pos_y~%float32 pos_z~%float32 distance~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Tracker>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'human) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Tracker>))
  "Converts a ROS message object to a list"
  (cl:list 'Tracker
    (cl:cons ':header (header msg))
    (cl:cons ':human (human msg))
))
