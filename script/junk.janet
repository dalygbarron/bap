(defn is-whitespace
  "Evaluates to a boolean for whether given character is whitespace"
  [c]
  (or (= c 32) (= c 10)))

(defn txt*
  "Joins lines of text without newlines unless empty string or explicit"
  [& str]
  (string ;(seq [i :in str]
             (if (= 0 (length i))
               "\n"
               (if (is-whitespace (i (- (length i) 1)))
                 i
                 (string i " "))))))

(defmacro txt
  "Macro version of txt*"
  [& str]
  (txt* ;str))

(defmacro deft
  "Defines output of txt into a constant to save space"
  [name & str]
  ['def name (txt* ;str)])

(defmacro vectored
  "Does everything twice with an index variable"
  [var content]
  ~(tuple (do (def ,var 0) ,content)
          (do (def ,var 1) ,content)))

(defn mult-vec
  "multiplies two 2d vectors and returns the result"
  [a b]
  (vectored i (* (a i) (b i))))

(defn add-vec
  "adds two 2d vectors and returns the result"
  [a b]
  (vectored i (+ (a i) (b i))))

(defn sub-vec
  "Subtracts one vector from another and returns the result"
  [a b]
  (vectored i (- (a i) (b i))))

(defn sign-vec
  "Makes the items in a vector be signed as requested in another one"
  [in signs]
  (vectored i
            (if (< (signs i) 0)
              (* (math/abs (in i)) -1)
              (if (> (signs i) 0)
                (math/abs (in i))
                (in i)))))

(defn print-vec
  "prints a vector in a readable form"
  [vec]
  (printf "(%d %d)" (vec 0) (vec 1)))

(defmacro set-if-more-interesting
  "Sets the variable given if it's value is nil"
  [name value]
  ~(if (= ,name nil) (set ,name ,value))) 