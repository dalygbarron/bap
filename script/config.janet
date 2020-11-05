(import script/sprite :as sprite)

(def confirm "...")
(def start-script "script/talk.janet")
(def map-dir "assets/maps/")
(def font (sprite/make (get-sprite "font")))
(def selector (sprite/make-animated 1
                                    ;(sprite/cut-h (get-sprite "target") 4)))
(def panel (sprite/make-panel-sprite (get-sprite "background")
                                     (get-sprite "panel")
                                     4))
(defn map-input
  "Takes an input key code and converts it to a game relevant key keyword"
  [code]
  (case code
    0x7A :run
    0x78 :jump
    0x4000004F :right
    0x40000050 :left
    0x40000051 :down
    0x40000052 :up
    nil))
