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

(defn tokenise
      "takes a string and breaks it into an array based on whitespace"
      [text]
      text)

(defn wrap-text
      "Takes some text and wraps it based on a given font"
      [text font width]
      (def buffer @"")
      (each line
            (string/split text "\n")
            (progn (buffer/push-string (wrap-tokens (tokenise line) width))
                   (buffer/push-string "\n"))
      buffer)

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
      (def border (get-sprite config/border-sprite))
      (def panel (get-sprite config/panel-sprite))
      (draw-border screen bounds border config/border-width)
      (def inner-bounds (shrink-rect bounds config/border-width))
      (if (and (vectored i (> (inner-bounds i) 0)))
        (draw-rect screen inner-bounds panel))
      inner-bounds)

