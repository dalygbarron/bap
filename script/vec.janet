# This file is for doing 2d vector stuff. It should only depend on util.janet
# if anything.

(import script/util :as util)

(def- normal-plus +)
(def- normal-minus -)
(def- normal-times *)
(def- normal-div /)

(defn +
  "adds two 2d vectors and returns the result"
  [a b]
  (util/cloop 2 i (normal-plus (a i) (b i))))

(defn -
  "Subtracts one vector from another and returns the result"
  [a b]
  (util/cloop 2 i (normal-minus (a i) (b i))))

(defn *
  "multiplies two 2d vectors and returns the result"
  [a b]
  (util/cloop 2 i (normal-times (a i) (b i))))

(defn /
  "Divides one vector by another itemwise"
  [a b]
  (util/cloop 2 i (normal-div (a i) (b i))))

(defn sign
  "Makes the items in a vector be signed as requested in another one"
  [v signs]
  (util/cloop 2 i
            (if (< (signs i) 0) 
              (normal-times (math/abs (v i)) -1)
              (if (> (signs i) 0)
                (math/abs (v i))
                (v i)))))

(defn axis
  "Takes a keyword what names a vector, right, and kinda just turns it into a
  two dimensional unit vector following that axis in a positive manner"
  [a]
  (case a
    :horizontal [1 0]
    :vertical [0 1]
    (error (string/format "%q is not a valid axis" a))))

(defn fit-ratio
  "Finds a single amount to multiply a 2d vector by to make it fit as large as
  possible inside the bounds of another 2d vector while maintaining it's slope"
  [vector bounds]
  (min ;(/ bounds vector)))

(defn floor
  "Returns the given vector with both it's dimensions floored into an int"
  [vector]
  (util/cloop 2 i (math/floor (vector i))))

(defn wrap
  "wraps a vector between 0 and another vector ya know what I mean"
  [vector inside]
  (util/cloop 2 i (util/wrap (vector i) (inside i))))
