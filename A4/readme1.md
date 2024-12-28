# Assignment 4 Question 1: Philosopher's Dining Table Problem

## Program Structure
The program is structured into several functions:

eating(int philosopher_id): 
- Simulates the eating action of a philosopher. The function prints a message indicating the philosopher's eating state and introduces a delay to simulate the eating time.

thinking(int philosopher_id): 
- Simulates the thinking action of a philosopher. The function prints a message indicating the philosopher's thinking state and introduces a delay to simulate the thinking time.

void *philosopher(void *args): 
- The main function for philosopher threads. Each philosopher carries out thinking and eating actions in a loop. The philosopher acquires both forks before attempting to eat and releases forks if unable to acquire both.

main(): Initializes mutexes for forks and bowls, creates philosopher threads, and joins them. The program runs an infinite loop of philosophers thinking and eating.

## Deadlock Prevention
To prevent deadlocks, the program introduces a constraint where a philosopher must acquire both forks before attempting to eat. If a philosopher cannot acquire both forks, they release any acquired forks to avoid a cyclic dependency, thus preventing a deadlock.

## Fairness
Fairness is maintained by allowing philosophers to attempt eating only when both forks are acquired. This prevents a single philosopher from indefinitely holding a fork, ensuring all philosophers have an equal chance to eat when the required resources are available. The frequency of a philosopher eating depends on the availability of both forks and bowls, leading to a balanced distribution of eating opportunities.
