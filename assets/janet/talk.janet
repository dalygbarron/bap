(fn []
    (print "Hello you stupid mother fuckers")
    (yield 1)
    (print (+ 5 (* 4 3)))
    (yield 2)
    (print "I am gonna kill you all wahooo")
    (yield 1)
    (var sum 0)
    (for i 0 10
         (+= sum i)
         (if (= (% i 2) 0)
             (print ".")))
    (print sum))
