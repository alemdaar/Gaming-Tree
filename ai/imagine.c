#include "library.h"

// void init_imagine(t_ai *ai, t_info *info)
// {
//     // 
// }
w
int vertical_finish(t_info *info, t_ai *ai, int fight)
{
    t_cord last;
    int i = 0;
    int filled = 0;
    int empty = 0;
    while (i < 3)
    {
        if (info->square[i][0].data == 'O')
            filled += 1;
        else if (info->square[i][0].data == ' ')
        {
            last.x = 0;
            last.y = i;
            empty += 1;
        }
        if (info->square[i][1].data == 'O')
            filled += 1;
        else if (info->square[i][1].data == ' ')
        {
            last.x = 0;
            last.y = i;
            empty += 1;
        }
        if (info->square[i][2].data == 'O')
            filled += 1;
        else if (info->square[i][2].data == ' ')
        {
            last.x = 0;
            last.y = i;
            empty += 1;
        }
        if (filled == 2 && empty == 1)
        {
            if (fight == ATTACK)
            {
                ai->finish_him.x = last.x;
                ai->finish_him.y = last.y;
            }
            else if (fight == DEFENSE)
            {
                ai->defense.x = last.x;
                ai->defense.y = last.y;
            }
            return (FINISH_VER);
        }
        filled = 0;
        empty = 0;
        i++;
    }
    return (0);
}

int horizontal_finish(t_info *info, t_ai *ai, int fight)
{
    t_cord last;
    int i = 0;
    int filled = 0;
    int empty = 0;
    while (i < 3)
    {
        if (info->square[0][i].data == 'O')
            filled += 1;
        else if (info->square[0][i].data == ' ')
        {
            last.x = 0;
            last.y = i;
            empty += 1;
        }
        if (info->square[1][i].data == 'O')
            filled += 1;
        else if (info->square[1][i].data == ' ')
        {
            last.x = 0;
            last.y = i;
            empty += 1;
        }
        if (info->square[2][i].data == 'O')
            filled += 1;
        else if (info->square[2][i].data == ' ')
        {
            last.x = 0;
            last.y = i;
            empty += 1;
        }
        if (filled == 2 && empty == 1)
        {
            if (fight == ATTACK)
            {
                ai->finish_him.x = last.x;
                ai->finish_him.y = last.y;
            }
            else if (fight == DEFENSE)
            {
                ai->defense.x = last.x;
                ai->defense.y = last.y;
            }
            return (FINISH_HOR);
        }
        filled = 0;
        empty = 0;
        i++;
    }
    return (0);
}

int xrd_finish(t_info *info, t_ai *ai, int fight)
{
    t_cord last;
    int filled = 0;
    int empty = 0;

    if (info->square[0][0].data == 'O')
        filled += 1;
    else if (info->square[0][0].data == ' ')
    {
        last.x = 0;
        last.y = 0;
        empty += 1;
    }
    if (info->square[1][2].data == 'O')
        filled += 1;
    else if (info->square[1][2].data == ' ')
    {
        last.x = 0;
        last.y = 1;
        empty += 1;
    }
    if (info->square[2][2].data == 'O')
        filled += 1;
    else if (info->square[2][2].data == ' ')
    {
        last.x = 0;
        last.y = 2;
        empty += 1;
    }
    if (filled == 2 && empty == 1)
    {
        if (fight == ATTACK)
        {
            ai->finish_him.x = last.x;
            ai->finish_him.y = last.y;
        }
        else if (fight == DEFENSE)
        {
            ai->defense.x = last.x;
            ai->defense.y = last.y;
        }
        return (FINISH_XRD);
    }
    filled = 0;
    empty = 0;
    return (0);
}

int xru_finish(t_info *info, t_ai *ai, int fight)
{
    t_cord last;
    int filled = 0;
    int empty = 0;

    if (info->square[2][0].data == 'O')
        filled += 1;
    else if (info->square[2][0].data == ' ')
    {
        last.x = 0;
        last.y = 0;
        empty += 1;
    }
    if (info->square[1][2].data == 'O')
        filled += 1;
    else if (info->square[1][2].data == ' ')
    {
        last.x = 0;
        last.y = 1;
        empty += 1;
    }
    if (info->square[0][2].data == 'O')
        filled += 1;
    else if (info->square[0][2].data == ' ')
    {
        last.x = 0;
        last.y = 2;
        empty += 1;
    }
    if (filled == 2 && empty == 1)
    {
        if (fight == ATTACK)
        {
            ai->finish_him.x = last.x;
            ai->finish_him.y = last.y;
        }
        else if (fight == DEFENSE)
        {
            ai->defense.x = last.x;
            ai->defense.y = last.y;
        }
        return (FINISH_XRU);
    }
    filled = 0;
    empty = 0;
    return (0);
}

int check_win(t_info *info, t_ai *ai)
{
    if (vertical_finish(info, ai, ATTACK) == FINISH_VER)
        return (SUCCESS);
    if (horizontal_finish(info, ai, ATTACK) == FINISH_HOR)
        return (SUCCESS);
    if (xrd_finish(info, ai, ATTACK) == FINISH_XRD)
        return (SUCCESS);
    if (xru_finish(info, ai, ATTACK) == FINISH_VER)
        return (SUCCESS);
    return (FAILED);
}

int check_defense(t_info *info, t_ai *ai)
{
    if (vertical_finish(info, ai, DEFENSE) == FINISH_VER)
        return (SUCCESS);
    if (horizontal_finish(info, ai, DEFENSE) == FINISH_HOR)
        return (SUCCESS);
    if (xrd_finish(info, ai, DEFENSE) == FINISH_XRD)
        return (SUCCESS);
    if (xru_finish(info, ai, DEFENSE) == FINISH_VER)
        return (SUCCESS);
    return (FAILED);
}

// random_move

t_cord next_place_in_order(t_info *info)
{
    t_cord index;
    int i = 0;
    while (i < LEN_SQUARES)
    {
        int j = 0;
        while (j < LEN_SQUARES)
        {
            if (info->square[i][j].data == ' ') {
                index.y = i;
                index.x = j;
                return (index);
            }
            j++;
        }
        i++;
    }
    index.y = -1;
    index.x = -1;
    return (index);
}

void expectaions(t_cord index, t_info *info, t_ai *ai, int size)
{
    if (size == 0)
        return;
    if (info->reached_3_hits >= 2)
    {
        if (check_win(info, ai) == SUCCESS)
            return ;
        if (check_defense(info, ai) == SUCCESS)
            return ;
    }
    t_cord index = next_place_in_order(info->tmp_square);
    expectaions(index, info, ai, size - 1);
    return ;
}

int imagine(t_info *info, t_ai *ai)
{
    // init_imagine(ai, info);
    int i = 0;
    while (i < 2)
    {
        int j = 0;
        while (j < 2)
        {
            info->tmp_square[i][j].data = info->square[i][j].data;
            j++;
        }
        i++;
    }
    ai->prev.x = 0;
    ai->prev.y = 0;
    int i = 0;
    while (i < ai->size)
    {
        t_cord index = next_place_in_ordernext(info->square);
        expectaions(index, info, ai, ai->size);
        i++;
    }
    decide_nextmove(info, ai);
    best_move(info, ai);
}
