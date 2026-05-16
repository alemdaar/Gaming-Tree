#include "library.h"

/* ── Globals for terminal restoration ─────────────────────────────────────── */

static struct termios	g_orig_termios;
static int				g_termios_saved = 0;

/* ── Utility ──────────────────────────────────────────────────────────────── */

size_t	mystrlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	clear_screen(void)
{
	printf("\033[2J\033[H");
	fflush(stdout);
}

void	restore_terminal(void)
{
	if (g_termios_saved)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &g_orig_termios);
		printf("\033[?25h");
		fflush(stdout);
	}
}

static void	enable_raw_mode(void)
{
	struct termios	newt;

	tcgetattr(STDIN_FILENO, &g_orig_termios);
	g_termios_saved = 1;
	newt = g_orig_termios;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	printf("\033[?25l");
	fflush(stdout);
}

static void	handle_signal(int sig)
{
	(void)sig;
	restore_terminal();
	clear_screen();
	printf("Interrupted. Bye!\n");
	exit(0);
}

char	getch(void)
{
	char	ch;
	ssize_t	n;

	n = read(STDIN_FILENO, &ch, 1);
	if (n <= 0)
		return (0);
	return (ch);
}

/* ── Init / Free ──────────────────────────────────────────────────────────── */

static void	init_pad(t_info *info)
{
	int	i;

	info->pad = malloc(SIDE_SPACES + 1);
	if (!info->pad)
	{
		restore_terminal();
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}
	i = 0;
	while (i < SIDE_SPACES)
		info->pad[i++] = ' ';
	info->pad[i] = '\0';
}

static void	init_info(t_info *info, t_mode mode)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			info->square[i][j].data = ' ';
			info->square[i][j].selected = 0;
			j++;
		}
		i++;
	}
	info->cursor_x = 1;
	info->cursor_y = 1;
	info->square[1][1].selected = 1;
	info->turn = 'X';
	info->moves = 0;
	info->winner = 0;
	info->mode = mode;
	init_pad(info);
}

static void	free_info(t_info *info)
{
	if (info->pad)
	{
		free(info->pad);
		info->pad = NULL;
	}
}

/* ── Movement ─────────────────────────────────────────────────────────────── */

static void	move_cursor(t_info *info, int dx, int dy)
{
	int	nx;
	int	ny;

	nx = info->cursor_x + dx;
	ny = info->cursor_y + dy;
	if (nx < 0 || nx > 2 || ny < 0 || ny > 2)
		return ;
	info->square[info->cursor_y][info->cursor_x].selected = 0;
	info->cursor_x = nx;
	info->cursor_y = ny;
	info->square[ny][nx].selected = 1;
}

/* ── Win / state ──────────────────────────────────────────────────────────── */

static char	check_lines(t_info *info)
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
		a = info->square[lines[i][0][0]][lines[i][0][1]].data;
		b = info->square[lines[i][1][0]][lines[i][1][1]].data;
		c = info->square[lines[i][2][0]][lines[i][2][1]].data;
		if (a != ' ' && a == b && b == c)
			return (a);
		i++;
	}
	return (0);
}

static char	check_game_state(t_info *info)
{
	char	winner;

	winner = check_lines(info);
	if (winner != 0)
		return (winner);
	if (info->moves >= 9)
		return ('D');
	return (0);
}

/* ── Placing a move (shared between human and AI) ────────────────────────── */

int	place_at(t_info *info, int row, int col)
{
	if (info->square[row][col].data != ' ')
		return (0);
	info->square[info->cursor_y][info->cursor_x].selected = 0;
	info->cursor_x = col;
	info->cursor_y = row;
	info->square[row][col].data = info->turn;
	info->square[row][col].selected = 1;
	info->moves++;
	info->winner = check_game_state(info);
	if (info->winner == 0)
	{
		if (info->turn == 'X')
			info->turn = 'O';
		else
			info->turn = 'X';
	}
	return (1);
}

static int	place_at_cursor(t_info *info)
{
	return (place_at(info, info->cursor_y, info->cursor_x));
}

/* ── Input handling ───────────────────────────────────────────────────────── */

static int	handle_escape(t_info *info)
{
	char	second;
	char	third;

	second = getch();
	if (second != '[')
		return (-1);
	third = getch();
	if (third == 'A')
		move_cursor(info, 0, -1);
	else if (third == 'B')
		move_cursor(info, 0, 1);
	else if (third == 'C')
		move_cursor(info, 1, 0);
	else if (third == 'D')
		move_cursor(info, -1, 0);
	return (0);
}

