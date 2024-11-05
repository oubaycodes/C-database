#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <signal.h>

void handleResize(int sig)
{

    signal(SIGWINCH, SIG_IGN);

    endwin();
    initscr();
    refresh();
    clear();

    // char tmp[128];
    // // sprintf(tmp, "%dx%d", COLS, LINES);
    // char *text = "fuck you";
    // // Approximate the center
    // int x = COLS / 2 - strlen(text) / 2;
    // int y = LINES / 2 - 1;

    // mvaddstr(y, x, "FUCK YOU");
    refresh();

    signal(SIGWINCH, handleResize);
}
void initTerminalInterface()
{
    // warning basically playground code i never used this shi before so i gotta play around
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // COLS/LINES are now set
    // handleResize(0);
    signal(SIGWINCH, handleResize);

    char *text = "fuck you";
    int x = 0;
    int y = 0;

    int ch;
    while ((ch = getch()) != 'q')
    {
        switch (ch)
        {
        case KEY_RIGHT:
            x++;
            break;
        case KEY_LEFT:
            x--;
            break;

        case KEY_UP:
            y--;
            break;

        case KEY_DOWN:
            y++;
            break;
        }

        clear();
        mvprintw(y, x, "");
        refresh();
    }
    endwin();
}