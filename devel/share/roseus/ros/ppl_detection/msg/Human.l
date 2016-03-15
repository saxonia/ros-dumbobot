;; Auto-generated. Do not edit!


(when (boundp 'ppl_detection::Human)
  (if (not (find-package "PPL_DETECTION"))
    (make-package "PPL_DETECTION"))
  (shadow 'Human (find-package "PPL_DETECTION")))
(unless (find-package "PPL_DETECTION::HUMAN")
  (make-package "PPL_DETECTION::HUMAN"))

(in-package "ROS")
;;//! \htmlinclude Human.msg.html


(defclass ppl_detection::Human
  :super ros::object
  :slots (_tracking_no _pos_x _pos_y _pos_z _distance ))

(defmethod ppl_detection::Human
  (:init
   (&key
    ((:tracking_no __tracking_no) 0)
    ((:pos_x __pos_x) 0.0)
    ((:pos_y __pos_y) 0.0)
    ((:pos_z __pos_z) 0.0)
    ((:distance __distance) 0.0)
    )
   (send-super :init)
   (setq _tracking_no (round __tracking_no))
   (setq _pos_x (float __pos_x))
   (setq _pos_y (float __pos_y))
   (setq _pos_z (float __pos_z))
   (setq _distance (float __distance))
   self)
  (:tracking_no
   (&optional __tracking_no)
   (if __tracking_no (setq _tracking_no __tracking_no)) _tracking_no)
  (:pos_x
   (&optional __pos_x)
   (if __pos_x (setq _pos_x __pos_x)) _pos_x)
  (:pos_y
   (&optional __pos_y)
   (if __pos_y (setq _pos_y __pos_y)) _pos_y)
  (:pos_z
   (&optional __pos_z)
   (if __pos_z (setq _pos_z __pos_z)) _pos_z)
  (:distance
   (&optional __distance)
   (if __distance (setq _distance __distance)) _distance)
  (:serialization-length
   ()
   (+
    ;; int32 _tracking_no
    4
    ;; float32 _pos_x
    4
    ;; float32 _pos_y
    4
    ;; float32 _pos_z
    4
    ;; float32 _distance
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _tracking_no
       (write-long _tracking_no s)
     ;; float32 _pos_x
       (sys::poke _pos_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pos_y
       (sys::poke _pos_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pos_z
       (sys::poke _pos_z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _distance
       (sys::poke _distance (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _tracking_no
     (setq _tracking_no (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _pos_x
     (setq _pos_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pos_y
     (setq _pos_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pos_z
     (setq _pos_z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _distance
     (setq _distance (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get ppl_detection::Human :md5sum-) "6cb5260ec06aeaff8021eb127c0c79ac")
(setf (get ppl_detection::Human :datatype-) "ppl_detection/Human")
(setf (get ppl_detection::Human :definition-)
      "int32 tracking_no
float32 pos_x
float32 pos_y
float32 pos_z
float32 distance

")



(provide :ppl_detection/Human "6cb5260ec06aeaff8021eb127c0c79ac")


