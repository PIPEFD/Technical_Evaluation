#include "../inc/threads.h"


unsigned long long set_hash_mix(unsigned long long x)
{
    unsigned long long hash;

    if (x != 0)
    {
        hash = x ^ (x >> 42);
        hash = hash * 0xff51afd7ed558ccdULL;
        hash = hash ^ (hash >> 42);
        hash = hash * 0xc4ceb9fe1a85ec53ULL;
        hash = hash ^ (hash >> 42);
        // printf("hash %llu\n", hash);
        return (hash);
    }
    return (0x123456789abcdefULL);
}



int set_seed_threads(t_threads_table *thread_table, unsigned long long *seed)
{
    unsigned long long  base_seed;
    pid_t               current_pid;
    time_t              current_time;

    current_pid = getpid();
    current_time = time(NULL);

    if (thread_table && seed)
    {
     
        base_seed = (unsigned long long)(current_time ^ (current_pid << 16));
        base_seed  ^= (unsigned long long)thread_table;
        *seed = set_hash_mix(base_seed);
        return(0);
    }
    return(1);
}

int     set_threads(t_threads_table *thread_table, int *nbr_threads, int *nbr_per_thread)
{
    unsigned long long  seed;

    if (thread_table && nbr_threads && nbr_per_thread &&
        *nbr_threads >= MIN_THREADS && *nbr_threads <= MAX_THREADS &&
        *nbr_per_thread >= MIN_PER_THREAD && *nbr_per_thread <= MAX_PER_THREAD)
    {
        (*thread_table).nbr_threads = *nbr_threads;
        (*thread_table).nbr_per_thread = *nbr_per_thread;
        (*thread_table).total_negative_numbers = 0;
        (*thread_table).total_positive_numbers = 0;

        if (set_seed_threads(thread_table, &seed) == 0)
            (*thread_table).seed = seed;
        // printf("nbr_threads %d\n", (*thread_table).nbr_threads);
        // printf("nbr_per_thread %d\n", (*thread_table).nbr_per_thread);
        // printf("seed %llu\n", (*thread_table).seed);
        return(0);
    }
    return(1);
}