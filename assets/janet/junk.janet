(import assets/janet/config :as config)

(defn is-whitespace
  "Evaluates to a boolean for whether given character is whitespace"
  [c]
  (or (= c 32) (= c 10)))

(defmacro text
  "Joins lines of text without newlines unless empty string or explicit"
  [& str]
  (string ;(seq [i :in str] (if (= 0 (length i))
                              "\n"
                              (if (is-whitespace (i -1))
                                i
                                (string i " "))))))

(defmacro def-text
  "Defines output of text into a constant to save space"
  [name & str]
  ~(def ,name (text ,;str)))

(defmacro vectored
  "Does everything twice with an index variable"
  [var content]
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
      (string/split " " text))

(defn wrap-tokens
      ``
      Takes a list of tokens and merges them into one string such that they
      do not exceed the required number of characters per line. Adds a newline
      on the end as well.
      ``
      [tokens width]
      (var i 0)
      (var buffer (buffer/new 32))
      (each token
            tokens
            [(if (< width (+ i (length token)))
               [(set i 0)
                (buffer/push-string buffer "\n")])
             (set i (+ i (length token) 1))
             (buffer/push-string buffer token)
             (buffer/push-string buffer " ")])
      (buffer/push-string buffer "\n")
      buffer)

(defn wrap-text
      "Takes some text and wraps it based on a given font"
      [text font width]
      (var buffer (buffer/new 256))
      (def chars (/ width (/ (font 2) 16)))
      (each line
            (string/split "\n" text)
            (buffer/push-string buffer (wrap-tokens (tokenise line) chars)))
      (string buffer))

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

