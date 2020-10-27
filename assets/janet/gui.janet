(import assets/janet/junk :as junk)

(def- wrap-cache
     "Stores wrapped texts so you don't have to save manually"
     @{})

(defn make-panel-sprite
      "Makes a nice struct to represent the parts of a panel sprite"
      [background border width]
      {:background background :border border :width width})

(def Knob
     "Gui element thing"
     @{:bounds [0 0 0 0]
       :get-min-width (fn [self height] 0)
       :get-min-height (fn [self width] 0)
       :set-position (fn [self bounds] (set (self :bounds) bounds))})

(def PanelKnob
     "Represents a panel that fits stuff vertically"


(defn tokenise
      "takes a string and breaks it into an array based on whitespace"
      [text]
      (string/split " " text))

(defn wrap-tokens
      "takes a list of tokens and merges them with newlines to fit width"
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
      (def cached-value (get wrap-cache [text font width]))
      (if cached-value (return cached-value))
      (var buffer (buffer/new 256))
      (def chars (/ width (/ (font 2) 16)))
      (each line
            (string/split "\n" text)
            (buffer/push-string buffer (wrap-tokens (tokenise line) chars)))
      (def out (string buffer))
      (put wrap-cache [text font width] out)
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
      (if (and (junk/vectored i (> (inner-bounds i) 0)))
        (draw-rect screen inner-bounds panel))
      inner-bounds)
