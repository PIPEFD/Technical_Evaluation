#include "threads.h"

int sort_threads_lists(t_threads_table *thread_table)
{
    int i;
    const char *list_name;

    if (thread_table ||  thread_table->list_threads)
   {
        i = 0;
        while (i < LIST_SIZE)
        {
            if (i == LIST_POSITIVE)
                list_name = "Positive Numbers List";
            else
                list_name = "Negative Numbers List";
            if (thread_table->list_threads->threads[i].size > 0  \
                && thread_table->list_threads->threads[i].data != NULL)
            {                
                qsort(thread_table->list_threads->threads[i].data, thread_table->list_threads->threads[i].size, sizeof(int), compare_lists);
            }
            else 
            {
                printf("\n%s is empty\n", list_name);
            }

            i++;
        }
   } 
   

    return (0);
}
