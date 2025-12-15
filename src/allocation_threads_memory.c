
#include "../inc/threads.h"



int mutex_thread_init(t_threads_table *thread_table)
{
	if (thread_table)
	{
		int i;
		i = 0;
		while (i < LIST_SIZE)
		{
			if (pthread_mutex_init(&(*thread_table).list_threads->mutex[i], NULL) != 0)
			{
				mutex_thread_destroy(thread_table);
				return (1);
			}
            i++;
		}
	}
	return (0);
}



int thread_args_allocation(t_threads_table *thread_table)
{
    if (thread_table)
    {
        int i;
        thread_table->thread_args = (t_thread_args **)malloc(sizeof(t_thread_args *) * thread_table->nbr_threads);
        if (!thread_table->thread_args)
            return (free_threads(thread_table), 1);        
        i = 0;
        while (i < (*thread_table).nbr_threads)
        {
            thread_table->thread_args[i] = (t_thread_args *)malloc(sizeof(t_thread_args));
            if (!thread_table->thread_args[i])
                return (free_threads(thread_table), 1);
            thread_table->thread_args[i]->thread_table = thread_table;
            thread_table->thread_args[i]->thread_id = i;
            thread_table->thread_args[i]->seed = init_thread_aletory_rng_seed(thread_table, (void*)thread_table->thread_args[i],i);
            // printf("Allocated thread arguments at address %p for thread %d with final seed %llu\n\n", 
                (void*)thread_table->thread_args[i], 
                i, 
                thread_table->thread_args[i]->seed);
            // printf("Memory address of seed in thread args: %p\n", (void*)&thread_table->thread_args[i]->seed);
            // printf("--------------------------------------------------\n");
            i++;
        }
    }
    return (0);
}

int list_thread_allocation(t_threads_table *thread_table, size_t size_list)
{
	if (thread_table && (size_list > 0 && size_list <= (size_t)(INT_MAX)))
	{
		int i;
		i = 0;
		while (i < LIST_SIZE)
		{
			(*thread_table).list_threads->threads[i].data = (int *)calloc(size_list, sizeof(int));
			if (!(*thread_table).list_threads->threads[i].data)
				return (free_threads(thread_table), 1);
			(*thread_table).list_threads->threads[i].size = 0;
			(*thread_table).list_threads->threads[i].space = size_list;
			i++;
		}
        return (0);
	}
	return (1);
}


int thread_memory_allocation(t_threads_table *thread_table)
{
    	if (thread_table)
	{
		size_t size_list;

        // Calculate total size needed for thread data lists
		size_list = (size_t)(thread_table->nbr_threads) * (size_t)(thread_table->nbr_per_thread);

		(*thread_table).threads = (pthread_t *)malloc(sizeof(pthread_t) * thread_table->nbr_threads);
		
		if (!(*thread_table).threads)
			return (1);
		(*thread_table).list_threads = (t_list_threads *)malloc(sizeof(t_list_threads));
		if (!(*thread_table).list_threads)
            return (free_threads(thread_table), 1);
		if (list_thread_allocation(thread_table, size_list) != 0)
		{
			return (1);
		}
		if (thread_args_allocation(thread_table) != 0)
		{
			return (1);
		}
		if (mutex_thread_init(thread_table) != 0)
		{
			return (1);
		}
        return (0);
	}
	return (1);
}
