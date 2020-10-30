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
      [(junk/set-if-cooler out (child (tuple ;inner)))
       (+= (inner 1) (inner 3))])
    out))

(defn v-panel
  "Creates a panel that splits into two panels vertically with a given ratio"
  [sprite ratio a b]
  (fn [bounds]
    (var inner (draw-panel bounds sprite))
    (var out nil)
    (def portion (* (bounds 3) ratio))
    (junk/set-if-cooler out
                        (a (draw-panel [(bounds 0)
                                        (bounds 1)
                                        (bounds 2)
                                        portion]
                                       sprite)))
    (junk/set-if-cooler out
                        (b (draw-panel [(bounds 0)
                                        (+ (bounds 1) portion)
                                        (bounds 2)
                                        (- (bounds 3) portion)]
                                       sprite)))
    out))

(defn h-panel
  "Creates a panel that splits into two panels vertically with a given ratio"
  [sprite ratio a b]
  (fn [bounds]
    (var inner (draw-panel bounds sprite))
    (var out nil)
    (def portion (* (bounds 2) ratio))
    (junk/set-if-cooler out
                        (a (draw-panel [(bounds 0)
                                        (bounds 1)
                                        portion
                                        (bounds 3)]
                                       sprite)))
    (junk/set-if-cooler out
                        (b (draw-panel [(+ (bounds 0) portion)
                                        (bounds 1)
                                        (- (bounds 2) portion)
                                        (bounds 3)]
                                       sprite)))
    out))

(defn text
  "Creates a function that performs a text's duties"
  [font message]
  (fn [bounds]
    (def wrapped (wrap-text message font (bounds 2)))
    (draw-text bounds font wrapped)
    nil))

(defn dyn-text
  "Creates a function that does text which can change each time"
  [font wrap generator]
  (fn [bounds]
    (def wrapped (if wrap
                   (wrap-text (generator) font (bounds 2))
                   (generator)))
    (draw-text bounds font wrapped)
    nil))

(defn sprite
  "Creates a function that draws a greedily sized sprite"
  [pic stretch]
  (fn [bounds]
    (draw-sprite (if stretch
                   bounds
                   (do
                     (def ratio (min (/ (bounds 2) (pic 2))
                                     (/ (bounds 3) (pic 3))))
                     [(bounds 0)
                      (bounds 1)
                      (* (pic 2) ratio)
                      (* (pic 3) ratio)]))
                 pic)
    nil))


