#This program is written for COSC-341 assignment 6

import math

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

#======================================================================================================
#Question 5
#This function will determine the tax amount according to the following tax rules:
#Tax rates depend on income, martial status and state residency.
#In state residents rates {
#Single and income < 30000 tax rate->20%
#Single and income > 30000 tax rate->25%
#married and income < 50000 tax rate -> 10%
#married and incom >= 50000 tax rate -> 15%
#}
#Out of state residents {
#  same rules but -3%
#}

def compute_tax(income, status, state):
    rate = 0 #varible for storing rate
    i = 0 #counter

    #if single
    if status in ['single', 'SINGLE']:
        if income < 30000:
            rate = .2
        else:
            rate = .25
    #if married
    if status in ['married', 'MARRIED']:
        if income < 50000:
            rate = .1
        else:
            rate = .15
    #if out of state
    if state == 'o':
        rate = rate - .03
    
    return income * rate

#======================================================================================================
#Question 6
#This function will take the input parameters as coefficents of a quadratic equation.
#It wil then compute if there are solutions
#if there are solutions it will return the solutions if not it will return 0

def quadratic(a, b, c):
    cando = (b*b) - 4*a*c
    if cando >= 0:
        sol1 = ((b*-1) + math.sqrt((b*b)-(4*a*c)))/(2*a)
        sol2 = ((b*-1) - math.sqrt((b*b)-(4*a*c)))/(2*a)
        return sol1, sol2
    else:
        return 0,0
    


#======================================================================================================
#Question 7
#this funtion will take in a list and sort the list using slection sort 

def sort(list):
    length = len(list)
    for i in range(length):
        #find minimum index
        mindex = i
        for j in range(i+1, length):
            if list[mindex] > list[j]:
                mindex = j
        
        #swap elements
        list[i], list[mindex] = list[mindex], list[i]
    return list

#======================================================================================================
#Question 8
#this function will generate a password and username 

def id_password(first, last):
    #generate username
    username = first[0]+last
    #generate password
    flast = len(first)
    llast = len(last)
    password = first[0] + first[flast-1] + last[0] + last[1] + last[2] + str(flast) + str(llast)
    return username, password

#======================================================================================================
#Question 9
#place a input file and a output file in the folder containing this program and this program will
#sort a list of students by id numbers 

def file_sort(infile, outfile):
    #open the infile
    infile = open(infile, 'r')
   
    #read in data from file to sepperate arrays
    line = infile.readline()
    line = line.strip()
    ids = [0]*int(line)
    names = [0]*int(line)
    gpa = [0]*int(line)
    length = int(line)
    for i in range(0, length,1):
        line = infile.readline()
        line = line.strip()
        line = line.split()
        ids[i] = line[0]
        names[i] = line[1]
        gpa[i] = line[2]
    infile.close()
    
    #sort arrays with selection sort
    length = len(ids)
    for i in range(length):
        #find minimum index
        mindex = i
        for j in range(i+1, length):
            if ids[mindex] > ids[j]:
                mindex = j
        
        #swap elements
        ids[i], ids[mindex] = ids[mindex], ids[i]
        names[i], names[mindex] = names[mindex], names[i]
        gpa[i], gpa[mindex] = gpa[mindex], gpa[i]

    #write to outfile
    outfile = open(outfile, 'w')
    length = len(ids)
    for i in range(0, length):
        outfile.write(ids[i]+' '+names[i]+' '+gpa[i]+'\n')
    outfile.close

#======================================================================================================
#Question 10
#main menu
done = False
while done == False:
    print("Welcome to Nathaniel Fishel's Assignment 6! please select a function from below")
    choice = int(input('compute_pi:1\ncompute_sqrt:2\ndisplay_primes:3\nprocess_scores:4\ncompute_tax:5\nquadratic:6\nsort:7\nid_password:8\nfile_sort:9\nTo quit:0\n>'))
    if choice == 1:
        #compute_pi
        n = int(input('Two what number do you want to find pi too? '))
        print(compute_pi(n))
    if choice == 2:
        #compute_sqrt
        x = int(input('What number would you like to find the square root of? '))
        print(compute_sqrt(x))
    if choice == 3:
        #display_primes
        q = int(input('From 0 to what number would you like the prime numbers '))
        display_primes(q)
    if choice == 4:
        #process_scores
        process_scores()
    if choice == 5:
        #compute_tax
        income = int(input('What is your yearly income '))
        status = input('Are you married or single ')
        state = input('Do you live in or out of state ')
        print(compute_tax(income, status, state))
    if choice == 6:
        #quadratic
        a = int(input('Enter a '))
        b = int(input('Enter b '))
        c = int(input('Enter c '))
        print(quadratic(a, b, c))
    if choice == 7:
        #sort
        done = False
        lst = []
        inputt = [1]
        while done == False:
            inputt[0] = int(input('Enter a number or -1 to exit '))
            if inputt[0] ==  -1:
                break
            lst= lst+inputt
        print(sort(lst))
    if choice == 8:
        #id_password
        first = input('Enter your first name ')
        last = input('Enter your last name ')
        print(id_password(first, last))
    if choice == 9:
        #file_sort
        infile = input('Enter the input file name ')
        outfile = input('Enter the output file name ')
        file_sort(infile, outfile)
        print('Done!')
    if choice == 0:
        #quit
        break



    
        





    


        

       
    
    
        
        
    









