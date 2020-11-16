(fn []
  (var going true)
  (def batch (load-batch "assets/coom.png"))
  (while going
    (render-batch batch)
    (yield 1)))
