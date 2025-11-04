#include <curses.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int ch, row, col;
	int prev = EOF;
	FILE *fp;
	int y, x;

	if(argc != 2){
		printf("Usage: %s <a c filename>\n", argv[0]);
	}

	fp = fopen(argv[1], "r");
	if(fp == NULL){
		perror("Cannot open input file");
		exit(1);
	}

	initscr();
	getmaxyx(stdscr, row, col);		/*size of standard screen window*/
	(void) col;				/*Used to ignore compiler errors?*/
	while((ch = fgetc(fp)) != EOF){		/*fgetc to file pointer is not at end of file*/
	getyx(stdscr, row, col);		/*get current cursor location*/
		if(y == (row - 1)){		/*at end of screen?*/
			printw("<-Press Any Key->");
			getch();
			clear();
			move(0, 0);		/*start at beginning of screen*/
		}
		if(prev == '/' && ch == '*'){
			attron(A_BOLD);		/*bold on */
			getyx(stdscr, y, x);
			move(y, x - 1);		/*Move one space back*/
			printw("%c%c", '/', ch);
		}
		else{
			printw("%c", ch);
		}
		refresh();
		if(prev == '*' && ch == '/')
			attroff(A_BOLD);	/*bold off*/
		prev = ch;
	}
	endwin();
	fclose(fp);
	return 0;
}
