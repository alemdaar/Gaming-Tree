#include "library.h"

/*
** AI strategy
** ────────────
**   Player is 'X' and goes first. AI is 'O'.
**
**   For each empty cell, the AI:
**     1. Places 'O' there temporarily
**     2. Enumerates ALL possible game continuations (both player and AI
**        playing every empty cell at every step)
**     3. Counts the outcomes: wins (O), draws, losses (X)
**     4. Computes a score 0–10 using:
**
**             score = (10 × wins + 5 × draws) / total
**
**        Range:
**           wins = total  → 10  (always win)
**           draws = total →  5  (always draw)
**           losses = total →  0  (always lose)
**
**   Then the AI picks the cell with the highest score.
**
**   Two fast paths run before the full simulation:
**     • If O can win this turn, do it.
**     • If X can win next turn, block them.
**
**   Performance:
**     The game tree of tic-tac-toe is small (≤ 9! = 362,880 leaves), and
**     each scoring call explores far less than that since wins prune early.
**     The AI's first response (8 empty cells) takes about 1–10 ms.
*/

static char	check_winner_board(char board[3][3])
{
	static const int	lines[8][3][2] = {
	{{0, 0}, {0, 1}, {0, 2}}, {{1, 0}, {1, 1}, {1, 2}}, {{2, 0}, {2, 1}, {2, 2}},
	{{0, 0}, {1, 0}, {2, 0}}, {{0, 1}, {1, 1}, {2, 1}}, {{0, 2}, {1, 2}, {2, 2}},
	{{0, 0}, {1, 1}, {2, 2}}, {{0, 2}, {1, 1}, {2, 0}}
	};
	int		i;
	char	a;
	char	b;
	char	c;

	i = 0;
	while (i < 8)
	{
		a = board[lines[i][0][0]][lines[i][0][1]];
		b = board[lines[i][1][0]][lines[i][1][1]];
		c = board[lines[i][2][0]][lines[i][2][1]];
		if (a != ' ' && a == b && b == c)
			return (a);
		i++;
	}
	return (0);
}

/*
** Recursively explore all possible continuations from the current board.
** Each terminal state (someone won, or no cells left) increments stats.
*/
static void	simulate(char board[3][3], char turn, t_stats *stats)
{
	char	w;
	int		i;
	int		j;
	char	next_turn;
	int		any_empty;

	w = check_winner_board(board);
	if (w == 'O')
	{
		stats->wins++;
		stats->total++;
		return ;
	}
	if (w == 'X')
	{
		stats->losses++;
		stats->total++;
		return ;
	}
	any_empty = 0;
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (board[i][j] == ' ')
				any_empty = 1;
			j++;
		}
		i++;
	}
	if (!any_empty)
	{
		stats->draws++;
		stats->total++;
		return ;
	}
	if (turn == 'X')
		next_turn = 'O';
	else
		next_turn = 'X';
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = turn;
				simulate(board, next_turn, stats);
				board[i][j] = ' ';
			}
			j++;
		}
		i++;
	}
}

/*
** Compute the 0–10 score for placing 'O' at (row, col).
*/
static double	score_move(char board[3][3], int row, int col)
{
	t_stats	stats;

	stats.wins = 0;
	stats.draws = 0;
	stats.losses = 0;
	stats.total = 0;
	board[row][col] = 'O';
	simulate(board, 'X', &stats);
	board[row][col] = ' ';
	if (stats.total == 0)
		return (0.0);
	return ((10.0 * stats.wins + 5.0 * stats.draws) / stats.total);
}

/*
** Check if `player` can win by placing on some empty cell. If yes, fills
** *row and *col and returns 1. Otherwise returns 0.
*/
static int	find_immediate_win(char board[3][3], char player,
								int *row, int *col)
{
	int		i;
	int		j;
	char	w;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = player;
				w = check_winner_board(board);
				board[i][j] = ' ';
				if (w == player)
				{
					*row = i;
					*col = j;
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

/*
** Pick the best (row, col) for the AI's next move.
*/
static void	pick_best_move(char board[3][3], int *row, int *col)
{
	double	best_score;
	double	s;
	int		i;
	int		j;

	if (find_immediate_win(board, 'O', row, col))
		return ;
	if (find_immediate_win(board, 'X', row, col))
		return ;
	best_score = -1.0;
	*row = -1;
	*col = -1;
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (board[i][j] == ' ')
			{
				s = score_move(board, i, j);
				if (s > best_score)
				{
					best_score = s;
					*row = i;
					*col = j;
				}
			}
			j++;
		}
		i++;
	}
}

/*
** Public entry point: compute the AI's best move and place it.
*/
void	ai_make_move(t_info *info)
{
	char	board[3][3];
	int		i;
	int		j;
	int		row;
	int		col;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			board[i][j] = info->square[i][j].data;
			j++;
		}
		i++;
	}
	pick_best_move(board, &row, &col);
	if (row >= 0 && col >= 0)
		place_at(info, row, col);
}
