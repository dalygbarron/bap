(import script/config :as config)
(import script/junk :as junk)

(junk/deft say
           "I am the greatest. I am the greatest and best man in the"
           "world. Man I am so great it hurts my pee pee."
           ""
           "I am so great I am gonna go down to the hat shop right now and the"
           "guy running the shop is gonna run right over and see what I want"
           "and I will say nothing and they just be grateful I even showed"
           "up.")

(fn [screen]
  (replace-trans screen
                 (new-blank screen
                            config/start-script
                            say)))
