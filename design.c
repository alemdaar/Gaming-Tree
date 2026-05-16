#include "library.h"

/*
** Each cell is 5 content rows tall and 15 cols wide.
** Patterns below fill that area to make big X / O / cursor shapes.
*/

static const char	*g_pattern_x[5] = {
	"  X         X  ",
	"    X     X    ",
	"       X       ",
	"    X     X    ",
	"  X         X  ",
};

static const char	*g_pattern_o[5] = {
	"     O O O     ",
	"   O       O   ",
	"   O       O   ",
	"   O       O   ",
	"     O O O     ",
};

static const char	*g_pattern_cursor[5] = {
	"  * * * * * *  ",
	"  *         *  ",
	"  *         *  ",
	"  *         *  ",
	"  * * * * * *  ",
};

static const char	*g_pattern_empty[5] = {
	"               ",
	"               ",
	"               ",
	"               ",
	"               ",
};

static void	print_cell_line(t_cell *cell, int line, char turn)
{
	const char	*content;
	const char	*color;

	color = COL_RESET;
	if (cell->data == 'X')
	{
		content = g_pattern_x[line];
		color = COL_RED;
	}
	else if (cell->data == 'O')
	{
		content = g_pattern_o[line];
		color = COL_BLUE;
	}
	else if (cell->selected)
	{
		content = g_pattern_cursor[line];
		if (turn == 'X')
			color = COL_RED;
		else
			color = COL_BLUE;
	}
	else
		content = g_pattern_empty[line];
	if (cell->selected && cell->data != ' ')
		printf("%s\033[7m%s%s", color, content, COL_RESET);
	else
		printf("%s%s%s", color, content, COL_RESET);
}

static void	print_separator(t_info *info)
{
	printf("%s++===============++===============++===============++%s\n",
		info->pad, info->pad);
}

static void	print_blank_line(t_info *info)
{
	printf("%s||               ||               ||               ||%s\n",
		info->pad, info->pad);
}

static void	print_content_row(t_info *info, int row, int line)
{
	int	col;

	printf("%s", info->pad);
	col = 0;
	while (col < 3)
	{
		printf("||");
		print_cell_line(&info->square[row][col], line, info->turn);
		col++;
	}
	printf("||%s\n", info->pad);
}

void	print_banner(void)
{
	printf("\n");
	printf("                              "
		COL_YELLOW COL_BOLD
		" ╔════════════════════════════════════╗\n" COL_RESET);
	printf("                              "
		COL_YELLOW COL_BOLD
		" ║       T I C   T A C   T O E        ║\n" COL_RESET);
	printf("                              "
		COL_YELLOW COL_BOLD
		" ╚════════════════════════════════════╝\n" COL_RESET);
	printf("\n");
}

void	display(t_info *info)
{
	int	row;
	int	line;

	clear_screen();
	print_banner();
	row = 0;
	while (row < LEN_SQUARES)
	{
		print_separator(info);
		print_blank_line(info);
		line = 0;
		while (line < 5)
		{
			print_content_row(info, row, line);
			line++;
		}
		print_blank_line(info);
		row++;
	}
	print_separator(info);
	printf("\n");
}

void	print_message(t_info *info, const char *msg, const char *color)
{
	printf("%s%s%s%s\n", info->pad, color, msg, COL_RESET);
}

/*
** Menu screen — returns the user's chosen mode, or exits on 'Q'.
*/
t_mode	show_menu(void)
{
	char	c;

	while (1)
	{
		clear_screen();
		print_banner();
		printf("                              "
			COL_CYAN COL_BOLD
			"            Choose a mode\n\n" COL_RESET);
		printf("                              "
			COL_GREEN COL_BOLD "  [1]" COL_RESET
			"   Play against AI  🤖\n");
		printf("                              "
			COL_GREEN COL_BOLD "  [2]" COL_RESET
			"   Play with a friend  👥\n");
		printf("                              "
			COL_RED COL_BOLD "  [Q]" COL_RESET
			"   Quit\n\n");
		printf("                              "
			COL_DIM "  Your choice: " COL_RESET);
		fflush(stdout);
		c = getch();
		if (c == '1')
			return (MODE_PVAI);
		if (c == '2')
			return (MODE_PVP);
		if (c == 'q' || c == 'Q')
		{
			clear_screen();
			restore_terminal();
			printf("\n  Bye! 👋\n\n");
			exit(0);
		}
	}
}
