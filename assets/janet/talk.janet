(import assets/janet/junk :as junk)

(fn [screen message]
    (def screen-size (get-screen-dimensions screen))
    (def box (get-sprite screen "panel"))
    (def font (get-sprite screen "font"))
    (while true
           (draw-text screen
                      (junk/draw-panel screen [128 400 512 80])
                      font
                      message)
           (yield 1)))
