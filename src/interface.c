#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <signal.h>

void displayLoginPage()
{
    // mvaddstr(0, COLS / 2, "C Database Employee Management\n");
    mvaddstr(2, 2, "Enter admin login credentials:");
    mvaddstr(4, 12, "Enter username:");
    mvaddstr(5, 12, "Enter password:");
    // 16 is the size of the string
}
void handleResize(int sig)
{

    signal(SIGWINCH, SIG_IGN);

    endwin();
    initscr();
    refresh();
    clear();

    char *text = "C Database Employee Management";
    // // Approximate the center
    int x = COLS / 2 - strlen(text) / 2;

    mvaddstr(0, x, text);
    displayLoginPage();
    refresh();

    signal(SIGWINCH, handleResize);
}

void initTerminalInterface()
{
    initscr();
    cbreak();
    // noecho();
    keypad(stdscr, TRUE);

    signal(SIGWINCH, handleResize);
    int ch;
    char user[100] = "";
    char password[100] = "";
    do
    {
        handleResize(0);
        displayLoginPage();

        move(4, 12 + 16);
        getstr(user);

        move(5, 12 + 16);
        getstr(password);
        if (user[0] != '\0' && password[0] != '\0')
            clear();
        else
        {
            clear();
            handleResize(0);
            displayLoginPage();
        }
        refresh();
    } while ((ch = getch()) != 'q');

    endwin();
}
