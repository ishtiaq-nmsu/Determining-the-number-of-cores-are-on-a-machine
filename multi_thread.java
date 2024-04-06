/*
Assignment: Determining the number of "cores" are on a machine
Submitted by: Md Ishtiaq Ahmed
Objective: Run a program using multiple threads to determine how many cores are in a computer. 
Here, I created a function to fill up an array repeatedly and call the function using multiple threads.
If the system is using the cores equitably, run times should be until there are more than N threads (where N is the reported number of cores). 
*/
// Multithread code reference from https://stackoverflow.com/questions/5238397/populating-array-from-different-threads
// Multithread code reference from https://www.geeksforgeeks.org/multithreading-in-java/

import java.util.Arrays;
import java.util.Scanner;

//Pre condition: None
//Post condition: Execute the fill_array method using multiple thread for multiple iteration. Return average and standard deviation
// of runnning time for each thread 
public class multi_thread {
    public static void main(String[] args) {
        int cpuCount = Runtime.getRuntime().availableProcessors(); // Get the core count of the computer
        System.out.println("Number of CPUs: " + cpuCount);
        System.out.println();

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the maximum number of threads: ");
        final int num_threads_max = scanner.nextInt(); // Maximum number of threads to use
        scanner.close();
        final int numIterations = 5; // Number of iterations per thread
        final int arraySize = 100000; // Size of the array

        // Iterate over each thread configuration
        for (int numThreads = 1; numThreads <= num_threads_max; numThreads++) {
            System.out.println("Running with " + numThreads + " thread:");
            long[] executionTimes = new long[numIterations]; // Array to store execution times for each iteration

            // Run multiple iterations
            for (int i = 0; i < numIterations; i++) {
                long startTime = System.nanoTime(); // Start time of the iteration
                fill_array(arraySize, numThreads); // Run the iteration
                long endTime = System.nanoTime(); // End time of the iteration
                long iterationTime = endTime - startTime; // Calculate iteration time
                executionTimes[i] = iterationTime; // Store iteration time in the array
                System.out.println("Iteration " + (i + 1) + " running time: " + iterationTime + " nanoseconds"); 
            } // end for

            // Calculate and print average and standard deviation
            double average = get_average(executionTimes); // Calculate average execution time
            double standard_deviation = get_std_dev(executionTimes); // Calculate standard deviation
            System.out.println("Average Running time using " + numThreads + " thread: " + average + " nanoseconds");
            System.out.println(
                    "Standard deviation using " + numThreads + " thread: " + standard_deviation + " nanoseconds"); 
 
            System.out.println();
        } // end for
    } // end main

    // Method to fill the array
    // Pre condition: None
    // Post Condition: Filling up an array repeatedly using multiple threads
    public static void fill_array(int arraySize, int numThreads) {
        Thread[] threads = new Thread[numThreads]; // Create an array of threads
       
        for (int i = 0; i < numThreads; i++) {
            // final int threadIndex = i;
            threads[i] = new Thread(() -> {
                int[] new_array = new int[arraySize];
                for (int j = 0; j < 10000; j++) // Outer loop for repeated filling
                {
                    for (int k = 0; k < arraySize; k++) // Inner loop to fill the array
                    {
                        new_array[k] = k; // Assigning values to array elements
                    }
                }
            });
            threads[i].start(); // Start each thread
        } // end for

        // Wait for all threads to finish
        for (Thread thread : threads) {
            try {
                thread.join(); // Wait for each thread to finish
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        } // end for
    } // end fill_array

    // Method to calculate average
    public static double get_average(long[] numbers) {
        long sum = 0;
        for (long num : numbers) {
            sum += num; // Sum up all the numbers
        }
        return (double) sum / numbers.length; // return the average
    }

    // Method to calculate standard deviation
    public static double get_std_dev(long[] numbers) {
        double mean = get_average(numbers); // Calculate the mean
        double squared_diff_sum = 0; // Variable to store sum of squared differences
        for (long num : numbers) { // Loop to calculate squared differences
            squared_diff_sum += (num - mean) * (num - mean); // Sum of squared differences
        }
        // Calculate the variance
        double variance = squared_diff_sum / numbers.length;
        return Math.sqrt(variance); // Return the standard deviation
    }
}