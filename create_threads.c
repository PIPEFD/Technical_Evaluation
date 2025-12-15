
#include "threads.h"



int	create_threads(t_threads_table *thread_table)
{
	int i;


	i = 0;
	while (i < (*thread_table).nbr_threads)
	{
		
        if (pthread_create(&(*thread_table).threads[i], NULL, 
        (void *(*)(void *))generation_aletory_numbers, 
        (void *)thread_table->thread_args[i]) != 0)
		{
            // free_threads(thread_table);
			return (1);
		}
        i++;
	}
    
	return (0);
}
