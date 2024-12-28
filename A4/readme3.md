# ASSIGNMENT 4 QUESTION 3 Bridges

## Code Logic

### Car Struct

- The struct car is used to represent each car, holding an id for identification and lrdirec indicating the direction from which the car is approaching (0 for left, 1 for right).

### Synchronization Mechanisms

- Mutex (pthread_mutex_t mutex): Ensures exclusive access to critical sections of the code, preventing data races when updating shared variables.

- Condition Variable (pthread_cond_t cond): Allows threads to wait for specific conditions to be met before proceeding, enabling efficient synchronization.

- Semaphores (sem_t left, right): Control the number of cars allowed on each side of the bridge. This prevents congestion and ensures fairness in allowing cars to cross.

## Functions

### cross_bridge(void *ptr)

- This function embodies the main behavior of a car crossing the bridge:

- Mutex Locking/Unlocking: The mutex is locked before entering critical sections and unlocked afterward to ensure exclusive access.

- Condition Waiting: Cars wait in a loop while conditions for safe crossing are not met. This prevents cars from crossing when the bridge is congested or when cars from the opposite side are crossing.

- Semaphore Usage: Semaphores are used to control the number of cars on each side, ensuring that the maximum allowed cars are not exceeded.

- Critical Section Updates: The number of cars and the count on each side are updated within critical sections, ensuring that these updates are atomic.

- Sleep and Printing: Simulates the time taken for a car to cross the bridge. Prints messages indicating when a car has crossed from the left or right side.

- Semaphore Post: Signals that a car has successfully crossed, allowing waiting cars on the same side to proceed.

### main()

- Input Handling: User input is taken for the number of cars from each side.

- Semaphore Initialization: Semaphores for the left and right sides are initialized with a capacity of 5 each.

- Thread Creation: Threads for each car are created dynamically based on user input.

- Thread Joining: Ensures that the main program waits for all cars to complete their crossings.

- Semaphore Destruction: Releases system resources by destroying semaphores.

## Avoiding Concurrency Bugs

- Concurrency bugs, such as data races and deadlocks, are avoided through careful synchronization:

- Mutex Usage: The mutex is employed to provide exclusive access to critical sections, preventing multiple threads from concurrently modifying shared variables.

- Condition Variables: The use of condition variables ensures that threads wait for specific conditions before proceeding, preventing unnecessary busy-waiting.

- Semaphores: Semaphores are used to control access to shared resources (the bridge) and avoid congestion by limiting the number of cars allowed on each side.

- Atomic Updates: Critical section updates, such as incrementing the number of cars, are performed atomically within mutex-protected regions, avoiding data races.

- Dynamic Thread Creation: Using a while loop for dynamic thread creation ensures that the number of threads is based on user input, preventing potential overflows.

- By employing these synchronization mechanisms, the code ensures safe and efficient crossing of the bridge by multiple cars, preventing concurrency bugs and ensuring the integrity of shared data.
