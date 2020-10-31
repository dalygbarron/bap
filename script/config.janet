(import script/gui :as gui)

(def start-script "script/talk.janet")
(def map-dir "assets/maps/")
(def font (get-sprite "font"))
(def selector (get-sprite "life"))
(def panel (gui/make-panel-sprite (get-sprite "background")
                                  (get-sprite "panel")
                                  4))
