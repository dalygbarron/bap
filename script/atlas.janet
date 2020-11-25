(import script/util :as util)

(defn load-atlas
  "Loads a texture atlas from a given file. the format is the name, then x, 
  then y, then width, then height, all space seperated, and each sprite gets
  it's own line"
  [filename]
  (defn read-number [text] (scan-number (string/trim text)))
  (def sprites @{})
  (util/each-line filename
                  (fn [line]
                    (def parts (string/split " " line))
                    (assert (= (length parts) 5)
                            (string/format "'%s' is not a correct atlas line"
                                           (string line)))
                    (set (sprites (parts 0)) [(read-number (parts 1))
                                              (read-number (parts 2))
                                              (read-number (parts 3))
                                              (read-number (parts 4))])))
  (table/to-struct sprites))
