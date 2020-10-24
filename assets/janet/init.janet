(import assets/janet/config :as config)

(fn [screen]
    (replace-trans screen
                   (new-blank screen
                              config/start-script
                              (string "Hello and welcome to my game you "
                                      "fucking idiot. I really hope that "
                                      "you pay for your crimes before "
                                      "I cathch you."))))
