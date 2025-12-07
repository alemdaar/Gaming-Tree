#ifndef LIBRARY_H
#define LIBRARY_H


// include libraries
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>

// define numbers
#define LAST_POSSIB_STRC -44
#define ERROR -1
#define FALSE 0
#define SUCCESS 0
#define TRUE 1
#define FAILED 1
#define LEN_SQUARES 3
#define FINISH_VER 5
#define FINISH_HOR 6
#define FINISH_XRD 7
#define FINISH_XRU 8
#define ATTACK 9
#define DEFENSE 10
#define DIDNT_HIT_3 33
#define SIDE_SPACES 58
#define NULL_TERM_PLACE 58



// define strings
#define MSG_PRESS_KEY "Press any key (arrow keys or q to quit):\n\n\n"
#define ERR_MSG_MALLOC "allocation failed when using malloc\n"



// structs
typedef struct s_data
{
    int here;
    char data;
}   t_data;

typedef struct s_info
{
    t_data square[3][3];
    t_data tmp_square[3][3];
    char *centerlized_spaces;
    int select_position_x;
    int select_position_y;
    char turn;
    int reached_3_hits;
}   t_info;

typedef struct s_stats
{
    int count;
    int success;
    int draw;
    int lose;
}   t_stats;

typedef struct s_cord
{
    int x;
    int y;
}   t_cord;

typedef struct s_possibilities
{
    int level;
    t_cord cord;
    t_stats stats;
    // t_cord buffer[5040];
    struct s_possibilities** buffer;
    int index;
}   t_possibilities;

typedef struct s_ai
{
    struct s_ai fake_ai;
    t_possibilities possib[8]; // the next 8 possible ways that I have agains that first move
    t_cord first_move; // this is the first move that the user will move
    t_cord finish_him; //the variable that contains xo of the next move to win the game
    t_cord defense; //the variable that contains xo of the next move to defense
    t_cord prev; //the variable that contains xo of the next move to defense
    t_data square[3][3];
    int size;
}   t_ai;



// prototype 
int display();
int nextmove(t_info * info, t_ai *ai);


#endif



//    |   |   
// ---|---|---
//    | X |   
// ---|---|---
//    |   |   