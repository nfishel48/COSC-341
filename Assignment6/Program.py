#This program is written for COSC-341 assignment 6



#========================================================================================================
#Question 1
#this function will compute pi to whatever number is input
def compute_pi(n) :
    i = 1
    frac = 1
    flip = -1
    total = 1
    for i in range(1, n) :
        frac = 1/(2*i+1)
        frac = frac * flip
        flip = flip * -1
        total = total + frac

    total = total * 4
    return total

#========================================================================================================
#Question 2
#This functions will compute the square root of a selected area
def compute_sqrt(x) :
    i = 0
    nxt = 0
    last = 1
    for i in range(11):
        nxt = .5*(last + x/last)
        print(nxt)
        last = nxt

    return nxt

#========================================================================================================
#Question 3
#This function will return weather a number is prime or not 
def is_prime(n):
    i = 2
    p = 1
    for i in range(2,n,1):
        if n%i == 0 and i!= n: #check if remainder when dividing
            #return 0 if false
            return 0
        
    #return 1 if no number is found to have a remainder
    return 1
    

#this function will print all primes <=n
def display_primes(n):
    i = 2
    ans = 1
    for i in range (2, n,1):
        ans = is_prime(i) #call is primes function to decice if function is prime or not 
        if ans == 1:
            print(i)


#========================================================================================================
#Question 4
#This function will read student names and scores from the user. Then it will display 
#the average, the minimum, and the maximum along with that sudents name
def process_scores():
    print('Please enter the student names and scores, enter q to quit')
    done = 0
    i = 1 #counter
    avg = 0
    max = 0
    min = 100
    max_name =''
    min_name =''
    while done == 0:
        name = input('Enter Name: ')
        if name == 'q': #check for quit
            break
        score = float(input('Enter score: '))
        avg += score # total all scores
        if score > max:
            max = score
            max_name = name
        if score < min:
            min = score
            min_name = name
        i = i+1
    avg=avg/i
    print('The average score was: ',avg)
    print('The max score was: ',max,'achieved by',max_name)
    print('The min score was: ',min,'achieved by',min_name)

process_scores()

    


        

       
    
    
        
        
    









