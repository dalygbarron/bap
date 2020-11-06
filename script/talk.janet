(import script/sprite :as sprite)
(import script/gui :as gui)
(import script/config :as config)
(import script/rect :as rect)

(defn choices
  "Runs a choice gui thing and closes and returns the chosen one at end"
  [speaker message & items]
  (var death false)
  (var updates {:input [] :delta 0})
  (def content-section
    (gui/split-panel config/panel
                     0.8
                     :vertical
                     (gui/text config/font message)
                     (gui/v-choice config/selector
                                   (fn [choice] (set death true))
                                   (gui/text config/font config/confirm))))
  (def window (gui/panel config/panel
                         (gui/split-panel config/panel
                                          0.15
                                          :vertical
                                          (gui/text config/font speaker)
                                          content-section)))
  (def box (gui/make-bounds :left 0.4 0.7))
  (while (not death)
    (window (updates :delta) box (updates :input))
    (set updates (yield))))

(defn main
  "Runs a talking thingy"
  [message]
  (choices "Johnny" message "yes" "no" "maybe"))
