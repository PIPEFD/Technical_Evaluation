#include "threads.h"




int verify_results(t_threads_table *thread_table)
{
    size_t expected_total;
    size_t actual_total;

    if (thread_table)
    {
        expected_total = (size_t)(thread_table->nbr_threads) * (size_t)(thread_table->nbr_per_thread);
        actual_total = thread_table->list_threads->threads[LIST_POSITIVE].size + thread_table->list_threads->threads[LIST_NEGATIVE].size;
        
        if (expected_total == actual_total)
            return (0);
        else
            return (1);
    }
    return (1);
}


int verify_sorted_list(int *data, size_t size)
{
    size_t j;
    
    if (!data || size == 0)
        return (0);
    
    j = 0;
    while (j < size - 1)
    {
        if (data[j] > data[j + 1])
        {
            // printf("Not sorted correctly!\n", list_name);
            // printf("Position %zu: %d > Position %zu: %d\n", j, data[j], j + 1, data[j + 1]);
            return (1);
        }
        j++;
    }
    // printf("%s is sorted correctly (%zu elements)\n", list_name, size);
    return (0);
}



int compare_lists(const void *a, const void *b)
{
    int *int_a = (int *)a;
    int *int_b = (int *)b;
    if (int_a && int_b)
    {
        if (*int_a < *int_b)
            return (-1);
        else if (*int_a > *int_b)
            return (1);
        
    }
    else
        return (0);
    
    return (0);
}



unsigned long long aletory_number_with_rng(unsigned long long *nbr)
{
    unsigned long long a = 6364136223846793005ULL;
    unsigned long long c = 1442695040888963407ULL;

    if (nbr)
    {
        *nbr = a * (*nbr) + c;
        return (*nbr);
    }
    return (0);
}


int parse(const char *str, int *nbr)
{
    char    *endptr;
    long    val;

    if(!str || !nbr || *str == '\0' || *str == ' ')
        return (1);
    
    if(*str == '+')
    {
        if(*(str + 1) == '\0')
            return (1);
        str++;
    }
    val = strtol(str, &endptr, 10);
    if (*endptr == '\0' && val >= MIN_PER_THREAD && val <= MAX_PER_THREAD && val >= INT_MIN && val <= INT_MAX)
    {
        *nbr = (int)val;
        return (0);
    }
    return (1);
}