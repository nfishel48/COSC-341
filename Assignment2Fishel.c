/*
This program was written for Assignment 2 in COSC 341 with Dr.Maniccam
A copy of this program can be found on my github www.github.come/nfishel48
*/
#include <string.h>
#include <stdio.h>

/*
This funtion will compute pi using n terms
*/
double compute_pi(double n)
{
  int i;
  double pi, frac1, frac2;
  for(i=1; i<=n; i=i+4){
    frac1 = 1/i;
    frac2 = 1/i+2;
    pi = pi+(frac1-frac2);
  }
  pi = pi*4;
  return pi;
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
    next = 1/2*last + x/last;
    last = next;
  }
  return next;
}

/*
This function will return Yes or No if a interger is a Prime Number
*/
int is_prime(int n)
{
  int i;
  for(i=2; i<n-1; i++)
  {
    if(n%i > 0)
    {
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
  int i = 0;



}

/*
Switch statement menu for debug and choosing function
*/
int main ()
{
  printf("Welcome to Nathaniel Fishel's Assignment Two.\n Please enter a question number to use.\n>");
  char choice;
  choice = getchar();

  switch (choice) {
    case 1:
    printf("\nEnter a number to compute pi to the first nth terms\n>");

    compute_pi();
    break;
  }

}
