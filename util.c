#include <stdio.h>

int get_length(int val)
{
    int len = 0;
    while(val != 0)
    {
        if(val > 9) len++;
        val = val/10;
    }
    
    return len;
}

int get_int(char *str)
{
    int result = 0;
    int puiss = 1;

    while (('-' == (*str)) || ((*str) == '+'))
    {
        if (*str == '-')
        {
            puiss = puiss * -1;
        }
        str++;
    }
    
    while ((*str >= '0') && (*str <= '9'))
    {
        result = (result * 10) + ((*str) - '0');
        str++;
    }
    return (result * puiss);
}
