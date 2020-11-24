(fn []
  (var going true)
  (def texture (load-texture "assets/idiot.png"))
  (def batch (create-batch texture 15))
  (while going
    (def expansion (math/floor (* (math/random) 900)))
    (pp expansion)
    (clear-batch batch)
    (draw-rect-to-batch batch ;[10 10 expansion expansion] ;[0 0 expansion expansion])
    (render-batch batch)
    (yield 1))
  (free-batch batch)
  (free-texture texture))
