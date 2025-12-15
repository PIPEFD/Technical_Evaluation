#include "threads.h"

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