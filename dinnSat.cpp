#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>

#define N 5 //Define number of philosophers (N) as 5
#define THINKING 2 //Define the state THINKING as 2
#define HUNGRY 1 //Define the state HUNGRY as 1
#define EATING 0 //Define the state EATING as 0
#define LEFT (pno + (N - 1)) % N //Define LEFT as the number of the Philosopher to the left
#define RIGHT (pno + 1) % N //Define LEFT as the number of the Philosopher to the right

int state[N]; //Store the state of each Philosopher in an array. state[i] is the state of Philosopher i and can be 0, 1, or 2 represented by EATING, HUNGRY and THINKING respectively
int phil[N] = { 0, 1, 2, 3, 4 }; //Store Philosopher number in an array

sem_t mutex; //Define mutex as semaphore type
sem_t S[N]; //Define S as an array of semaphore type

void check_and_eat(int pno)
{
    if (state[pno] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) { //Check if Philosopher pno is hungry and the philosophers to the left and right of pno are not eating
        state[pno] = EATING; //Change the state of Philosopher pno to eating
        sleep(2); //Sleep for 2ms
        printf("Philosopher %d takes chopstick %d and %d\n", pno + 1, LEFT + 1, pno + 1); //Print that Philosopher pno takes the chopsticks adjacent to him
        printf("Philosopher %d is Eating\n", pno + 1); //Print that philosopher pno is eating
        sem_post(&S[pno]); //Release the semaphore S[pno] for philosopher pno
    }
}

void take_chopstick(int pno)
{
    sem_wait(&mutex); //Lock mutex by Philosopher pno
    state[pno] = HUNGRY; //Change state of Philosopher pno to HUNGRY
    printf("Philosopher %d is Hungry\n", pno + 1); //Print the state of Philosopher pno
    check_and_eat(pno); //Since Philosopher pno has locked the mutex, he can eat. So call the check_and_eat function
    sem_post(&mutex); //Unlock mutex by Philosopher pno
    sem_wait(&S[pno]); //Wait and lock semaphore S[pno] for Philosopher pno. Wait in case not eaten
    sleep(1); //Sleep for 1ms
}

void put_chopstick(int pno)
{
    sem_wait(&mutex); //Wait and lock mutex by Philosopher pno
    state[pno] = THINKING; //Change the state of Philosopher pno to thinking
    printf("Philosopher %d putting chopstick %d and %d down\n", pno + 1, LEFT + 1, pno + 1); //Inform that Philosopher pno has put the chopsticks adjacent to him down
    printf("Philosopher %d is thinking\n", pno + 1); //Print the state of Philosopher pno
    check_and_eat(LEFT); //Check if Philosopher to the left of pno is hungry. If so, make him eat.
    check_and_eat(RIGHT); //Check if Philosopher to the right of pno is hungry. If so, make him eat.
    sem_post(&mutex); //Unlock mutex
}

void* philospher(void* num)
{
        int* i = num; //i is the Philosopher number which is equal to num
        sleep(1);
        take_chopstick(*i); //Philosopher num takes chopsticks
        sleep(0);
        put_chopstick(*i); //Philosopher num puts the chopsticks back
}

//Main driver function
int main()
{
    int i;
    pthread_t thread_id[N]; //Create array of thread type with N elements
    sem_init(&mutex, 0, 1); //Initialize semaphore mutex with 1
    for (i = 0; i < N; i++)
        sem_init(&S[i], 0, 0); //Initialize semaphore S[i] with 0 for all N philosophers
    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philospher, &phil[i]); //Create a thread for philosopher i
        printf("Philosopher %d is thinking\n", i + 1); //Tell the state of philosopher i
    }
    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL); //Join all threads
}
