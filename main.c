
#include <unistd.h>
#include <stdio.h>

#include <stdlib.h>
#include <limits.h>


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
    if(*endptr == '\0' && val >= 0 && val <= INT_MAX)
    {
        *nbr = (int)val;
        return (0);
    }
    return (1);
}

int main (int argc, char **argv)
{

    int     nbr_threads;
    int     nbr_per_thread;

    if (argc != 3)
        return(write(2, "Usage: ./program <nbr_threads> <nbr_per_thread>\n", 48), 1);
    if (parse(argv[1], &nbr_threads) != 0 || parse(argv[2], &nbr_per_thread) != 0)
        return(write(2, "Error: Invalid arguments\n", 25), 1);
    printf("Number of threads: %d\n", nbr_threads);
    printf("Number per thread: %d\n", nbr_per_thread);
    return(0);
}