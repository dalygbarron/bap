(import assets/janet/junk :as junk)

(fn [screen message]
    (def box (get-sprite screen "panel"))
    (var width [50 50])
    (var pos [300 300])
    (var vel [5 -9])
    (print message)
    (while true
           (set pos (junk/add-vec pos vel))
           (set width (junk/add-vec (junk/mult-vec (junk/sub-vec [(math/random) (math/random)]
                                                                 [0.5 0.5])
                                                   [6 6])
                                    width))
           (draw-border screen [(pos 0) (pos 1) (width 0) (width 1)] box 4)
           (if (< (pos 0) 0)
               (set vel (junk/sign-vec vel [1 0])))
           (if (< (pos 1) 0)
               (set vel (junk/sign-vec vel [0 1])))
           (if (> (pos 0) (- 768 (width 0)))
               (set vel (junk/sign-vec vel [-1 0])))
           (if (> (pos 1) (- 480 (width 1)))
               (set vel (junk/sign-vec vel [0 -1])))
           (yield 1)))
