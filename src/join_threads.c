#include "../inc/threads.h"

int join_threads(t_threads_table *thread_table)
{
    int i;

    i = 0;
    while (i < (*thread_table).nbr_threads)
    {
        if (pthread_join((*thread_table).threads[i], NULL) != 0)
        {
            free_threads(thread_table);
            return (1);
        }
        i++;
    }
    return (0);
}
