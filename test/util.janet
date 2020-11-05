(import script/util :as util)

(defn test-consume
  "Tests that the consume macro generates what we would expect"
  []
  (def macroed
    (macex '(util/consume :unknown
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

(defn test-cloop
  "Tests that the cloop macro evaluates to a bunch of forms etc"
  []
  (def macroed [(util/cloop 3 i (* i 3))])
  (def natural [0 3 6])
  (pp macroed)
  (pp natural)
  (assert (deep= macroed natural)))

(test-consume)
(test-cloop)
