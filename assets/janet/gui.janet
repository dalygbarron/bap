(import assets/janet/junk :as junk)

(var *wrap-cache* :private @{})

(defn tokenise
      "takes a string and breaks it into an array based on whitespace"
      [text]
      (string/split " " text))

(defn wrap-tokens
      (junk/text "Takes a list of tokens and merges them into one string such"
                 "that they do not exceed the required number of characters"
                 "per line. Adds a newline on the end as well.")
      [tokens width]
      (var i 0)
      (var buffer (buffer/new 32))
      (each token
            tokens
            [(if (< width (+ i (length token)))
               [(set i 0)
                (buffer/push-string buffer "\n")])
             (set i (+ i (length token) 1))
             (buffer/push-string buffer token)
             (buffer/push-string buffer " ")])
      (buffer/push-string buffer "\n")
      buffer)

(defn wrap-text
      "Takes some text and wraps it based on a given font"
      [text font width]
      (def cached-value (get *wrap-cache* [text font width]))
      (if cached-value (return cached-value))
      (var buffer (buffer/new 256))
      (def chars (/ width (/ (font 2) 16)))
      (each line
            (string/split "\n" text)
            (buffer/push-string buffer (wrap-tokens (tokenise line) chars)))
      (def out (string buffer))
      (if key (put *wrap-cache* [text font width] out))
      out)

(defn shrink-rect
      "Takes a rectangle and shrinks it by an amount on all sides"
      [rect shrink]
      [(+ (rect 0) shrink)
       (+ (rect 1) shrink)
       (- (rect 2) (* shrink 2))
       (- (rect 3) (* shrink 2))])

(defn draw-panel
      "Draws a panel with default border and background and returns inner bounds"
      [screen bounds]
      (def border (get-sprite config/border-sprite))
      (def panel (get-sprite config/panel-sprite))
      (draw-border screen bounds border config/border-width)
      (def inner-bounds (shrink-rect bounds config/border-width))
      (if (and (vectored i (> (inner-bounds i) 0)))
        (draw-rect screen inner-bounds panel))
      inner-bounds)
