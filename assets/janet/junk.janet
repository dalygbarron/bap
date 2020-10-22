(defmacro vectored [content]
  ~(tuple (do (def index 0) ,content)
          (do (def index 1) ,content)))

(defn mult-vec
  "multiplies two 2d vectors and returns the result"
  [a b]
  (vectored (* (a index) (b index))))

(defn add-vec
      "adds two 2d vectors and returns the result"
      [a b]
      (vectored (+ (a index) (b index))))

(defn sub-vec
      "Subtracts one vector from another and returns the result"
      [a b]
      (vectored (- (a index) (b index))))

(defn sign-vec
      "Makes the items in a vector be signed as requested in another one"
      [in signs]
      (vectored (if (= (signs index) -1)
        (* (math/abs (in index)) -1)
        (if (= (signs index) 1)
          (math/abs (in index))
          (in index)))))

(defn print-vec
      "prints a vector in a readable form"
      [vec]
      (printf "(%d %d)" (vec 0) (vec 1)))
