(import script/util :as util)
(import script/sprite :as sprite)
(import script/config :as config)
(import script/vec :as vec)
(import script/rect :as rect)

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
    [0
     (/ (* (dimensions 1) width) 2)
     (* (dimensions 0) protrusion)
     (* (dimensions 1) width)]))

(defn panel
  "Creates a function that performs a panels rendering and logic duties"
  [sprite & children]
  (var time 0)
  (fn [delta bounds input]
    (+= time delta)
    (var inner (array ;(sprite/draw-panel bounds sprite time)))
    (/= (inner 3) (length children))
    (each child children
      (child delta (tuple ;inner) input)
      (+= (inner 1) (inner 3)))))

(defn split-panel
  "Creates a panel that splits two things either vertically or horizontally"
  [sprite ratio axis a b]
  (def axis-vector (vec/axis axis))
  (var time 0)
  (fn [delta bounds input]
    (+= time delta)
    (def pos (rect/pos bounds))
    (def size (rect/size bounds))
    (def portion (vec/- size
                        (vec/* (vec/* size (util/cloop 2 i (- 1 ratio)))
                               axis-vector)))
    (def mould (rect/make (vec/+ pos (vec/* portion axis-vector))
                          (vec/- size (vec/* portion axis-vector))))
    (->> input
         (a delta (sprite/draw-panel (rect/make pos portion) sprite time))
         (b delta (sprite/draw-panel mould sprite time)))))

(defn text
  "Creates a function that performs a text's duties"
  [font message]
  (var time 0)
  (fn [delta bounds input]
    (+= time delta)
    (def font-frame (font time))
    (def wrapped (wrap-text message font-frame (bounds 2)))
    (draw-text bounds font-frame wrapped)
    input))

(defn sprite
  "Creates a function that draws a greedily sized sprite"
  [pic stretch]
  (var time 0)
  (fn [delta bounds input]
    (+= time delta)
    (if stretch
      (draw-sprite bounds (pic time))
      (sprite/draw-aspect pic bounds time))
    input))

(defn v-choice
  "Creates a function that does a vertical selecty thingy"
  [pic action & children]
  (var choice 0)
  (var time 0)
  (fn [delta bounds input]
    (+= time delta)
    (def pic-frame (pic time))
    (def inner [(+ (bounds 0) (pic-frame 2))
                (bounds 1)
                (- (bounds 2) (pic-frame 2))
                (/ (bounds 3) (length children))])
    (for i 0 (length children)
      (if (and (= i choice) (not (nil? action)))
        (draw-sprite [(bounds 0)
                      (+ (bounds 1) (* (inner 3) i))
                      (pic-frame 2)
                      (inner 3)]
                     pic-frame))
      ((children i) delta (rect/+ inner [0 (* (inner 3) i) 0 0]) []))
    (def out 
      (if (not (nil? action))
        (util/consume 'keep
                      press
                      input
                      (case (config/map-input press)
                        :jump (action choice)
                        :up (-- choice)
                        :down (++ choice)
                        'keep))
        input))
    (set choice (util/wrap choice (length children)))
    out))
