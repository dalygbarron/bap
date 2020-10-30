(import script/junk :as junk)

(def- wrap-cache @{})

(defn- tokenise
  "takes a string and breaks it into an array based on whitespace"
  [text]
  (string/split " " text))

(defn- wrap-tokens
  "takes a list of tokens and merges them with newlines to fit width"
  [tokens width]
  (var i 0)
  (var buffer (buffer/new 32))
  (each token tokens
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
  (def cached-value (get wrap-cache [text font (math/ceil width)]))
  (if cached-value
    cached-value
    (do (var buffer (buffer/new 256))
      (def chars (/ width (/ (font 2) 16)))
      (each line (string/split "\n" text)
        (buffer/push-string buffer (wrap-tokens (tokenise line) chars)))
      (def out (string buffer))
      (put wrap-cache [text font (math/ceil width)] out)
      out)))

(defn make-panel-sprite
  "Makes a nice struct to represent the parts of a panel sprite"
  [background border width]
  {:background background :border border :width width})

(defn shrink-rect
  "Takes a rectangle and shrinks it by an amount on all sides"
  [rect shrink]
  [(+ (rect 0) shrink)
   (+ (rect 1) shrink)
   (- (rect 2) (* shrink 2))
   (- (rect 3) (* shrink 2))])

(defn draw-panel
  "Draws a panel with default border and background and returns inner bounds"
  [bounds sprite]
  (draw-border bounds (sprite :border) (sprite :width))
  (def inner-bounds (shrink-rect bounds (sprite :width)))
  (if (and (junk/vectored i (> (inner-bounds i) 0)))
    (draw-rect inner-bounds (sprite :background)))
  inner-bounds)

(defn panel
  "Creates a function that performs a panels rendering and logic duties"
  [sprite & children]
  (fn [bounds]
    (var inner (array ;(draw-panel bounds sprite)))
    (var out nil)
    (/= (inner 3) (length children))
    (each child children
      [(junk/set-if-more-interesting out (child (tuple ;inner)))
       (+= (inner 1) (inner 3))])
    out))

(defn text
  "Creates a function that performs a text's duties"
  [font message]
  (fn [bounds]
    (def wrapped (wrap-text message font (bounds 2)))
    (draw-text bounds font wrapped)
    nil))
