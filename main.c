#include "library.h"

size_t mystrlen(char *str)
{
    size_t i = 0;
    while (str[i])
        i++;
    return (i);
}

void clear_screen(void)
{
    system ("clear");
    return ;
}

char getch() {
    struct termios oldt, newt;
    char ch;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    read(STDIN_FILENO, &ch, 1);
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int display(t_info *info)
{
    clear_screen();
    printf ("\n\n\n\n\n\n\n\n\n");
    printf ("%s||===============||===============||===============||%s\n", info->centerlized_spaces, info->centerlized_spaces);
    int i = 0;
    while (i < LEN_SQUARES)
    {
        printf ("%s||               ||               ||               ||%s\n", info->centerlized_spaces, info->centerlized_spaces);
        // //   
        printf ("%s||   %c%c%c%c%c%c%c%c%c   ||   %c%c%c%c%c%c%c%c%c   ||   %c%c%c%c%c%c%c%c%c   ||%s\n", info->centerlized_spaces, 
                                                                                                          info->square[i][0].here, info->square[i][0].here, info->square[i][0].here, 
                                                                                                          info->square[i][0].here, info->square[i][0].here, info->square[i][0].here, 
                                                                                                          info->square[i][0].here, info->square[i][0].here, info->square[i][0].here, 
                                                                                                          info->square[i][1].here, info->square[i][1].here, info->square[i][1].here, 
                                                                                                          info->square[i][1].here, info->square[i][1].here, info->square[i][1].here, 
                                                                                                          info->square[i][1].here, info->square[i][1].here, info->square[i][1].here, 
                                                                                                          info->square[i][2].here, info->square[i][2].here, info->square[i][2].here, 
                                                                                                          info->square[i][2].here, info->square[i][2].here, info->square[i][2].here, 
                                                                                                          info->square[i][2].here, info->square[i][2].here, info->square[i][2].here, 
                                                                                                          info->centerlized_spaces);
        // //   
        printf ("%s||   %c       %c   ||   %c       %c   ||   %c       %c   ||%s\n", info->centerlized_spaces, 
                                                                                     info->square[i][0].here, info->square[i][0].here,
                                                                                     info->square[i][1].here, info->square[i][1].here,
                                                                                     info->square[i][2].here, info->square[i][2].here,
                                                                                     info->centerlized_spaces);
        // //   
        printf ("%s||   %c   %c   %c   ||   %c   %c   %c   ||   %c   %c   %c   ||%s\n",  info->centerlized_spaces,
                                                                                         info->square[i][0].here, info->square[i][0].data, info->square[i][0].here, 
                                                                                         info->square[i][1].here, info->square[i][1].data, info->square[i][1].here, 
                                                                                         info->square[i][2].here, info->square[i][2].data, info->square[i][2].here,
                                                                                         info->centerlized_spaces);
        // //   
        printf ("%s||   %c       %c   ||   %c       %c   ||   %c       %c   ||%s\n", info->centerlized_spaces, 
                                                                                     info->square[i][0].here, info->square[i][0].here,
                                                                                     info->square[i][1].here, info->square[i][1].here,
                                                                                     info->square[i][2].here, info->square[i][2].here,
                                                                                     info->centerlized_spaces);
        // //   
        printf ("%s||   %c%c%c%c%c%c%c%c%c   ||   %c%c%c%c%c%c%c%c%c   ||   %c%c%c%c%c%c%c%c%c   ||%s\n", info->centerlized_spaces, 
                                                                                                          info->square[i][0].here, info->square[i][0].here, info->square[i][0].here, 
                                                                                                          info->square[i][0].here, info->square[i][0].here, info->square[i][0].here, 
                                                                                                          info->square[i][0].here, info->square[i][0].here, info->square[i][0].here, 
                                                                                                          info->square[i][1].here, info->square[i][1].here, info->square[i][1].here, 
                                                                                                          info->square[i][1].here, info->square[i][1].here, info->square[i][1].here, 
                                                                                                          info->square[i][1].here, info->square[i][1].here, info->square[i][1].here, 
                                                                                                          info->square[i][2].here, info->square[i][2].here, info->square[i][2].here, 
                                                                                                          info->square[i][2].here, info->square[i][2].here, info->square[i][2].here, 
                                                                                                          info->square[i][2].here, info->square[i][2].here, info->square[i][2].here, 
                                                                                                          info->centerlized_spaces);
        // //   
        printf ("%s||               ||               ||               ||%s\n", info->centerlized_spaces, info->centerlized_spaces);
        //  // //
        printf ("%s||===============||===============||===============||%s\n", info->centerlized_spaces, info->centerlized_spaces);
        i++;
    }
    return 0;
}

void init_select(t_info *info)
{
    // this one will let the select starts in the middle -> line 1 and line 1
    info->select_position_x = 1;
    info->select_position_y = 1;
    info->square[info->select_position_y][info->select_position_x].here = '*';
}

void free_heap(t_info *info)
{
    if (info->centerlized_spaces == NULL) // because if it equals null it means either we didnt initialize it yet or it returned an error
    {
        free (info->centerlized_spaces); // we free it, means that memory space/place isnt taken anymore and available to use , but the data still there, means if we allocated again and malloc gave us this address, we will realize that the data hold in each byte still the same
        info->centerlized_spaces = NULL; /*now I set the variable to null for several reasons :
                                             -> the variable now points on no address
                                             -> if I tried to free the variable again i will know that this variable doesnt have any address in its value, so it means eitehr just initialized or already freed
                                            */
    }
}
void handle_error(t_info *info, const char *err_msg)
{
    char nls[] = "\n\n\n\n\n";
    int i;

    clear_screen();
    write (2, &err_msg[i], 1);
    i = 0;
    while (i < mystrlen(info->centerlized_spaces))
        write (2, &err_msg[i], 1);
    free_heap(info);
    exit (-1);
}

void init_centerlized_spaces(t_info *info)
{
    info->centerlized_spaces = malloc (SIDE_SPACES + NULL_TERM_PLACE);
    if (info->centerlized_spaces == NULL)
        handle_error(info, ERR_MSG_MALLOC);
    int i = 0;
    while (i < 58)
        info->centerlized_spaces[i++] = ' ';
    info->centerlized_spaces[i] = 0;
}
int init_info(t_info *info)
{
    t_data *tmp;

    // now we will considere everything as an empty box and set everything to space
    int i = 0;
    while (i < 3)
    {
        int j = 0;
        while (j < 3)
        {
            info->square[i][j].data = ' '; // im setting all data to space, so it means the board is empty from x and o
            info->square[i][j].here = ' '; // im setting the select to space so it means theres no select yet
            j++;
        }

        i++;
    }
    info->turn = 'X'; // making sure that the player that has first turn is 'X'
    info->reached_3_hits = 0; // making sure that the variable that sees if the first player reached 3 hits, so i can start checking the winning algo
    init_select(info); // init the the select with '*'s
    init_centerlized_spaces(info); // init spaces that will make the game in center
    return 0;
}

int move_select(t_info *info, int x, int y)
{
    if (info->select_position_x + x > 2 || info->select_position_x + x < 0)
        return (1);
    if (info->select_position_y + y > 2 || info->select_position_y + y < 0)
        return (1);
    info->square[info->select_position_y][info->select_position_x].here = ' ';
    info->select_position_x += x;
    info->select_position_y += y;
    info->square[info->select_position_y][info->select_position_x].here = '*';
    return (0);
}

int remove_select(t_info *info)
{
    info->square[info->select_position_y][info->select_position_y].here = 32;
    return (0);
}

void someone_won(t_info *info)
{
    clear_screen();
    printf ("\n\n\n\n\n\n\n\n\n\n\n%splayer '%c' WON !!!!!\n", info->centerlized_spaces, info->turn);
}

void vertical_check(t_info *info, int x, int y)
{
    int tmp = 0;
    int i;

    if (y - 1 >= 0) // check if he is out of the square
    {
        // 79 is O in ascii || 88 is X in ascii 
        if (info->square[y - 1][x].data == info->turn)
        {
            if (y == 2)
            {
                if (info->square[y - 2][x].data == info->turn)
                {
                    remove_select (info);
                    display(info);
                    tmp = 0;
                    printf ("player '%c' WON !!!!!\n", info->turn);
                    // someone_won(info);
                    exit(0);
                }
            }
            else
            {
                if (info->square[y + 1][x].data == info->turn)
                {
                    remove_select (info);
                    display(info);    
                    tmp = 0;
                    printf ("player '%c' WON !!!!!\n", info->turn);
                    // someone_won(info);
                    exit(0);
                }
            }
        }
    }
    else
    {
        i = 1;
        while (i <= 2)
        {
            if (x >= 0 && x < 3 && y >= 0 && y < 3)
            {
                if (info->square[y + i][x].data != info->turn)
                {
                    break;
                }
            }
            else
                return;
            i++;
        }
        if (i == 3)
        {
            remove_select (info);
            display(info);    
            tmp = 0;
            printf ("player '%c' WON !!!!!\n", info->turn);
            // someone_won(info);
            exit(0);
        }
    }
}

void horizontal_check(t_info *info, int x, int y)
{
    int tmp = 0;
    int i;
    // x ->
    if (x - 1 >= 0) // check if he is out of the square
    {
        // 79  O || 88  X
        if (info->square[y][x - 1].data == info->turn)
        {
            if (x == 2)
            {
                if (info->square[y][x - 2].data == info->turn)
                {
                    remove_select (info);
                    display(info);    
                    tmp = 0;
                    printf ("player '%c' WON !!!!!\n", info->turn);
                    // someone_won(info);
                    exit(0);
                }
            }
            else
            {
                if (info->square[y][x + 1].data == info->turn)
                {
                    remove_select (info);
                    display(info);    
                    tmp = 0;
                    printf ("player '%c' WON !!!!!\n", info->turn);
                    // someone_won(info);
                    exit(0);
                }
            }
        }
    }
    else
    {
        i = 1;
        while (i <= 2)
        {
            if (x >= 0 && x < 3 && y >= 0 && y < 3)
            {
                if (info->square[y][x + i].data != info->turn)
                {
                    break;
                }
            }
            else
                return;
            i++;
        }
        if (i == 3)
        {
            remove_select (info);
            display(info);    
            tmp = 0;
            printf ("player '%c' WON !!!!!\n", info->turn);
            // someone_won(info);
            exit(0);
        }
    }
}
void xypp_check(t_info *info, int x, int y)
{
    int tmp = 0;
    int i = 0;

    if (x - 1 >= 0 && y - 1 >= 0) // check if he is out of the square
    {
        // 79  O || 88  X
        if (info->square[y - 1][x - 1].data == info->turn)
        {
            if (x == 2 && y == 2)
            {
                if (info->square[y - 2][x - 2].data == info->turn)
                {
                    remove_select (info);
                    display(info);    
                    tmp = 0;
                    printf ("player '%c' WON !!!!!\n", info->turn);
                    // someone_won(info);
                    exit(0);
                }
            }
            else if (x == 1 && y == 1)
            {
                if (info->square[y + 2][x + 1].data == info->turn)
                {
                    remove_select (info);
                    display(info);    
                    tmp = 0;
                    printf ("player '%c' WON !!!!!\n", info->turn);
                    // someone_won(info);
                    exit(0);
                }
            }
        }
    }
    else
    {
        i = 1;
        while (i <= 2)
        {
            if (x >= 0 && x < 3 && y >= 0 && y < 3)
            {
                if (info->square[y + i][x + i].data != info->turn)
                {
                    break;
                }
            }
            else
                return;
            i++;
        }
        if (i == 3)
        {
            remove_select (info);
            display(info);    
            tmp = 0;
            printf ("player '%c' WON !!!!!\n", info->turn);
            // someone_won(info);
            exit(0);
        }
    }
}

void xyop_check(t_info *info, int x, int y)
{
    int tmp = 0;
    int i = 0;

    if (x - 1 >= 0 && y + 1 >= 0) // check if he is out of the square
    {
        // 79  O || 88  X
        if (info->square[y + 1][x - 1].data == info->turn)
        {
            if (x == 2 && y == 0)
            {
                if (info->square[y + 2][x - 2].data == info->turn)
                {
                    remove_select (info);
                    display(info);    
                    tmp = 0;
                    printf ("player '%c' WON !!!!!\n", info->turn);
                    // someone_won(info);
                    exit(0);
                }
            }
            else if (x == 1 && y == 1)
            {
                if (info->square[y - 1][x + 1].data == info->turn)
                {
                    remove_select (info);
                    display(info);    
                    tmp = 0;
                    printf ("player '%c' WON !!!!!\n", info->turn);
                    // someone_won(info);
                    exit(0);
                }
            }
        }
    }
    else
    {
        i = 1;
        while (i <= 2)
        {
            if (x >= 0 && x < 3 && y >= 0 && y < 3)
            {
                if (info->square[y - i][x + i].data != info->turn)
                {
                    break;
                }
            }
            else
                return;
            i++;
        }
        if (i == 3)
        {
            remove_select (info);
            display(info);    
            tmp = 0;
            printf ("player '%c' WON !!!!!\n", info->turn);
            // someone_won(info);
            exit(0);
        }
    }
}

int winning_algo(t_info *info)
{
    int check = 1;
    int angle = 1;
    int x = info->select_position_x;
    int y = info->select_position_y;

    vertical_check(info, x, y);
    horizontal_check(info, x, y);
    xypp_check(info, x, y);
    xyop_check(info, x, y);

    
    return (0);
}

void end_game(t_info *info)
{
    remove_select(info);
    display(info);
    printf ("the game ended and nobody won !\n");
    exit (22);
}

int hit_enter(t_info *info, t_ai *ai)
{
    if (info->square[info->select_position_y][info->select_position_x].data != ' ')
        return (DIDNT_HIT_3);
    info->square[info->select_position_y][info->select_position_x].data = info->turn;
    info->reached_3_hits ++;
    if (info->reached_3_hits == 5)
        end_game(info);
    info->turn = 'X' + 'O' - info->turn;
    nextmove(info, ai);
    if (info->reached_3_hits >= 3)
        winning_algo (info);
    return (0);
}

void pop_up(const char *msg, t_info *info)
{
    int i = 0;
    while (i < mystrlen((char *)msg))
        write (1, &msg[i++], 1);
    return ;
}
int main() {
    t_info info;
    t_ai ai;
    char c;

    init_info(&info);
    clear_screen();
    pop_up(MSG_PRESS_KEY, &info);
    getch();
    while (1) {
        display(&info);    
        c = getch();
        if (c == 27)
        {
            char second = getch();
            char third = getch();

            if (second == '[') {
                if (third == 'A')
                {
                    printf("Up arrow pressed\n\n\n");
                    move_select(&info, 0, -1);
                }
                else if (third == 'B')
                {
                    move_select(&info, 0, 1);
                    printf("Down arrow pressed\n\n\n");
                }
                else if (third == 'C')
                {
                    printf("Right arrow pressed\n\n\n");
                    move_select(&info, 1, 0);
                }
                else if (third == 'D')
                {
                    printf("Left arrow pressed\n\n\n");
                    move_select(&info, -1, 0);
                }
                else
                {
                    printf("Unknown escape sequence\n\n\n\n");
                }
            }
            else
            {
                printf ("exit in else!\n");
                exit(0);
            }
        }
        else if (c == '\n')
            hit_enter(&info, &ai);
    }
    return 0;
}
