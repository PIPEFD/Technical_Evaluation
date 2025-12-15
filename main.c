#include "threads.h"



int main (int argc, char **argv)
{

    t_threads_table  threads_table;

    int     nbr_threads;
    int     nbr_per_thread;

    if (argc != 3)
        return(write(2, "Usage: ./program <nbr_threads> <nbr_per_thread>\n", 48), 1);
    if (parse(argv[1], &nbr_threads) != 0 || parse(argv[2], &nbr_per_thread) != 0)
        return(write(2, "Error: Invalid arguments\n", 25), 1);
    if (set_threads(&threads_table, &nbr_threads, &nbr_per_thread) != 0 || thread_memory_allocation(&threads_table) != 0)
    return (write(2, "Error: Initialization failed\n", 29), 1);
    if(create_threads(&threads_table) != 0)
        return (write(2, "Error: Thread creation failed\n", 30), 1);
    if(join_threads(&threads_table) != 0)
        return (write(2, "Error: Thread joining failed\n", 29), 1); 
    printf("Number of threads: %d\n", nbr_threads);
    printf("Number per thread: %d\n", nbr_per_thread);
    return(0);
}