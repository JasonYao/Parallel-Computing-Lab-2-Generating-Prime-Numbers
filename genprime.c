#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

/* By Jason Yao */
typedef enum { false, true } bool;      /* Enables boolean types */

/* Configuration settings */
bool IS_DEBUG_MODE = false;             /* Change to true to switch to debugging mode */
bool IS_SEQUENTIAL_MODE = false;        /* Change to true to switch to sequential version */
bool IS_TIMED_MODE = false;             /* Change to true to switch to show runtime */

/***** Globals ******/
int *fullValues;                        /* Array to contain all numbers from [2, N] */
bool *isPrime;                          /* Array telling whether the value is prime or not */
int N;                                  /* The upper bound of the values to check */
int *primeValues;                       /* Implements a list of prime values */
int primeValuesSize = 1;                /* The size() of the prime-number list */

/* Setup functions */
int initialise(char *argv[]);           /* Read input from file */
void cleanup(char *string);             /* Free()'s anything that we have malloc'd */

/* Solution suite function declarations */
void sequential();                      /* Runs the sequential version of the code */
void parallel(int numberOfThreads);     /* Runs the parallel version of the code */

/* Testing suite function declarations */
void testFullValues();
void testIsPrime();
void testAll();

/**********************
 * Test Suite Functions
 **********************/
void testFullValues()
{
    int i;
    printf("The fullValues[i] matrix:\n");
    for (i = 0; i < N; ++i)
        printf("%d ", fullValues[i]);
    printf("\n");
    printf("---------------------------------------------\n");
} // End of test full values function

void testPrimeValues()
{
    int i;
    printf("The primeValues[i] matrix:\n");
    for (i = 0; i < N; ++i)
        printf("%d ", primeValues[i]);
    printf("\n");
    printf("---------------------------------------------\n");
} // End of the test prime values function

void testIsPrime()
{
    int i;
    printf("The isPrime[i] matrix:\n");
    for (i = 0; i < N; ++i)
    {
        if (isPrime[i])
            printf("Y ");
        else
            printf("N ");
    }
    printf("\n");
    printf("---------------------------------------------\n");
} // End of test isPrime values function

void testAll()
{
    testFullValues();
    testIsPrime();
    testPrimeValues();
} // End of the test all function

/**
 * Sequential functions
 */
void sequential()
{
    int current;
    for (current = 2; current < N; ++current)
    {
        if (isPrime[current])
        {
            // Marks all multiples of this prime value as false
            for (int i = current; i < N; i += current)
                isPrime[i] = false;

            primeValues[primeValuesSize] = current;
            ++primeValuesSize;
        } // End of marking future values
    } // End of iterating through all generations
} // End of the sequential wrapper function

/**
 * Parallel functions
 */

/**
 * Parallel solution:
 * 1.) We will iterate through all numbers [2, N]
 * 2.) When iterating, we will check if a value is prime
 * 3.) If the value is prime, fork, and give each thread a portion of the multiples to the isPrime[] array
 * 4.) Once all multiples are marked as not prime, join again, and continue
 */
void parallel(int numberOfThreads)
{
    int current;
    for (current = 2; current < N; ++current)
    {
        if (isPrime[current])
        {
            // Marks all multiples of this prime value as false
            # pragma omp parallel num_threads(numberOfThreads)
            {
                #pragma omp for
                for (int i = current; i < N; i += current)
                    isPrime[i] = false;
            }

            primeValues[primeValuesSize] = current;
            ++primeValuesSize;
        } // End of marking future values
    } // End of iterating through all generations
} // End of the parallel wrapper function

/**
 * Setup functions
 */
void cleanup(char *outputFile)
{
    free(outputFile);
    free(fullValues);
    free(isPrime);
    free(primeValues);
} // End of the cleanup function

int initialise(char *argv[])
{
    N = atoi(argv[1]);

    // Deals with full values
    fullValues = (int *) malloc(N * sizeof(int));
    if( !fullValues)
    {
        printf("Cannot allocate full values array!\n");
        exit(1);
    }

    int i;
    for (i = 0; i < N; ++i)
        fullValues[i] = i;

    // Deals with isPrime
    isPrime = (bool *) malloc(N * sizeof(bool));
    if( !isPrime)
    {
        printf("Cannot allocate is prime array!\n");
        exit(1);
    }

    int j;
    for (j = 0; j < N; ++j)
        isPrime[j] = true;

    // Deals with primeValues
    int floor = ((N + 1) / 2) + 1; // We add one to the floor to keep rank consistent, and simply don't use primeVal[0]
    primeValues = (int *) malloc(floor * sizeof(int));
    if( !primeValues)
    {
        printf("Cannot allocate prime values array!\n");
        exit(1);
    }

    primeValues[0] = 2;

    return atoi(argv[2]); // Returns the number of threads
} // End of the initialise function

void output(char* outputFile)
{
    FILE * out = fopen(outputFile, "w");

    // test for files not existing.
    if (out == NULL)
    {
        printf("Error! Could not open file\n");
        exit(-1); // must include stdlib.h
    }

    int i;
    for (i = 1; i < primeValuesSize; ++i)
        fprintf(out, "%d %d %d\n", i, primeValues[i], primeValues[i] - primeValues[i - 1]); // write to file
    fclose(out);
} // End of the output function

int main(int argc, char *argv[])
{
    /* Timing stuff */
    double tstart, ttaken;

    if( argc != 3)
    {
        printf("Usage: ./genprime <N_value> <number_of_threads>\n");
        exit(1);
    }

    /* Read the input file and fill the global data structure above */
    int numberOfThreads = initialise(argv);

    /* Setting up for file output */
    char *fileExtension = ".txt\0";
    char *outputFile = malloc(strlen(argv[1]) + strlen(fileExtension) + 1);
    outputFile[0] = '\0';   // ensures the memory is an empty string
    strcat(outputFile, argv[1]);
    strcat(outputFile, fileExtension);

    /* Start of timing the middle section */
    tstart = omp_get_wtime();

    if (IS_DEBUG_MODE)
        printf("Number of threads: %d\n", numberOfThreads);

    if (IS_SEQUENTIAL_MODE)
    {
        sequential();

        // Timing stuff
        if (IS_TIMED_MODE)
        {
            ttaken = omp_get_wtime() - tstart;
            printf("Time take for the main part: %f\n", ttaken);
        }

        // Outputs the prime values
        output(outputFile);
    } // End of sequential mode
    else
    {
        parallel(numberOfThreads); // Implicit blocking in the for-loops results in no need for an explicit barrier

        int thread_rank = omp_get_thread_num();
        if (thread_rank == 0)
        {
            if (IS_TIMED_MODE)
            {
                ttaken = omp_get_wtime() - tstart;
                printf("Time take for the main part: %f\n", ttaken);
            }

            // Outputs the prime values
            output(outputFile);
        }
    } // End of parallel mode

    if (IS_DEBUG_MODE)
        testAll();

    cleanup(outputFile);
    return EXIT_SUCCESS;
} // End of the main function