static int	process_input(t_info *info, char c)
{
	if (c == 'q' || c == 'Q')
		return (1);
	if (c == 27)
	{
		if (handle_escape(info) == -1)
			return (1);
		return (0);
	}
	if (c == '\n' || c == ' ')
	{
		if (place_at_cursor(info))
			return (2);
	}
	return (0);
}

/* ── Status prompts ───────────────────────────────────────────────────────── */

static void	prompt_status(t_info *info)
{
	char		buf[128];
	const char	*color;

	if (info->turn == 'X')
		color = COL_RED;
	else
		color = COL_BLUE;
	if (info->mode == MODE_PVAI && info->turn == 'X')
		snprintf(buf, sizeof(buf),
			"  Your turn (X).  Arrow keys + ENTER, Q to quit.");
	else
		snprintf(buf, sizeof(buf),
			"  Player %c's turn.  Arrow keys + ENTER, Q to quit.",
			info->turn);
	print_message(info, buf, color);
}

static void	prompt_ai_thinking(t_info *info)
{
	print_message(info, "  AI is thinking... 🤖", COL_BLUE COL_BOLD);
}

/* ── End-of-round ─────────────────────────────────────────────────────────── */

static void	show_winner(t_info *info)
{
	display(info);
	if (info->winner == 'X')
	{
		if (info->mode == MODE_PVAI)
			print_message(info,
				"  🎉  You win!  🎉", COL_RED COL_BOLD);
		else
			print_message(info,
				"  🎉  Player X wins!  🎉", COL_RED COL_BOLD);
	}
	else if (info->winner == 'O')
	{
		if (info->mode == MODE_PVAI)
			print_message(info,
				"  🤖  AI wins!", COL_BLUE COL_BOLD);
		else
			print_message(info,
				"  🎉  Player O wins!  🎉", COL_BLUE COL_BOLD);
	}
	else
		print_message(info,
			"  🤝  It's a draw!", COL_YELLOW COL_BOLD);
	printf("\n");
	print_message(info, "  Press any key to continue...", COL_DIM);
	getch();
}

static int	ask_play_again(t_info *info)
{
	char	c;

	clear_screen();
	print_banner();
	print_message(info, "  Play again?  [Y/N]", COL_CYAN);
	c = getch();
	if (c == 'y' || c == 'Y' || c == '\n')
		return (1);
	return (0);
}

/* ── Game loop ────────────────────────────────────────────────────────────── */

static void	play_round(t_info *info)
{
	char	c;
	int		r;

	while (info->winner == 0)
	{
		display(info);
		if (info->mode == MODE_PVAI && info->turn == 'O')
		{
			prompt_ai_thinking(info);
			fflush(stdout);
			usleep(450000);
			ai_make_move(info);
			continue ;
		}
		prompt_status(info);
		c = getch();
		r = process_input(info, c);
		if (r == 1)
		{
			info->winner = 'Q';
			return ;
		}
	}
}

/* ── Main ─────────────────────────────────────────────────────────────────── */

int	main(void)
{
	t_info	info;
	t_mode	mode;
	char	c;

	signal(SIGINT, handle_signal);
	enable_raw_mode();
	while (1)
	{
		mode = show_menu();
		init_info(&info, mode);
		clear_screen();
		print_banner();
		print_message(&info, MSG_PRESS_KEY, COL_CYAN);
		if (mode == MODE_PVAI)
			print_message(&info,
				"  You are X (red).  AI is O (blue).  X moves first.",
				COL_DIM);
		else
			print_message(&info,
				"  Player 1 = X (red).  Player 2 = O (blue).",
				COL_DIM);
		printf("\n");
		print_message(&info, "  Press any key to start...", COL_DIM);
		c = getch();
		if (c == 'q' || c == 'Q')
		{
			free_info(&info);
			break ;
		}
		play_round(&info);
		if (info.winner == 'Q')
		{
			free_info(&info);
			break ;
		}
		show_winner(&info);
		if (!ask_play_again(&info))
		{
			free_info(&info);
			break ;
		}
		free_info(&info);
	}
	clear_screen();
	printf("\n  Thanks for playing! 👋\n\n");
	restore_terminal();
	return (0);
}
