
#ifndef THREADS_H
#define THREADS_H

#define MIN_THREADS 1
#define MAX_PER_THREAD 1000000000
#define MIN_PER_THREAD 1
#define MAX_THREADS 1024
#define MAX_PRINTED_NUMBERS 50

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

// Structure Definitions



typedef struct t_thread_data
{
    int    *data;
    size_t  size;
    size_t  space;
} t_thread_data;

typedef struct t_thread_args
{
    t_threads_table  *threads_table;
    int thread_id;
    unsigned long long seed;
} t_threads__args;


typedef enum
{
    LIST_POSITIVE = 0,
    LIST_NEGATIVE = 1,
    LIST_SIZE = 2
};

typedef struct t_list_threads
{
    t_thread_data  *threads_data[LIST_SIZE];
    pthread_mutex_t mutex[LIST_SIZE];
} t_list_threads;



typedef struct t_threads_table
{
    
    int  nbr_threads;
    int nbr_per_thread;
    pthread_t *threads;
    t_list_threads *list_threads;
    t_threads__args *args;
    size_t total_postive_numbers;
    size_t total_negative_numbers;
    unsigned long long seed;

} t_threads_table;



// Function Prototypes

int     parse(const char *str, int *nbr);


#endif