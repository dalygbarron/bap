(import assets/janet/junk :as junk)

(defmacro vectored [content]
  (tuple 'do (def index 0) content)
  (tuple 'do (def index 1) content))


(defn mult-vec
  "multiplies two 2d vectors and returns the result"
  [a b]
  [(* (a 0) (b 0)) (* (a 1) (b 1))])

(defn add-vec
      "adds two 2d vectors and returns the result"
      [a b]
      [(vectored (+ (a index) (b index)))])

(defn sign-vec
      "Makes the items in a vector be signed as requested in another one"
      [in signs]
      [(vectored (if (= (signs index) -1)
         (* (math/abs (signs index)) -1)
         (if (= (signs index) 1)
           (math/abs (signs 0))
           (signs index))))])

(fn [screen message]
    (def box (get-sprite screen "panel"))
    (var width [50 50])
    (var pos [300 300])
    (var vel [5 -9])
    (print message)
    (while true
           (set pos (add-vec pos vel))
           (draw-border screen [(pos 0) (pos 1) (width 0) (width 1)] box 4)
           (if (< (pos 0) 0)
               (set vel (mult-vec vel [-1 1])))
           (if (< (pos 1) 0)
               (set vel (mult-vec vel [1 -1])))
           (if (> (pos 0) (- 768 (width 0)))
               (set vel (mult-vec vel [-1 1])))
           (if (> (pos 1) (- 480 (width 1)))
               (set vel (mult-vec vel [1 -1])))
           (yield 1)))
