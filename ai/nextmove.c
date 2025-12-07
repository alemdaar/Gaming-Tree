#include "library.h"

int possible_size(t_ai *ai, t_info *info)
{
    // 
    ai->size = 0;
    int i = 0;
    while (i < 2)
    {
        int j = 0;
        while (j < 2)
        {
            if (info->square[i][j].data != ' ')
                ai->size ++;
            j++;
        }
        i++;
    }
    return (0);
}
void init_nextmove(t_ai *ai, t_info *info)
{
    // 
    possible_size(ai, info);
    // init_index(ai, info);
}

int nextmove(t_info * info, t_ai *ai)
{
    init_nextmove(ai, info);
    if (info->reached_3_hits >= 2)
    {
        if (check_win(info, ai) == SUCCESS)
            return ;
        if (check_defense(info, ai) == SUCCESS)
            return ;
    }
    imagine(info, ai);
}