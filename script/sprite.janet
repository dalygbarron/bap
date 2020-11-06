(import script/util :as util)
(import script/rect :as rect)
(import script/vec :as vec)

(defn cut-h
  "Takes a frame and cuts it into a number of frames horizontally"
  [frame n]
  (def piece (/ (frame 2) n))
  (map (fn [i]
         [(+ (frame 0) (* piece i))
          (frame 1)
          piece
          (frame 3)])
       (range n)))

(defn make
  "Makes a sprite function that only does one frame"
  [frame]
  (fn [time] frame))

(defn make-animated
  "Creates a little function whose sole purpose is to return animation frames"
  [frame-time & frames]
  (assert (> (length frames) 0) "animated sprite needs frames")
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
  (def inner-bounds (rect/shrink bounds (sprite :width)))
  (if (and ;(util/cloop 2 i (> (inner-bounds (+ i 2)) 0)))
    (draw-rect inner-bounds ((sprite :background) time)))
  inner-bounds)

(defn draw-aspect
  "Draws a sprite maintaining aspect ratio or not"
  [pic bounds time]
  (def frame (pic time))
  (def ratio (vec/fit-ratio (rect/size frame) (rect/size bounds)))
  (draw-sprite (rect/make (rect/pos bounds)
                          (vec/* (rect/size frame) [ratio ratio]))
               frame))
