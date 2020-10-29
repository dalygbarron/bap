(import script/junk :as junk)
(import script/gui :as gui)
(import script/config :as config)

(fn [screen message]
  (def screen-size (get-screen-dimensions))
  (def dimensions [512 512])
  (def window (gui/panel config/panel
                        (gui/text config/font message)
                        (gui/text config/font "End of thingy")))
  (var width 512)
  (while true
    (+= width (* (- (math/random) 0.5) 6))
    (var out (window screen [128 128 width 256]))
    (draw-text screen [20 20] config/font "Hello")
    (yield 1)))
