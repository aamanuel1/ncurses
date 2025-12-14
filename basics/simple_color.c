#include <stdlib.h>
#include <string.h>
#include <curses.h>

void print_in_middle(WINDOW *win, int starty, int startx, int width, const char* string);

int main(void){
	initscr();
	if (has_colors() == FALSE){
		endwin();
		printf("Your terminal doesn't support colour\n");
		exit(1);
	}

	start_color();
	init_color(COLOR_RED, 600, 0, 0);    
	/* param 1     : color name
     	* param 2, 3, 4 : rgb content min = 0, max = 1000 */
	init_pair(1, COLOR_RED, COLOR_BLACK);				//1, foreground, background colour
	
	attron(COLOR_PAIR(1));
	print_in_middle(stdscr, LINES / 2, 0, 0, "Viola !!! in colour ...");
	attroff(COLOR_PAIR(1));
	getch();
	endwin();
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, const char* string){
	int length, x, y;
	float temp;

	if (win == NULL)
		win = stdscr;						//Standard screen
	getyx(win, y, x);
	if (startx != 0)
		x = startx;
	if (starty != 0)
		y = starty;
	if (width == 0)
		width = 80;

	length = (int)strlen(string);
	temp = (float)(width - length) / 2;
	x = startx + (int) temp;
	mvwprintw(win, y, x, "%s", string);
	refresh();
}
