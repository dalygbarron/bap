(import assets/janet/config :as config)

(fn [screen]
    (file/close (file/write (file/open "brexit.janet"
                                       :w)
                            "this shit is real gay"))
    (replace-trans screen
                   (new-blank screen
                              config/start-script
                              "Hello and welcome to my game")))
