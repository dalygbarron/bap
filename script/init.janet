(import script/gui :as gui)

(fn [] 
  (var going true)
  (while going
    (gui/say "Program" "Welcome to test. Press x to continue.")
    (set going (= (gui/say "Bongo"
                           "This is the end."
                           "Start again."
                           "Close") 0))))
