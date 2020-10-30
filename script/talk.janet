(import script/junk :as junk)
(import script/gui :as gui)
(import script/config :as config)

(defn main
  "Runs a talking thingy"
  [message]
  (def screen-size (get-screen-dimensions))
  (def pic (get-sprite "dany"))
  (var count-down 1000)
  (defn warning [] (string/format "%d more ticks" count-down))
  (def window
    (gui/panel config/panel
               (gui/v-panel config/panel
                            0.1
                            (gui/dyn-text config/font nil warning)
                            (gui/h-panel config/panel
                                         0.5
                                         (gui/h-panel config/panel
                                                      0.5
                                                      (gui/sprite pic nil)
                                                      (gui/sprite config/font true))
                                         (gui/text config/font message)))))
  (var width 512)
  (while (> count-down 0)
    (-= count-down 1)
    (+= width (* (- (math/random) 0.5) 6))
    (var out (window [0 0 (screen-size 0) (screen-size 1)]))
    (yield)))
