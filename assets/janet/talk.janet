(import assets/janet/junk :as junk)

(fn [screen message]
    (def screen-size (get-screen-dimensions))
    (def box (get-sprite "panel"))
    (def font (get-sprite "font"))
    (def width 512)
    (def wrapped (wrap-text message font width))
    (while true
           (draw-text screen
                      (junk/draw-panel screen [128 400 width 80])
                      font
                      wrapped)
           (yield 1)))
