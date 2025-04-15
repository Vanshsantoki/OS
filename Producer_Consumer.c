#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 10
#define MAX_CYCLES 10  // Define how many times you want to produce and consume

int buffer[SIZE];
int in = 0;
int out = 0;
int count = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

int produced_items = 0;
int consumed_items = 0;

// Function to simulate producer
void* produce(void* arg) {
    while (produced_items < MAX_CYCLES) {  // Run for MAX_CYCLES times
        int item = rand() % 100;

        sem_wait(&empty);        
        pthread_mutex_lock(&mutex); 

        buffer[in] = item;
        printf("Produced: %d at position %d\n", item, in);
        in = (in + 1) % SIZE;
        count++;
        produced_items++;  // Increment the number of produced items

        pthread_mutex_unlock(&mutex);
        sem_post(&full);  

        sleep(2);  // Simulate production time
    }
    return NULL;
}

// Function to simulate consumer
void* consume(void* arg) {
    while (consumed_items < MAX_CYCLES) {  // Run for MAX_CYCLES times
        sem_wait(&full);  
        pthread_mutex_lock(&mutex); 

        int item = buffer[out];
        printf("Consumed: %d from position %d\n", item, out);
        out = (out + 1) % SIZE;
        count--;
        consumed_items++;  // Increment the number of consumed items

        pthread_mutex_unlock(&mutex); 
        sem_post(&empty); 

        sleep(3);  // Simulate consumption time
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    sem_init(&empty, 0, SIZE); 
    sem_init(&full, 0, 0);     
    pthread_mutex_init(&mutex, NULL);  

    pthread_create(&producer_thread, NULL, produce, NULL);
    pthread_create(&consumer_thread, NULL, consume, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}