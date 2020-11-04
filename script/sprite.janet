(import script/junk :as junk)

(defn make
  "Makes a sprite function that only does one frame"
  [frame]
  (fn [time] frame))

(defn make-animated
  "Creates a little function whose sole purpose is to return animation frames"
  [frame-time & frames]
  (assert (> (length frames) 0))
  (fn [time]
    (frames (% (math/floor (/ time frame-time))
               (length frames)))))

(defn make-panel-sprite
  "Makes a nice struct to represent the parts of a panel sprite"
  [background border width]
  {:background (if (function? background) background (make background))
   :border (if (function? border) border (make border))
   :width width})

(defn draw-panel
  "Draws a panel with default border and background and returns inner bounds"
  [bounds sprite time]
  (draw-border bounds ((sprite :border) time) (sprite :width))
  (def inner-bounds (junk/shrink-rect bounds (sprite :width)))
  (if (and (junk/vectored i (> (inner-bounds i) 0)))
    (draw-rect inner-bounds ((sprite :background) time)))
  inner-bounds)

(defn draw-aspect
  "Draws a sprite maintaining aspect ratio or not"
  [pic bounds time]
  (def ratio (junk/fit-ratio (tuple/slice pic 2 4) (tuple/slice bounds 2 4)))
  (draw-sprite [(bounds 0)
                (bounds 1)
                (* (pic 2) ratio)
                (* (pic 3) ratio)]
               (pic time)))
