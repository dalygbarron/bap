(import script/junk :as junk)
(import script/sprite :as sprite)
(import script/gui :as gui)
(import script/config :as config)

(defn choices
  "Runs a choice gui thing and closes and returns the chosen one at end"
  [speaker message & items]
  (def zimmer (sprite/make-animated 5
                                    (get-sprite "cheat")
                                    (get-sprite "craneHook")
                                    (get-sprite "craneKey")))
  (def window
    (gui/panel config/panel
               (gui/v-panel config/panel
                            0.15
                            (gui/text config/font speaker)
                            (gui/v-panel config/panel
                                         0.8
                                         (gui/text config/font message)
                                         (gui/v-choice zimmer
                                                       true
                                                       (gui/text config/font
                                                                 config/confirm))))))
  (var updates {:input [] :delta 0})
  (while true
    (window (updates :delta) (gui/make-bounds :left 0.4 0.7) (updates :input))
    (set updates (yield))))

(defn main
  "Runs a talking thingy"
  [message]
  (choices "Johnny" message "yes" "no" "maybe"))
