
#include "../inc/threads.h"

int free_threads(t_threads_table *thread_table)
{
    int i;
    if (thread_table)
    {
        i = 0;
        while (i < LIST_SIZE)
        {
            if ((*thread_table).list_threads->threads[i].data)
            {
                free((*thread_table).list_threads->threads[i].data);
                (*thread_table).list_threads->threads[i].data = NULL;
            } 
            i++;
        }
        if ((*thread_table).thread_args)
        {
            i = 0;
            while (i < (*thread_table).nbr_threads)
            {
                if ((*thread_table).thread_args[i])
                {
                    free((*thread_table).thread_args[i]);
                    (*thread_table).thread_args[i] = NULL;
                }
                i++;
            }
            free((*thread_table).thread_args);
            (*thread_table).thread_args = NULL;
        }
        if ((*thread_table).threads)
        {
            free((*thread_table).threads);
            (*thread_table).threads = NULL;
        }
        if ((*thread_table).list_threads)
        {
            free((*thread_table).list_threads);
            (*thread_table).list_threads = NULL;
            
        }
    }
    return (0);
}

int mutex_thread_destroy(t_threads_table *thread_table)
{
	if (thread_table)
	{
		int i;
		i = 0;
		while (i < LIST_SIZE)
		{
			pthread_mutex_destroy(&(*thread_table).list_threads->mutex[i]);
			i++;
		}
	}
	return (0);
}

