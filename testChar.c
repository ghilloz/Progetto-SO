#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

struct sprite {
  int width;
  int height;
  char * spt;
};

void printpxl (int y, int x) {
    mvaddch(y, x, ' ');
    mvaddch(y, x+1, ' ');
};

void print_sprite (int y, int x, struct sprite * spt) {
    for (int j = y, z = 0; z < spt->height; j++, z++) {
        for (int i = x, w = 0; w < spt->width; i+=2, w++) {
          if (spt->spt[w+z*spt->width] == ' ') printpxl (j,i);
        }
    }
};


int main() {
    // Initialize ncurses
    initscr();
    start_color();
    curs_set(0);
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);

    // Define color pairs
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // Pair ID 1 for white text on black background
    init_pair(1, COLOR_BLACK, COLOR_GREEN);    

    char s[] = "* *    * ";
    char svas[] = "   * ** *       * ** *   ";
    struct sprite spt = {3,3, s};
  
    
    // Set color pair
    attron(COLOR_PAIR(1));

    
    // Print colored character
    //attron(A_REVERSE); // Reverse video to print background color

    print_sprite(0,0, &spt); 

    int x_step = 0, y_step = 0, x = 0, y = 0;
    bool move = false;
    char flag = 0, key = 0;
    while (flag != 'q') {
        flag = (char)getch();
        if (flag == 'a') {x -= 10; move = true; x_step = (-10);}
        else if (flag == 'd') {x+= 10;move = true; x_step = 10;}
        else if (flag == 'w') {y -= 5; move = true; y_step = (-5);}
        else if (flag == 's') {y += 5;move = true; y_step = 5;}
        
        if (move) {
          attron(COLOR_PAIR(2));
          print_sprite(y-y_step, x-x_step, &spt);
          x_step = 0; y_step = 0;
          attron(COLOR_PAIR(1));
          print_sprite(y, x, &spt);
          refresh();
        }
        usleep(5000);
    }

    attroff(A_REVERSE); // Turn off reverse video

    // Refresh the screen
    refresh();

    // Wait for user input
    getch();

    // End ncurses
    endwin();

    return 0;
}