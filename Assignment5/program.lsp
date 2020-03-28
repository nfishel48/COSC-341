;;;This program is for COSC-341 assignment 5
;gnu clisp 2.49

(defun my_member (x L)
    (cond ((null L) nil)          ;if L is empty then x is not in L
        ((equal x (car L))T)      ;if x is first element of L then x is in L
        (T (my_member x (cdr L))) ;else check x is in cdr of L
        )
    )

;function 1

(defun f1 (x L)
    (cond 
        ((null L) 0)                                    ;if L is empty 
        ((null (cddr L)) x)                              ;when the rest of the list is empty output the answer
        ((listp (car L)) (f1 (+ x 1) (cdr L)))          ;if  car L is a list add one
        ((equal (listp (car L)) nil) (f1 x (cdr L)))    ;if  car L is not a list keep looking 
        )
        
    )
(print "function one :")
(print(f1 '0 '(a (a b (b c)) c d (e))))

;function 2

(defun f2 (L)
    (cond 
        ((null L) nil)                               ;if L is empty
        ((null (cdr L)) nil)                         ;reached end of list
        ((equal (listp (car L)) nil) t)              ;if an atom is found                   
        )
    )
(print "function two nil call: ")
(print(f2 '((a b)(c d))))
(print "function two true call: ")
(print(f2 '(a(b c))))

;function 3

(defun f3 (L)
    (cond
        ((null L)nil)    ;if empty
        ((< 0 (mod (car L) 2)) (cons (car L) (f3 (cdr L)))) ;if its odd add to the list
        (t(f3(cdr L)))                                      ;else continue
        )
    )


(print "function three: ")
(print (f3  '(23 4 7 18 22)))

;funtion 4

(defun f4 (x L)
    (cond
        ((null L) nil)                      ;if empty
        ((null(cdr L))
           (cond
               ((<(car L) x) (car L))
               (T x)
         ))
        ((<(car L) x) (f4 (car L) (cdr L))) ;if current value is less than previous lowest
        (T(f4 x (cdr L)))                   ;else keep looking 
                      
    )
   )
(print "function four")
(print (f4  '1000 '(6 9 2 7 10 5)))

;function 5

(defun f5 (L)
    (cond 
        ((null L) nil)                          ;if empty
        (T(append (f5 (cdr L)) (list (car L)))) ;append front of list to the back of list
        )
    )
(print "function five")
(print(f5 '(a (b c) (x) d)))

;function 6

(defun f6 (L)
    (cond 
        ((null L)nil)                        ; if empty return nil
        (t(cons (car L) (f6 (cdr (cdr L))))) ; return the first element then call function to get the rest of the rest of the list
        )
    )
(print "function six")
(print(f6 '(c ( a b ) d (x y) (a) b)))

;function 7

(defun f7 (L n)
    (cond
        ((null L)nil)           ;if empty return nil
        ((equal n 0) (car L))   ;return this atom when n reaches 0
        (t(f7 (cdr L) (- n 1))) ;take off firt element decrement n return the 
        )
    )
(print "function seven")
(print(f7  '(c (a b) (d c) (x y)) '2))

;function 8


(defun f8 (L)
    (cond 
        ((null L)1)                                     ;if empty 
        ((listp(car L))(* (car (car L)) (f8 (cdr L))))  ;if it is a list get the first element of that list                               
        (t(* (car L) (f8 (cdr L))))                     ;multipy the element and pass the rest of the list
        )
    )

(print "function eight")
(print(f8 '(2 5 4 3 2 1 10 5)))

;function 9
(defun f9 (L)
    (cond
        ((null L)nil)                               ; if empty
        ((my_member (car L) (cdr L)) (f9 (cdr L)))  ;check if the atom is contained in the rest of the list 
        (t (cons (car L) (f9 (cdr L))))             ;base case make a list with the element that is not in the other list
        )
    )
(print "function nine")
(print(f9 '(c (a b) c d (a b))))
       

;function 10

(defun f10 (L1 L2)
    (cond
        ((null L1)nil)                                              ;if list one is empty
        ((null L2)nil)                                              ;if list two is empty
        ((my_member (car L1) L2) (cons (car L1) (f10 (cdr L1) L2))) ;if a member of the first list is contained in the second list add it to a new list
        (t(f10 (cdr L1) L2))                                        ;else continue searching for intersection
        )
    )
(print "function ten:")
(print (f10 '(a (a b) c d) '(b (a b) d)))
       