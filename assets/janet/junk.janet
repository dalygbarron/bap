(defmacro vectored [var content]
  ~(tuple (do (def ,var 0) ,content)
          (do (def ,var 1) ,content)))

(defn mult-vec
  "multiplies two 2d vectors and returns the result"
  [a b]
  (vectored i (* (a i) (b i))))

(defn add-vec
      "adds two 2d vectors and returns the result"
      [a b]
      (vectored i (+ (a i) (b i))))

(defn sub-vec
      "Subtracts one vector from another and returns the result"
      [a b]
      (vectored i (- (a i) (b i))))

(defn sign-vec
      "Makes the items in a vector be signed as requested in another one"
      [in signs]
      (vectored i
                (if (< (signs i) 0)
                  (* (math/abs (in i)) -1)
                  (if (> (signs i) 0)
                    (math/abs (in i))
                    (in i)))))

(defn print-vec
      "prints a vector in a readable form"
      [vec]
      (printf "(%d %d)" (vec 0) (vec 1)))
