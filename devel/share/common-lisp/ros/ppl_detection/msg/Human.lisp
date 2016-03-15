; Auto-generated. Do not edit!


(cl:in-package ppl_detection-msg)


;//! \htmlinclude Human.msg.html

(cl:defclass <Human> (roslisp-msg-protocol:ros-message)
  ((tracking_no
    :reader tracking_no
    :initarg :tracking_no
    :type cl:integer
    :initform 0)
   (pos_x
    :reader pos_x
    :initarg :pos_x
    :type cl:float
    :initform 0.0)
   (pos_y
    :reader pos_y
    :initarg :pos_y
    :type cl:float
    :initform 0.0)
   (pos_z
    :reader pos_z
    :initarg :pos_z
    :type cl:float
    :initform 0.0)
   (distance
    :reader distance
    :initarg :distance
    :type cl:float
    :initform 0.0))
)

(cl:defclass Human (<Human>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Human>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Human)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ppl_detection-msg:<Human> is deprecated: use ppl_detection-msg:Human instead.")))

(cl:ensure-generic-function 'tracking_no-val :lambda-list '(m))
(cl:defmethod tracking_no-val ((m <Human>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ppl_detection-msg:tracking_no-val is deprecated.  Use ppl_detection-msg:tracking_no instead.")
  (tracking_no m))

(cl:ensure-generic-function 'pos_x-val :lambda-list '(m))
(cl:defmethod pos_x-val ((m <Human>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ppl_detection-msg:pos_x-val is deprecated.  Use ppl_detection-msg:pos_x instead.")
  (pos_x m))

(cl:ensure-generic-function 'pos_y-val :lambda-list '(m))
(cl:defmethod pos_y-val ((m <Human>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ppl_detection-msg:pos_y-val is deprecated.  Use ppl_detection-msg:pos_y instead.")
  (pos_y m))

(cl:ensure-generic-function 'pos_z-val :lambda-list '(m))
(cl:defmethod pos_z-val ((m <Human>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ppl_detection-msg:pos_z-val is deprecated.  Use ppl_detection-msg:pos_z instead.")
  (pos_z m))

(cl:ensure-generic-function 'distance-val :lambda-list '(m))
(cl:defmethod distance-val ((m <Human>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ppl_detection-msg:distance-val is deprecated.  Use ppl_detection-msg:distance instead.")
  (distance m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Human>) ostream)
  "Serializes a message object of type '<Human>"
  (cl:let* ((signed (cl:slot-value msg 'tracking_no)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pos_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pos_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pos_z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'distance))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Human>) istream)
  "Deserializes a message object of type '<Human>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'tracking_no) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pos_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pos_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pos_z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'distance) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Human>)))
  "Returns string type for a message object of type '<Human>"
  "ppl_detection/Human")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Human)))
  "Returns string type for a message object of type 'Human"
  "ppl_detection/Human")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Human>)))
  "Returns md5sum for a message object of type '<Human>"
  "6cb5260ec06aeaff8021eb127c0c79ac")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Human)))
  "Returns md5sum for a message object of type 'Human"
  "6cb5260ec06aeaff8021eb127c0c79ac")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Human>)))
  "Returns full string definition for message of type '<Human>"
  (cl:format cl:nil "int32 tracking_no~%float32 pos_x~%float32 pos_y~%float32 pos_z~%float32 distance~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Human)))
  "Returns full string definition for message of type 'Human"
  (cl:format cl:nil "int32 tracking_no~%float32 pos_x~%float32 pos_y~%float32 pos_z~%float32 distance~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Human>))
  (cl:+ 0
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Human>))
  "Converts a ROS message object to a list"
  (cl:list 'Human
    (cl:cons ':tracking_no (tracking_no msg))
    (cl:cons ':pos_x (pos_x msg))
    (cl:cons ':pos_y (pos_y msg))
    (cl:cons ':pos_z (pos_z msg))
    (cl:cons ':distance (distance msg))
))
