(import kowari)

(def sprites (mapcat (fn [item] (if (string/has-suffix? ".png" item)
                                  (string "sprites/" item)
                                  []))
                     (os/dir "sprites")))

(def atlas (kowari/make-atlas 1024 1024 ;sprites))
(kowari/render-atlas-to-file atlas "assets/coom.png")
(with [file (file/open "assets/cooxr.txt" :w)]
  (kowari/each-atlas atlas
                     (fn [x y pic]
                       (file/write file
                                   (string/format "%s %d %d %d %d\n"
                                                  (pic :name)
                                                  x
                                                  y
                                                  (pic :width)
                                                  (pic :height))))))

