/*
This program was written for Assignment 2 in COSC 341 with Dr.Maniccam
A copy of this program can be found on my github www.github.come/nfishel48
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
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
    printf("%f\n",last);
  }
  return next;
}

/*
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
This function will read student names and scores from the user. Then it will display 
the average, the minimum, and the maximum along with that sudents name
*/
void process_scores(){
  printf("\nPlease enter your data\n");
  int i, current, done = 0;
  char *names;
  names = (char*)malloc( 10* sizeof(char));

  while(done == 0){
    printf(">");
    /*
    Problem is here
    scanf("%s %d",&names[i], &current);
    */
    printf("HERE");
    if(names[i] == 'q'){
      done = 1;
    }
    i++;
  }
  printf("Here are the names %s",names[0]);
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
    printf("\nPi = %f",pi);
    break;

    case 2:
    printf("\nEnter a number to find its square root\n>");
    scanf("%lf",&pick);
    double sqrt = compute_sqrt(pick);
    printf("\nThe square root of %f is %f",pick,sqrt);
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

  }


}
