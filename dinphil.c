#include <stdio.h>
#include <pthread.h>

// macros
#define N 5 // # of philosophers & forks
#define THINKING 0// Think is 0
#define EATING 1// Eat is 1

// mutex lock
#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock

int state[N];

typedef struct {
    int position;
    int count;
    //int *state;
    pthread_mutex_t *mon;
    pthread_cond_t **cv;
    //pthread_t *leftFork = &fork[i];
    //pthread_t *rightFork = &fork[i+1 % N];
} phil_t;

void *Philosopher(void *arg);

void think(phil_t *phil);
void eat(phil_t *phil);
void pickup(phil_t *phil);
void putdown(phil_t *phil);



// Philosopher Function
void *Philosopher(void *arg){
    phil_t *phil = (phil_t *)arg;

    while(1){
        think(phil);
        pickup(phil);
        eat(phil);
        putdown(phil);
    }
}

void think(){
    //pthread_mutex_t fork[N];
}

void eat(){
	
}

void pickup(phil_t *phil){
    // revise RTFM for pthread lib
    phil_t *phil;

    lock(phil->mon);
    pthread_cond_wait(phil->cv, phil->mon);
    phil->state[phil->id] = EATING; // phil->id array hasn't been defined
    unlock(phil->mon);
}

void putdown(phil_t *phil){
    phil_t *phil;

    lock(phil->mon);
    pthread_cond_signal(phil->cv);
    phil->state[phil->id] = THINKING; // phil->id array hasn't been defined
    unlock(phil->mon);
}



int main(){
    int i;
    pthread_t forks[N];
    pthread_t threads[N];
    
    // create forks
    for (i=0; i<N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // create threads
    for (i=0; i<N; i++) {
        phil_t *phil = malloc(sizeof(phil_t));

        phil->position = i;
        phil->count = N; //change this to N[5]? array form?
        phil->leftFork = &forks[i];
        phil->rightFork = &forks[(i+1) % N];
        pthread_create(&threads[i], NULL, Philosopher, (void *)phil);
    }

    for (i=0; i<N; i++) {
        pthread_join(threads[i], NULL);
    }
}


