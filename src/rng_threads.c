#include "../inc/threads.h"



void *generation_aletory_numbers(void *arg)
{
    t_thread_args *thread_args = (t_thread_args *)arg;
    t_threads_table *thread_table = thread_args->thread_table;

    
    int i = 0;
    int random_number;
    int list_index;
    
    while (i < thread_table->nbr_per_thread)
    {
        random_number = init_thread_with_aleatory_rng(&thread_args->seed);
        
        if (random_number < 0)
        list_index = LIST_NEGATIVE;
        else
        list_index = LIST_POSITIVE;
        
        pthread_mutex_lock(&thread_table->list_threads->mutex[list_index]);
        
        t_thread_data *thread_data = &thread_table->list_threads->threads[list_index];
        if (thread_data->size < thread_data->space)
        {
            thread_data->data[thread_data->size] = random_number;
            // printf("--------------------------------------------------\n");
            // printf("Thread data structure at address %p\n", (void*)thread_data);
            // printf("Data array at address %p\n", (void*)thread_data->data);
            // printf("Memory address for new number: %p\n", (void*)&thread_data->data[thread_data->size]);
            // printf ("Memory address of mutex %d: %p\n", list_index, (void*)&thread_table->list_threads->mutex[list_index]);
            // printf("Memory address of thread" " args: %p\n", (void*)thread_args);
            // printf("Memory address of Seed value: %p\n", (void*)&thread_args->seed);
            // printf("[Thread [%d] Generating number %d using seed at address %p\n",
            //     thread_args->thread_id, random_number, (void*)&thread_args->seed);
            // printf("--------------------------------------------------\n");
            //  printf("Hashed Seed valu and Original Seed value:\n");
            // printf("  Original Seed: %llu\n", thread_table->seed);
            // printf("hashed seed value in thread args: %llu\n", thread_args->seed);
            // printf("Current size of list %d: %zu\n\n", list_index, thread_data->size + 1);
            // printf("Memory address of Currently Trhead Table: %p\n", (void*)thread_table);
            // printf("MEomory address of Thread[%d]: %p\n", thread_args->thread_id, (void*)&thread_table->threads[thread_args->thread_id]);
            // printf("--------------------------------------------------\n"); 
            // printf("Cycled of iteration: %d\n", i);
            thread_data->size++;
        }
        
        pthread_mutex_unlock(&thread_table->list_threads->mutex[list_index]);
        i++;
    }
    
    return (NULL);
}
