/*
Assignment: Determining the number of "cores" are on a machine
Submitted by: Md Ishtiaq Ahmed
Objective: Run a program using multiple threads to determine how many cores are in a computer. 
Here, I created a function to fill up an array repeatedly and call the function using multiple threads.
If the system is using the cores equitably, run times should be until there are more than N threads (where N is the reported number of cores). 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>

#define num_iteration 5 // Number of iterations for each thread count


// Pre condition: None
//Post Condition: Filling up an array repeatedly
void *fill_array(void *arg)
{
    int array_size = 10000; // Size of the array
    int new_array[array_size]; // The array to be filled
    int i, j;
    for (j = 0; j < 10000; j++) // Outer loop for repeated filling
    {
        for (i = 0; i < array_size; i++) // Inner loop to fill the array
        {
            new_array[i] = i; // Assigning values to array elements
        } // end for
    } // end for
    pthread_exit(NULL); // Exit the thread
} // end fill_array

// Pre Condition : A function to fill up an array
// Post Condition: Run the fumction using multple thread and return execution time and standard deviation
int main()
{   
    int num_threads_max; // variable for maximum number of thread to use in the program
    printf("Enter the maximum number of threads: "); 
    scanf("%d", &num_threads_max); // Input for the maximum thread number
    printf("\n");
    pthread_t threads[num_threads_max]; // Array of pthreads to store thread IDs
    double results[num_iteration]; // Array to store execution times for each iteration of thread

    // Loop through different thread counts
    for (int num_threads = 1; num_threads <= num_threads_max; num_threads++) // Outer loop iterating over different thread counts
    {
        printf("Running with: %d thread:\n", num_threads);
        // Loop for multiple iterations
        for (int k = 0; k < num_iteration; k++) // Inner loop for multiple iterations for num_threads
        {
            
            struct timeval start, end; // Structure to hold start and end times
            gettimeofday(&start, NULL); // Execution start time

            // Create and run threads
            for (int i = 0; i < num_threads; i++) // Loop to create multiple threads
            {
                pthread_create(&threads[i], NULL, fill_array, NULL); // Create a thread and call fill_array function
            } // end for

            // Wait for threads to finish
            for (int j = 0; j < num_threads; j++) // Join all  threads
            {
                pthread_join(threads[j], NULL); // Wait for thread to finish execution
            } // end for

            
            gettimeofday(&end, NULL); // Execution end time

            // Convert time spent to nanosecond
            long long startTime = start.tv_sec * 1000000000LL + start.tv_usec * 1000LL; 
            long long endTime = end.tv_sec * 1000000000LL + end.tv_usec * 1000LL; 

            // Calculate execution time
            double cpu_time_used = endTime - startTime; // Calculate elapsed time
            printf("Iteration %d running time: %.0f nano seconds\n", k+1, cpu_time_used);
            results[k] = cpu_time_used; // Store the execution time in the results array
        }// end for

        // Calculating the average running time
        long total = 0; // Variable to store total execution time of all the iteration
        for (int i = 0; i < num_iteration; i++) // Loop to calculate total execution time
        {
            total += results[i]; // total execution time of all the iteration
        } // end for

        // Calculate average
        long avg = total / num_iteration; // Calculate average execution time
        printf("Average Running time using %d thread: %ld nanoseconds\n", num_threads, avg); 

        // Calculating Standard Deviation

        // Calculate the squared differences from the mean
        double squared_diff_sum = 0.0; // Variable to store sum of squared differences
        for (int i = 0; i < num_iteration; ++i) // Loop to calculate squared differences
        {
            double diff = results[i] - avg; // Calculate difference from mean
            squared_diff_sum += diff * diff; // Sum of squared differences
        } // end for

        // Calculate the variance 
        double variance = squared_diff_sum / num_iteration; 

        // Calculate the standard deviation (square root of variance)
        double standard_deviation = sqrt(variance); // Calculate standard deviation

        // Print standard deviation
        printf("Standard Deviation using %d thread: %.2f\n\n", num_threads, standard_deviation); 
    } // end for

    return 0; 
} // end main