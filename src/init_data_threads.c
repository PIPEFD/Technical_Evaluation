#include "../inc/threads.h"    



unsigned long long init_thread_aletory_rng_seed(t_threads_table *thread_table, void *thread_ptr, int thread_id)
{
    unsigned long long seed_value;
    
    if (thread_table && thread_ptr)
    {
        seed_value = (*thread_table).seed ^ (unsigned long long)thread_id;  
        seed_value ^= (unsigned long long)(thread_ptr);  
        seed_value = set_hash_mix(seed_value);    
        return (seed_value);
    }
    return (0x123456789abcdefULL);
}




unsigned long long init_thread_with_aleatory_rng(unsigned long long *nbr)
{

    unsigned long long value;
    int result;

    if (nbr)
    {
        value = aletory_number_with_rng(nbr);
        result = (int)((value >> 42) & 0x7FFFFFFF);
        if (value & 0x1)
            result = -result;
        return (result);
    }
    return (0);
}

