#include <curses.h>
#include <string.h>

#define WIDTH 30
#define HEIGHT 10

int startx = 0;
int starty = 0;

const char* choices[] = 
{
	"Choice 1",
	"Choice 2",
	"Choice 3",
	"Choice 4",
	"Exit",
};

int n_choices = sizeof(choices) / sizeof(char*);

void print_menu(WINDOW *menu_win, int highlight);
void report_choice(int mouse_x, int mouse_y, int* p_choice);

int main(void){
	WINDOW* menu_win;
	MEVENT event;
	int highlight = 1;
	int choice = 0;
	int c;

	initscr();
	clear();
	noecho();
	cbreak();			//Line buffering disabled pass on everything
	
	//Window in middle of the screen
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;

	attron(A_REVERSE);
	mvprintw(23, 1, "Click on Exit to quit (Works best in a virtual console)");
	refresh();
	attroff(A_REVERSE);

	//Print menu for first time
	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	refresh();
	print_menu(menu_win, highlight);
	//Listen for all mouse events
	mousemask(ALL_MOUSE_EVENTS, NULL);

	while(1){
		c = wgetch(menu_win);
		switch(c){
			case KEY_MOUSE:
				if (getmouse(&event) == OK) {
					if (event.bstate & BUTTON1_PRESSED){
						report_choice(event.x + 1, event.y + 1, &choice);
						if (choice == -1)
							goto end;
						mvprintw(22, 1,
							"Choice made is : %d String Chosen is \"%10s\"",
							choice, choices[choice - 1]);
						refresh();
					}
				}
				print_menu(menu_win, choice);
				break;
		}
	}
	end:
		endwin();
		return 0;
}

void print_menu(WINDOW* menu_win, int highlight){
	int x, y, i;
	
	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for (i = 0; i < n_choices; ++i){
		if (highlight == i + 1)	//Highlight present choice
		{
			wattron(menu_win, A_REVERSE);
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
		{
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		}	
		++y;
	}
	wrefresh(menu_win);
}

//Report choice according to mouse position.
void report_choice(int mouse_x, int mouse_y, int *p_choice){
	int i, j, choice;
	
	//startx and y are in the middle
	i = startx + 2;
	j = starty + 3;

	for (choice = 0; choice < n_choices; ++choice){
		//If mouse is within bounding box of the choice
		if (mouse_y == j + choice
				&& mouse_x >= i
				&& mouse_x <= i + (int) strlen(choices[choice])){
			if (choice == n_choices - 1)	//and it's not the last choice
				*p_choice = -1;
			else				//Then pick the choice (unit-indexed)
				*p_choice = choice + 1;
			break;
		}
	}
}
