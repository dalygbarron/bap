(import script/junk :as junk)
(import script/gui :as gui)
(import script/config :as config)

(defn choices
  "Runs a choice gui thing and closes and returns the chosen one at end"
  [speaker message & items]
  (def window
    (gui/panel config/panel
               (gui/v-panel config/panel
                            0.15
                            (gui/text config/font speaker)
                            (gui/v-panel config/panel
                                         0.8
                                         (gui/text config/font message)
                                         (gui/v-choice config/selector
                                                       true
(gui/text config/font
                                                                 config/confirm)
(gui/text config/font
                                                                 config/confirm)
                                                       (gui/text config/font
                                                                 config/confirm))))))
  (var input [])
  (while true
    (window (gui/make-bounds :left 0.4 0.7) input)
    (set input (config/map-input (yield)))))

(defn main
  "Runs a talking thingy"
  [message]
  (choices "Johnny" message "yes" "no" "maybe"))
