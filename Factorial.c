/////////////////////////////////////////////////////////////////
//
// Kenta Suzue
//
// Factorial.c
//
// Compile:  gcc Factorial.c -o Factorial -lpthread
//
// Run:      ./Factorial <N>
//
//           <N>: an integer for which the factorial is to be
//                calculated 
//
///////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Global variables
int factorial_in;
long factorial_out = 1;

// Serial function
void Error_check(int argc, char** argv);

// Thread function 
void *Pth_factorial();

int main(int argc, char* argv[]) 
{
    pthread_t* thread_handle;

    thread_handle = malloc(sizeof(pthread_t));

    Error_check(argc, argv);

    pthread_create(thread_handle, NULL, Pth_factorial, NULL);

    pthread_join(*thread_handle, NULL);

    printf("%d! is %lld.\n", factorial_in, factorial_out);

    free(thread_handle);

    return 0;
}  

//The function Error_check reads in the number for which the factorial is calculated.
//The function Error_check also performs error checking on the command line arguments.
//The number of arguments must be 2.
//The number for which the factorial is calculated must be between 0 and 20.
//The maximum of 20 is chosen, since 20! is about 2.4E18 and still less than LLONG_MAX = 9.2E18.
void Error_check(int argc, char** argv)
{
    //Error checking that the number of arguments is 2.
    // If not, print help for the format of the run command.
    if (argc != 2)
    {
        fprintf(stderr, "Error: The number of arguments is incorrect!\n");
        fprintf(stderr, "USAGE: ./Factorial <N>\n");
        fprintf(stderr, "<N>: an integer for which the factorial is to be calculated.\n");

        exit(0);
    }

    factorial_in = atoi(argv[1]);

    //Error checking that the number for which the factorial is to be calculated is between 0 and 20.
    //If not, print help that the the number for which the factorial is to be calculated
    // should be between 0 and 20.
    if ((factorial_in < 0) || (factorial_in > 20))
    {
        fprintf(stderr, "Error: The number for which the factorial is calculated should be between 0 and 20.\n");

        exit (0);
    }
}

// The thread function Pth_factorial calculates factorial for the integer in the global variable
// factorial_in.
// The result is stored in the long global variable factorial_out 
void *Pth_factorial()
{
    int i;

    for (i = 1; i <= factorial_in; i++) 
    {
        factorial_out *= i;
    }

    return NULL;
}  
