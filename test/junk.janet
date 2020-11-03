(import script/junk :as junk)

(defn test-consume
  "Tests that the consume macro generates what we would expect"
  []
  (def macroed
    (macex '(junk/consume :unknown
                          input
                          inputs
                          (case input
                            :ui-accept (callback)
                            :up (-- chosen)
                            :down (++ chosen)
                            :unknown))))
  (def natural
    (macex '(filter (fn [input]
                      (= (case input
                           :ui-accept (callback)
                           :up (-- chosen)
                           :down (++ chosen)
                           :unknown)
                         :unknown)) inputs)))
    (assert (deep= macroed natural)))

(test-consume)
