# This file is for doing 2d vector stuff. It should only depend on util.janet
# if anything.

(import script/util :as util)

(defn *
  "multiplies two 2d vectors and returns the result"
  [a b]
  (util/cloop 2 i (* (a i) (b i))))

(defn +
  "adds two 2d vectors and returns the result"
  [a b]
  (util/cloop 2 i (+ (a i) (b i))))

(defn -
  "Subtracts one vector from another and returns the result"
  [a b]
  (util/cloop 2 i (- (a i) (b i))))

(defn sign
  "Makes the items in a vector be signed as requested in another one"
  [in signs]
  (util/cloop 2 i
            (if (< (signs i) 0)
              (* (math/abs (in i)) -1)
              (if (> (signs i) 0)
                (math/abs (in i))
                (in i)))))

(defn axis
  "Takes a keyword what names a vector, right, and kinda just turns it into a
  two dimensional unit vector following that axis in a positive manner"
  [axis]
  (case axis
    :horizontal [1 0]
    :vertical [0 1]
    (error (string/format "%s is not a valid axis" axis))))

(defn fit-ratio
  "Finds a single amount to multiply a 2d vector by to make it fit as large as
  possible inside the bounds of another 2d vector while maintaining it's slope"
  [vector bounds]
  (min ;(util/cloop 2 i (/ (bounds i) (vector i)))))

