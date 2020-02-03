/*
This program was written for Assignment 2 in COSC 341 with Dr.Maniccam
A copy of this program can be found on my github www.github.come/nfishel48
*/
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>



/*
Question 1
======================================================================================================
This funtion will compute pi using n terms
*/
double compute_pi(int n)
{
  int i = 1;
  double total = 1;
  double frac;
  int flip = -1;
  for(i=1; i<n; i++){
    frac = 1/(float)(2*i+1);
    frac = frac * flip;
    flip = flip * -1;
    total = total + (float)frac;
  }
  total = total * 4;
  return total;
}
/*
======================================================================================================
*/



/*
Question 2
======================================================================================================
This function computes the square root of a number
*/
double compute_sqrt (double x)
{
  int i;
  double last, next;
  last = 1;
  for(i=0; i<10; i++)
  {
    next = .5*(last + x/last);
    last = next;
  }
  return next;
}
/*
======================================================================================================
*/



/*
Question 3
======================================================================================================
This function will return Yes or No if a interger is a Prime Number
*/
int is_prime(int n)
{
  int i = 1;
  int p = 0;
  for(i = 2; i<=n; i++){
    if(n%i == 0 && i != n){
      /*
      Return 0 for false if remainder is greater than 0
      */
      return 0;
    }
  }
  
  /*
  Return 1 for true if no number has remainder greater than 0
  */
  return 1;
}

/*
This function displays all prime number <=n
*/
void display_primes (int n){
  int i = 1;
  int ans = 0;
  for(i = 2; i<=n; i++){
    ans = is_prime(i);
    if(ans == 1){
      printf("\n%d",i);
    }
  }
   
}
/*
======================================================================================================
*/


/*
======================================================================================================
This function will read student names and scores from the user. Then it will display 
the average, the minimum, and the maximum along with that sudents name
*/
void process_scores(){
  printf("\nPlease enter your data\n");
  int current, done, i = 0;
  int pos1, pos2, max= 0;
  double avg;
  int min = 100;
  char names[10][25];
  char word[25];
  char quit[25];
  quit[0] = 'q';

  do {
    scanf("%s",word);
    /*
    If the user enters q they can quit
    */
    if(word[0] == quit[0]){
      done = 1;
      continue;
    }
    scanf("%d ",&current);
    strcpy(names[i], word);
   
    avg += current;
    if(current > max){
      max = current;
      pos1 = i;
    }
    if(current < min){
      min = current;
      pos2 = i;
    } 
    i++;
    done = 1;
    if(word[0] != quit[0]){
      done = 0;
    }
  }while(done == 0);
  avg = avg/i;
  printf("\nThe average score was: %f\n",avg);
  printf("%s had the minimum score of %d\n",names[pos2],min);
  printf("%s had the maximum score of %d\n",names[pos1],max);
}
/*
======================================================================================================
*/

/*
======================================================================================================
This function will determine the tax amount according to the following tax rules:
Tax rates depend on income, martial status and state residency.
In state residents rates {
Single and income < 30000 tax rate->20%
Single and income > 30000 tax rate->25%
married and income < 50000 tax rate -> 10%
married and incom >= 50000 tax rate -> 15%
}
Out of state residents {
  same rules but -3%
}
*/
double compute_tax(int income, char *status, char state){
  const char *comp[4];
  comp[0] = "single";
  comp[1] = "SINGLE";
  comp[2] = "married";
  comp[3] = "MARRIED";
  double rate = 0;
  int i = 0;
  
    /*
    Used to validate input
    */
   if(income < 0){
     return -1;
   }
    if(state == 'i' || state == 'o'){
   }
   else{
     return -1;
   }
  
   if(strcmp(status,comp[0]) == 0 || strcmp(status,comp[1]) == 0){
   }
   else if(strcmp(status,comp[2]) == 0 || strcmp(status,comp[3]) == 0){
   }
   else{
     return -1;
   }

  if(strcmp(status,comp[0]) == 0 || strcmp(status,comp[1]) == 0){
    /*
    if single
    */
    if(income < 30000){
      rate = 20;
    }
    else{
      rate = 25;
      }
    }
    else{
    /*
    if married
    */
      if(income < 50000){
        rate = 10;
      }
      else{
        rate = 15;
      }
    }
  
  if(state == 'o')
    {
      rate = rate - 3;
    }

 return rate;
}
/*
======================================================================================================
*/

/*
======================================================================================================
This function will take the input parameters as coefficents of a quadratic equation.
It wil then compute if there are solutions
if there are solutions it will return the solutions if not it will return 0
*/
int quadratic(double a, double b, double c, double *solution1, double *solution2){
  double cando = (b*b) - 4*a*c;
  if(cando >= 0){
    *solution1 = ((b*-1) + sqrt((b*b)-(4*a*c)))/(2*a);
    *solution2 = ((b*-1) - sqrt((b*b)-(4*a*c)))/(2*a);
    return 1;
  }
  else
  {
    return 0;
  }
}
/*
======================================================================================================
*/

