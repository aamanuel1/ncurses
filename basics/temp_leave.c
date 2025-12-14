#include <stdlib.h>
#include <curses.h>

int main(void){
	initscr();
	printw("Hello World !!!\n");
	refresh();
	getch();	//To slow it down
	def_prog_mode();//Leave ncurses
	endwin();
	system("/bin/sh");	//Go to shell!
	reset_prog_mode();
	refresh();
	getch();
	printw("Another String\n");
	refresh();		//Slow it down before ending.
	getch();
	endwin();

	return 0;
}
