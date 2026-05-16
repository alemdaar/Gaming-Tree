#ifndef LIBRARY_H
# define LIBRARY_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <string.h>
# include <signal.h>

# define LEN_SQUARES   3
# define SIDE_SPACES   58

/* ANSI colors */
# define COL_RED       "\033[1;31m"
# define COL_BLUE      "\033[1;34m"
# define COL_YELLOW    "\033[1;33m"
# define COL_GREEN     "\033[1;32m"
# define COL_CYAN      "\033[1;36m"
# define COL_MAGENTA   "\033[1;35m"
# define COL_DIM       "\033[2;37m"
# define COL_BOLD      "\033[1m"
# define COL_RESET     "\033[0m"

# define MSG_PRESS_KEY "Use arrow keys to move, ENTER to place, Q to quit."

typedef enum e_mode
{
	MODE_PVP,
	MODE_PVAI
}	t_mode;

typedef struct s_cell
{
	char	data;       /* ' ', 'X', or 'O' */
	int		selected;
}	t_cell;

typedef struct s_info
{
	t_cell	square[3][3];
	int		cursor_x;
	int		cursor_y;
	char	turn;
	int		moves;
	int		winner;     /* 0 = ongoing, 'X', 'O', 'D' = draw, 'Q' = quit */
	char	*pad;
	t_mode	mode;
}	t_info;

/* For AI simulation: counts of game outcomes from a hypothetical move. */
typedef struct s_stats
{
	int	wins;       /* O (AI) wins */
	int	draws;
	int	losses;     /* X (player) wins */
	int	total;
}	t_stats;

/* design.c */
void	display(t_info *info);
void	print_banner(void);
void	print_message(t_info *info, const char *msg, const char *color);
t_mode	show_menu(void);

/* main.c */
size_t	mystrlen(const char *str);
void	clear_screen(void);
char	getch(void);
void	restore_terminal(void);
int		place_at(t_info *info, int row, int col);

/* ai.c */
void	ai_make_move(t_info *info);

#endif
