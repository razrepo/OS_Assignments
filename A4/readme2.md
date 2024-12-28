# ASSIGNMENT 4 QUESTION 2 LOADING UNLOADING

## CAR Structure:

carMutex: Semaphore for car synchronization.
passMutex: Semaphore for passenger synchronization.
passCurr: Current number of passengers in the car.
passTot: Capacity of passengers in the car.
passCurrArr: Array to track seated passengers.

## Functions

*car(void args): Car thread that manages the loading, running, and unloading procedures.
*passenger(void args): Passenger thread that boards and disembarks from the car.
load(): Initiates the loading process by setting passenger array elements to 0.
unload(): Initiates the unloading process by setting passenger array elements to -1.
board(int passenger_id): Prints a message when a passenger boards the car.
offboard(int passenger_id): Prints a message when a passenger disembarks from the car.
*init_array(int arr, int num): Initializes an array with -1 values.

## Synchronization

carMutex: Ensures exclusive access to car-related operations.
passMutex: Facilitates synchronization between the car and passengers.

## Assumptions

The program assumes a sleep time for the ride duration.
