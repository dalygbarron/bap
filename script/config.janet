(import script/gui :as gui)
(import script/junk :as junk)

(def start-script "script/talk.janet")
(def map-dir "assets/maps/")
(def font (get-sprite "font"))
(def selector (get-sprite "life"))
(def panel (gui/make-panel-sprite (get-sprite "background")
                                  (get-sprite "panel")
                                  4))
(defn map-input
  "Converts a list of raw key codes into usable inputs"
  [codes]
  (->> codes
       (mapcat (fn [code]
                 (case (junk/key-code code)
                   :left-shift :shift
                   :right-shift :shift
                   :z [:z :ui-accept]
                   :x [:x :ui-cancel]
                   :left :left
                   :right :right
                   :up :up
                   :down :down
                   :enter :ui-accept
                   :escape :ui-cancel)))
       (filter (fn [key] (not (= key nil))))))
