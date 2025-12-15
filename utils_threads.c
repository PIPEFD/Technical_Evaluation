#include "threads.h"



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