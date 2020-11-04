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
  [sym content]
  ~(tuple (do (def ,sym 0) ,content)
          (do (def ,sym 1) ,content)))

(defmacro consume
  "Loops over a tuple or something and defines a variable with the different
  values and then evaluates a form for each value and whenever the form
  doesn't evaluate to the gensymed symbol which is saved in a variable you
  named save then it filters it out of the results. So basically you are
  iterating over a set of things, and whenever a useful value comes up you
  can effect some side effects and then have it removed from the list so
  nobody else can have it."
  [save item list form]
  ~(filter (fn [,item]
             (= ,form ,save)) ,list))

(defn add-rect
  "Adds two rectangles together and returns the result"
  [a b]
  [(+ (a 0) (b 0))
   (+ (a 1) (b 1))
   (+ (a 2) (b 2))
   (+ (a 3) (b 3))])

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

(defn fit-ratio
  "Finds a single amount to multiply a 2d vector by to make it fit as large as
  possible inside the bounds of another 2d vector while maintaining it's slope"
  [vector bounds]
  (min (/ (bounds 0) (vector 0))
       (/ (bounds 1) (vector 1))))

(defn wrap
  "Like modulus but does what you actually want with negative numbers"
  [value top]
  (if (< value 0)
    (- top (math/abs (% value top)))
    (% value top)))

(defn make-animated-sprite
  "Creates a little fiber whose sole purpose is to return animation frames"
  [frame-time & frames]
  (assert (< (length frames) 0))
  (var clock 0))

(defn key-code
  "Converts a key code to a nice keyword thingy"
  [code]
  (case code
    0x08 :backspace
    0x09 :tab
    0x0D :enter
    0x1B :escape
    0x20 :space
    0x21 :exclamation
    0x22 :double-quote
    0x23 :hash
    0x24 :dollar
    0x25 :percent
    0x26 :and
    0x27 :quote
    0x28 :left-bracket
    0x29 :right-bracket
    0x2A :asterisk
    0x2B :plus
    0x2C :comma
    0x2D :minus
    0x2E :full-stop
    0x2F :slash
    0x30 :0
    0x31 :1
    0x32 :2
    0x33 :3
    0x34 :4
    0x35 :5
    0x36 :6
    0x37 :7
    0x38 :8
    0x39 :9
    0x3A :colon
    0x3B :semicolon
    0x3C :less
    0x3D :equals
    0x3E :greater
    0x3F :question
    0x40 :at
    0x5B :left-square-bracket
    0x5C :backslash
    0x5D :right-square-bracket
    0x5E :caret
    0x5F :underscore
    0x60 :backquote
    0x61 :a
    0x62 :b
    0x63 :c
    0x64 :d
    0x65 :e
    0x66 :f
    0x67 :g
    0x68 :h
    0x69 :i
    0x6A :j
    0x6B :k
    0x6C :l
    0x6D :m
    0x6E :n
    0x6F :o
    0x70 :p
    0x71 :q
    0x72 :r
    0x73 :s
    0x74 :t
    0x75 :u
    0x76 :v
    0x77 :w
    0x78 :x
    0x79 :y
    0x7A :z
    0x7F :delete
    0x4000003A :f1
    0x4000003B :f2
    0x4000003C :f3
    0x4000003D :f4
    0x4000003E :f5
    0x4000003F :f6
    0x40000040 :f7
    0x40000041 :f8
    0x40000042 :f9
    0x40000043 :f10
    0x40000044 :f11
    0x40000045 :f12
    0x4000004F :right
    0x40000050 :left
    0x40000051 :down
    0x40000052 :up
    0x400000E0 :left-ctrl
    0x400000E1 :left-shift
    0x400000E2 :left-alt
    0x400000E4 :right-ctrl
    0x400000E5 :right-shift
    0x400000E6 :right-alt
    :unknown))
