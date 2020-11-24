(defn load-atlas
  "Loads a texture atlas from a given file. the format is the name, then x, 
  then y, then width, then height, all space seperated, and each sprite gets
  it's own line"
  [filename]
  (def sprites @{})
  (with [file (file/open filename :r)]
    (def line (file/read file :line))
    (def parts (string/split " " line))
    (assert (= (length parts) 5)
            (string/format "'%s' is not a correct atlas line" (string line)))
    (pp (parts 1))
    (pp (parts 2))
    (pp (parts 3))
    (pp (parts 4))
    (set (sprites (parts 0)) [(int/u64 (parts 1))
                              (int/u64 (parts 2))
                              (int/u64 (parts 3))
                              (int/u64 (parts 4))]))
  (table/to-struct sprites))
