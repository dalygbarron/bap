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

(defn make-bounds
  "Helper to make bounding box that gui window goes into."
  [anchor width protrusion]
  (def dimensions (get-screen-dimensions))
  (case anchor
    :left [
           0
           (/ (* (dimensions 1) width) 2)
           (* (dimensions 0) protrusion)
           (* (dimensions 1) width)]
    :right [
            (* (dimensions 0) (- 1 protrusion))
            (/ (* (dimensions 1) width) 2)
            (* (dimensions 0) protrusion)
            (* (dimensions 1) width)]
    :top [
          0
          (/ (* (dimensions 1) width) 2)
          (* (dimensions 0) protrusion)
          (* (dimensions 1) width)]
    :bottom [
             0
             (/ (* (dimensions 1) width) 2)
             (* (dimensions 0) protrusion)
             (* (dimensions 1) width)]
    [
     0
     (/ (* (dimensions 1) width) 2)
     (* (dimensions 0) protrusion)
     (* (dimensions 1) width)]))

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

(defn draw-sprite-aspect
  "Draws a sprite maintaining aspect ratio or not"
  [pic bounds]
  (def ratio (junk/fit-ratio (tuple/slice pic 2 4)
                             (tuple/slice bounds 2 4)))
  (draw-sprite [(bounds 0)
                (bounds 1)
                (* (pic 2) ratio)
                (* (pic 3) ratio)]
               pic))

(defn panel
  "Creates a function that performs a panels rendering and logic duties"
  [sprite & children]
  (fn [bounds input]
    (var inner (array ;(draw-panel bounds sprite)))
    (/= (inner 3) (length children))
    (each child children
      (child (tuple ;inner) input)
      (+= (inner 1) (inner 3)))))

(defn v-panel
  "Creates a panel that splits into two panels vertically with a given ratio"
  [sprite ratio a b]
  (fn [bounds input]
    (def portion (* (bounds 3) ratio))
    (->> input
         (a (draw-panel [(bounds 0)
                         (bounds 1)
                         (bounds 2)
                         portion]
                        sprite))
         (b (draw-panel [(bounds 0)
                         (+ (bounds 1) portion)
                         (bounds 2)
                         (- (bounds 3) portion)]
                        sprite)))))

(defn h-panel
  "Creates a panel that splits into two panels vertically with a given ratio"
  [sprite ratio a b]
  (fn [bounds input]
    (def portion (* (bounds 2) ratio))
    (->> input
         (a (draw-panel [(bounds 0)
                         (bounds 1)
                         portion
                         (bounds 3)]
                        sprite))
         (b (draw-panel [(+ (bounds 0) portion)
                         (bounds 1)
                         (- (bounds 2) portion)
                         (bounds 3)]
                        sprite)))))

(defn text
  "Creates a function that performs a text's duties"
  [font message]
  (fn [bounds input]
    (def wrapped (wrap-text message font (bounds 2)))
    (draw-text bounds font wrapped)
    input))

(defn sprite
  "Creates a function that draws a greedily sized sprite"
  [pic stretch]
  (fn [bounds input]
    (if stretch
      (draw-sprite bounds pic)
      (draw-sprite-aspect pic bounds))
    input))

(defn v-choice
  "Creates a function that does a vertical selecty thingy"
  [pic active & children]
  (var choice 0)
  (fn [bounds input]
    (def inner [(+ (bounds 0) (pic 2))
                (bounds 1)
                (- (bounds 2) (pic 2))
                (/ (bounds 3) (length children))])
    (for i 0 (length children)
      (if (and (= i choice) input active)
        (draw-sprite [(bounds 0)
                      (+ (bounds 1) (* (inner 3) i))
                      (pic 2)
                      (inner 3)]
                     pic))
      ((children i) (junk/add-rect inner
                                   [0
                                    (* (inner 3) i)
                                    0
                                    0])
       []))
    (def out (junk/consume 'keep
                           press
                           input
                           (case press
                             :ui-accept (pp "brexit")
                             :up (-- choice)
                             :down (++ choice)
                             'keep)))
    (set choice (junk/wrap choice (length children)))
    out))
