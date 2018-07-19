#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// macros
#define N 5 // # of philosophers & forks
#define THINKING 0// Think is 0
#define EATING 1// Eat is 1

/* // mutex lock
#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock */

int state[N] = {1, 1, 1, 1, 1};
pthread_mutex_t forks[N];
pthread_t threads[N];

// Philosopher Function
void *Philosopher(int n){

    while(1){
        think(n);
        pickup(n);
        eat(n);
        putdown(n);
    }
}

void think(int n){
    printf("Phil %d is thinking\n", n);
    sleep(1); 
    //pthread_mutex_t fork[N];
}

void eat(int n){
    printf("Phil %d is eating\n", n);

    for (int i=0; i<N; i++) {
        printf("%d\n", state[i]);
    }	
    sleep(1); 
}

void pickup(int n){
    // revise RTFM for pthread lib
    pthread_mutex_lock(&forks[n]);
    pthread_mutex_lock(&forks[(n+1)%5]);
    state[n] = 0;
}

void putdown(int n){
    pthread_mutex_unlock(&forks[n]);
    pthread_mutex_unlock(&forks[(n+1)%5]);
    state[n] = 1;
}

 

int main(int argc, char *args[]){
   
        // create forks
    for (int i=0; i<N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // create threads
    for (int i=0; i<N; i++) {
        pthread_create(&threads[i], NULL, (void *)Philosopher, (void *)i);
    } 

    for (int i=0; i<N; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}


