(import assets/janet/junk :as junk)

(fn [screen]
    (def width [50 50])
    (var pos @[300 300])
    (var vel @[5 -9])
    (while true
           (junk/add-array pos vel)
           (drawBorder screen
                       [(pos 0) (pos 1) (width 0) (width 1)]
                       [85 120 32 32]
                       4)
           (if (< (pos 0) 0)
               (set (vel 0) (math/abs (vel 0))))
           (if (< (pos 1) 0)
               (set (vel 1) (math/abs (vel 1))))
           (if (> (pos 0) (- 768 (width 0)))
               (set (vel 0) (* -1 (math/abs (vel 0)))))
           (if (> (pos 1) (- 480 (width 1)))
               (set (vel 1) (* -1 (math/abs (vel 1)))))
           (yield 1)))
