(import assets/janet/junk :as junk)
(import assets/janet/gui :as gui)

(fn [screen message]
    (def screen-size (get-screen-dimensions))
    (def box (get-sprite "panel"))
    (def font (get-sprite "font"))
    (def width 512)
    (while true
        (def input (gui/place (gui/panel (gui/text message)
                                         (gui/button (gui/text "ok")))
                              :left 128
                              :width width
                              :bottom 0))
        (yield 1)))
