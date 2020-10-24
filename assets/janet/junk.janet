(import assets/janet/config :as config)

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

(defn shrink-rect
      "Takes a rectangle and shrinks it by an amount on all sides"
      [rect shrink]
      [(+ (rect 0) shrink)
       (+ (rect 1) shrink)
       (- (rect 2) (* shrink 2))
       (- (rect 3) (* shrink 2))])

(defn draw-panel
      "Draws a panel with default border and background and returns inner bounds"
      [screen bounds]
      (draw-border screen bounds config/border-sprite config/border-width)
      (def inner-bounds (shrink-rect bounds config/border-width))
      (if (and (inner-bounds 0) (inner-bounds 1))
        (draw-rect screen inner-bounds config/panel-sprite))
      inner-bounds)

