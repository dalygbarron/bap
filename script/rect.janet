# This file is for doing rectangle based stuff. It should only really depend on
# the main util file since it is fairly useful itself.

(import script/util :as util)

(def- normal-plus +)
(def- normal-minus -)
(def- normal-times *)
(def- normal-div /)

(defn make
  "Makes a rect out of two 2d vectors representing the position and size of the
  rectangle"
  [pos size]
  (assert (and (>= (length pos) 2) (>= (length size) 2))
          "Pos and Size must have at least two elements")
  [(pos 0) (pos 1) (size 0) (size 1)])

(defn size
  "Gives you a 2d vector representing a rectangle's width and height"
  [rect]
  [(rect 2) (rect 3)])

(defn pos
  "Gives you a 2d vector representing the rectangle's position"
  [rect]
  [(rect 0) (rect 1)])

(defn shrink
  "Takes a rectangle and shrinks it by an amount on all sides"
  [rect amount]
  [(normal-plus (rect 0) amount)
   (normal-plus (rect 1) amount)
   (normal-minus (rect 2) (normal-times amount 2))
   (normal-minus (rect 3) (normal-times amount 2))])

(defn +
  "Adds two rectangles together and returns the result"
  [a b]
  (util/cloop 4 i (normal-plus (a i) (b i))))

(defn -
  "Subtracts a rectangle from another itemwise"
  [a b]
  (util/cloop 4 i (normal-minus (a i) (b i))))

(defn *
  "Multiplies two rectangles piecewise"
  [a b]
  (util/cloop 4 i (normal-times (a i) (b i))))

(defn /
  "Divides two rectangles piecewise"
  [a b]
  (util/cloop 4 i (normal-div (a i) (b i))))

(defn floor
  "Returns the given rect with all it's bits floored"
  [vector]
  (util/cloop 4 i (math/floor (vector i))))
