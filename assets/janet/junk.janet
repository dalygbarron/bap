(defn add-array
  "Adds one array to another"
  [a b]
  (set (a 0) (+ (a 0) (b 0)))
  (set (a 1) (+ (a 1) (b 1))))
