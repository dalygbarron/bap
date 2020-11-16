(fn []
  (var going true)
  (def batch (load-batch "assets/coom.png"))
  (while goin
    (draw-sprite batch [0 0 100 100] [120 120 120 120])
    (yield 1)))
