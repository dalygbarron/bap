(import script/atlas :as atlas)

(fn []
  (var going true)
  (def texture (load-texture "assets/coom.png"))
  (def batch (create-batch texture 15))
  (def att (atlas/load-atlas "assets/cooxr.txt"))
  (def fav (in att "dany.png"))
  (while going
    (def expansion (math/floor (* (math/random) 900)))
    (clear-batch batch)
    (draw-rect-to-batch batch ;[10 10 expansion expansion] ;fav)
    (render-batch batch)
    (yield 1))
  (free-batch batch)
  (free-texture texture))
