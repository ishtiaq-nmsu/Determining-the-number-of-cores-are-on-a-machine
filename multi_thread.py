'''
Assignment: Determining the number of "cores" are on a machine
Submitted by: Md Ishtiaq Ahmed
Objective: Run a program using multiple threads to determine how many cores are in a computer. 
Here, I created a function to fill up an array repeatedly and call the function using multiple threads.
If the system is using the cores equitably, run times should be until there are more than N threads (where N is the reported number of cores). 

'''

import threading 
import time  
import statistics  
import os

cpu_count = os.cpu_count() # Get the core count of the computer
print(f'Number of CPUs: {cpu_count}\n' )

# Function to fill the array
# Pre condition: None
# Post Condition: Filling up an array repeatedly
def fill_array():
    array_size = 10000  # Size of the array

    # Fill the array 100 times
    for _ in range(100):
        
        new_array = [i for i in range(array_size)] 
    # end for
# end fill_array

# Function to run the threads
# Pre condition: A function to fill up an array multiple times
# Post Condition: fill_array function will be executed using multiple threads and return the execution time       

def thread_count(num_threads_max):
    iteration = []  # List to store execution times of each iteration
    print(f'Running with {num_threads_max} thread:')

    # Run 5 iterations
    for i in range(1, 6):
        start_time = time.time()  # Get the start time of the iteration
        threads = []  # List to store the thread objects

        # Create and start multiple threads
        for _ in range(num_threads_max):
            # Create a thread targeting the fill_array function
            thread = threading.Thread(target=fill_array)
            threads.append(thread)  # Append the thread to the list
            thread.start()  # Start the thread 
        #end for

        # Wait for all threads to finish
        for thread in threads:
            thread.join() 
        # end for

        end_time = time.time()  # End time of the iteration

        # Calculate the execution time of the iteration in nanoseconds
        run_time = (end_time - start_time) * 1e9
        iteration.append(run_time)  # Append the execution time to the list

   
        print(f'Iteration {i} running time: {run_time} nanoseconds')
    # end for

    # Calculate and print the average and standard deviation
    standard_deviation = statistics.stdev(iteration) # Standard Deviation
    avg = statistics.mean(iteration) # Average 
    print(f'Average Running time using {num_threads_max} thread:  {avg} nanoseconds')
    print(f'Standard Deviation using {num_threads_max} thread: {standard_deviation} \n')
# end thread_count


# Run the thread_count function 
num_threads = int(input("Enter the maximum number of threads: ")) # get the max number of thread from user input
# Execute the thread_count function using 1 thread to num_thread
for i in range(1, num_threads+1):
    thread_count(i) # call the thread_count function 
#end for



