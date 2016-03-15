;; Auto-generated. Do not edit!


(when (boundp 'ppl_detection::Tracker)
  (if (not (find-package "PPL_DETECTION"))
    (make-package "PPL_DETECTION"))
  (shadow 'Tracker (find-package "PPL_DETECTION")))
(unless (find-package "PPL_DETECTION::TRACKER")
  (make-package "PPL_DETECTION::TRACKER"))

(in-package "ROS")
;;//! \htmlinclude Tracker.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass ppl_detection::Tracker
  :super ros::object
  :slots (_header _human ))

(defmethod ppl_detection::Tracker
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:human __human) (let (r) (dotimes (i 0) (push (instance ppl_detection::Human :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _human __human)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:human
   (&rest __human)
   (if (keywordp (car __human))
       (send* _human __human)
     (progn
       (if __human (setq _human (car __human)))
       _human)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; ppl_detection/Human[] _human
    (apply #'+ (send-all _human :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; ppl_detection/Human[] _human
     (write-long (length _human) s)
     (dolist (elem _human)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; ppl_detection/Human[] _human
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _human (let (r) (dotimes (i n) (push (instance ppl_detection::Human :init) r)) r))
     (dolist (elem- _human)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get ppl_detection::Tracker :md5sum-) "3ddcc20a6bcdf88fc6a57af1ba99d938")
(setf (get ppl_detection::Tracker :datatype-) "ppl_detection/Tracker")
(setf (get ppl_detection::Tracker :definition-)
      "Header header
Human[] human

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: ppl_detection/Human
int32 tracking_no
float32 pos_x
float32 pos_y
float32 pos_z
float32 distance

")



(provide :ppl_detection/Tracker "3ddcc20a6bcdf88fc6a57af1ba99d938")


