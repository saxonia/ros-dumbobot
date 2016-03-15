
(cl:in-package :asdf)

(defsystem "ppl_detection-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Tracker" :depends-on ("_package_Tracker"))
    (:file "_package_Tracker" :depends-on ("_package"))
    (:file "Human" :depends-on ("_package_Human"))
    (:file "_package_Human" :depends-on ("_package"))
  ))