/*
======================================================================================================
This fuction will recusivly compute the factorial of n
*/
int factorial(int n){
  if(n <= 1){
    return 1;
  }
  else
  {
    return n*factorial(n-1);
  }
}
/*
======================================================================================================
*/

/*
======================================================================================================
This function will count all the characters and lines in file
*/
void file_count(char *file, int *characters, int *lines){
  int c_count, l_count, done = 0;
  char c;
  FILE *fp;
  fp = fopen(file, "r");
  while((c = fgetc(fp)) != EOF){
    c_count++;
    if(c == '\n' || c == '\0'){
      l_count++;
    }
  }
  *characters = c_count;
  *lines = l_count;
}
/*
======================================================================================================
*/

void file_sort(char *infile, char *outfile){
  FILE *fp;
  int *id;
  char *grade;
  double *gpa;

  fp = fopen(infile, "r");
  int total = fgetc(fp);
  total = total -48;
  /*
  Create dynamic arrays
  */
  id = (int *)malloc(total * sizeof(int));
  grade = (char *)malloc(total * sizeof(char));
  gpa = (double *)malloc(total * sizeof(double));

  /*
  Read in data
  */
  int i = 0;
  for(i = 0; i<total; i++){
    fscanf(fp,"%d", &id[i]);
    fscanf(fp," %c", &grade[i]);
    fscanf(fp,"%lf", &gpa[i]);
  }
  fclose(fp);

  /*
  Sort the data
  */
  int temp_id, min;
  char temp_gr;
  double temp_gpa;
  for(i = 0; i<total; i++){
    min = id[i];
    
  }

 /*
 Write the data
 */
  

}


/*
Switch statement menu for debug and choosing function
*/
int main ()
{
  printf("Welcome to Nathaniel Fishel's Assignment Two.\nPlease enter a question number to use.\n>");
  int choice;
  scanf("%d",&choice);
  printf("\nYou entered: %d\n",choice );
  double pick;

  switch (choice) {
    case 1:
    printf("\nEnter a number to compute pi to the first nth terms\n>");
    scanf("%lf",&pick);
    double pi = compute_pi(pick);
    printf("\nPi = %f\n",pi);
    break;

    case 2:
    printf("\nEnter a number to find its square root\n>");
    scanf("%lf",&pick);
    double sqrt = compute_sqrt(pick);
    printf("\nThe square root of %f is %f\n",pick,sqrt);
    break;

    case 3:
    printf("\nEnter a number and all prime <= will be displayed\n>");
    scanf("%lf",&pick);
    display_primes(pick);
    break;

    case 4:
    printf("This function will read student names and scores\nEnter data in the this way\n Name Score\nPress q to exit");
    process_scores();
    break;

    case 5:
    printf("This function will collect your information and return your tax rate\n");
    int income;
    char status[7];
    char state;
    double rate;
    printf("Enter your income\n>");
    scanf("%d", &income);
    printf("Enter i for in-state, or o for out of state\n>");
    scanf(" %c", &state);
    printf("Enter your status\n>");
    scanf("%s", status);
    rate = compute_tax(income, status, state);
    printf("\nYour tax rate is %f ", rate);
    break;

    case 6:
    printf("This function will read coefficents for a quadratic function and let you know if it has a solution, if it has a solution it will be displayed\n");
    double a,b,c;
    double x, y;
    printf("Enter coefficent a, b, c sperated by spaces\n>");
    scanf("%lf %lf %lf",&a,&b,&c);
    int solveable = quadratic(a,b,c,&x,&y);
    if(solveable == 0){
      printf("\nNo solution");
    }
    else{
      printf("The equation is solveable\nThe solutions are %f and %f", x, y);
    }
    break;

    case 7:
    printf("This function will compute factorial of your chosen interger");
    int pick;
    printf("\nPlease enter your interger\n>");
    scanf("%d",&pick);
    pick = factorial(pick);
    printf("The factorial is: %d",pick);
    break;

    case 8:
    printf("This function will count the characters and lines in a file");
    char file_name[25];
    printf("\nPlease enter a file name\n>");
    scanf("%s",file_name);
    int character_count = 0;
    int line_count = 0;
    file_count(file_name, &character_count, &line_count);
    printf("\nIn the file: %s there are %d characters and %d lines",file_name,character_count,line_count);
    break;

    case 9:
    printf("This function will read student information and then sort it based on id numbers");
    char input[25];
    char output[25];
    printf("\nEnter the file name of the input\n>");
    scanf("%s",input);
    printf("\nEnter the file name for the output file\n>");
    scanf("%s",output);
    file_sort(input, output);
    break;




  }


}
