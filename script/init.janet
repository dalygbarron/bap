(import script/atlas :as atlas)
(import script/vec :as vec)
(import script/rect :as rect)

(fn []
  (defn create-rat [sprite pos vel]
    @{:sprite sprite
      :pos pos
      :vel vel
      :update (fn [self] 
                (set (self :pos)
                     (vec/wrap (vec/+ (self :pos) (self :vel))
                               [1024 600])))
      :render (fn [self batch]
                (draw-rect-to-batch batch
                                    ;(vec/floor (self :pos))
                                    ((self :sprite) 2)
                                    ((self :sprite) 3)
                                    ;(rect/floor (self :sprite))))})
  (defn create-rats [n att]
    (def sprites (keys att))
    (def rats @[])
    (for i 0 n
      (do
        (def index (% i (length sprites)))
        (def sprite (att (sprites index)))
        (array/push rats
                    (create-rat sprite
                                [(math/random) (math/random)]
                                [(math/random) (math/random)]))))
    (tuple ;rats))
  (var going true)
  (def n 1000)
  (def texture (load-texture "assets/coom.png"))
  (def batch (create-batch texture n))
  (def att (atlas/load-atlas "assets/cooxr.txt"))
  (def rats (create-rats n att))
  (while going 
    (clear-batch batch)
    (each rat rats
      (do
        (:update rat)
        (:render rat batch)))
    (render-batch batch)
    (yield 1))
  (free-batch batch)
  (free-texture texture))
