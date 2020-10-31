(import script/junk :as junk)
(import script/gui :as gui)
(import script/config :as config)

(defn choices
  "Runs a choice gui thing and closes and returns the chosen one at end"
  [speaker message & items]
  (def window
    (gui/panel config/panel
               (gui/v-panel config/panel
                            0.1
                            (gui/text config/font speaker)
                            (gui/panel config/panel
                                       (gui/text config/font message)
                                       (gui/v-choice config/selector
                                                     ;(walk (fn [item]
                                                              (gui/text config/font item))
                                                            items))))))
  (var input [])
  (while true
    (if (> (length input) 0) (pp input))
    (window [100 100 400 300] input)
    (set input (yield))))

(defn main
  "Runs a talking thingy"
  [message]
  (choices "Johnny" message "yes" "no" "maybe"))
