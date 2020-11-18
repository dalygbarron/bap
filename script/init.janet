(fn []
  (var going true)
  (def texture (load-texture "assets/coom.png"))
  (def batch (create-batch texture))
  (while going
    (render-batch batch)
    (yield 1)))
