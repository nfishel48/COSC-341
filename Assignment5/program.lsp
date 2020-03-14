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
    
;(print(f1 '0 '(a (a b (b c)) c d (e))))

;function 2

(defun f2 (L)
    (cond 
        ((null L) nil)                               ;if L is empty
        ((null (cdr L)) nil)                             ;reached end of list
        ((equal (listp (car L)) nil) t)                         ;if an atom is found                   
        )
    )

;(print(f2 '((a b)(c d))))
;(print(f2 '(a(b c))))

(defun f3 (X L)
    (cond
        ((null L) nil)
        ((null (cdr L))                                         ;reached the end of the list
         (cond                                                  ;check the last item in the list
             ((< 0 (mod (car L) 2)) (cons (car L) X))           ;last atom was odd
             ))
        ((< 0 (mod (car L) 2)) (f3 (cons (car L) X) (cdr L)))    ;if number is odd add to a list and call function again
        (T (f3 X (cdr L)))                                       ;else call function again and do not add number to list
        )
    )
(print (f3 '() '(23 6 7  9 18 3  6 7 22 7)))

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
     
(print (f4  '1000 '(7 10 5)))

;function 5

(defun f5 (L)
    (cond 
        ((null L) nil)                          ;if empty
        (T(append (f5 (cdr L)) (list (car L)))) ;append front of list to the back of list
        )
    )
;(print(f5 '(a (b c) (x) d)))
        


                               
        

