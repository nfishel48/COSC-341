#include <stdio.h>
#include <stdlib.h>


void gpa(student list[], int length)
{
    int average;
    int i = 0;
    for(i = 0; i<=length; i++)
    {

    }
}

void factors()
{
    int done = 0;
    while(done == 0)
    {
        printf("Enter positive integer: ");
        int input;
        scanf("%d", &input);
        if(input == -1)
        {
            exit(0);
        }
        int i =0;
        for(i = 0; i<=input; i++)
        {
            if(input%i  > 0)
            {
               
            }
            else
            {
                printf("%d",i); 
            }   
        }
    }
}


int main()
{
struct student {
    char name[20];
    double gpa;
};

}