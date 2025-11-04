#include <curses.h>
#include <string.h>

int main(void){
	char mesg[] = "Enter a string: ";
	char str[80];
	int row, col;
	initscr();
	getmaxyx(stdscr, row, col);
	mvprintw(row / 2, (col - (int) strlen(mesg)) / 2, "%s", mesg);
	getstr(str);
	mvprintw(LINES - 2, 0, "You Entered %s", str);
	mvprintw(LINES - 1, 0, "LINES = %d", LINES);
	getch();
	endwin();

	return 0;
}
