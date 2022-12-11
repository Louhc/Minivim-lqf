//
// Created by Lenovo on 2022/11/21.
//
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <unistd.h>
#include "minivim.h"

extern const int filel=10;

int cursor_x, cursor_y;
WINDOW *file_win, *info_win, *comm_win;
std::string filename;
int line,col;

int main(int argc, char *argv[]) {
    initscr();
    raw();
    keypad(stdscr, true);
    getmaxyx(stdscr,line,col);
    file_win=newwin(filel,col,0,0);
    info_win=newwin(1,col,filel,0);
    comm_win=newwin(1,col,filel+1,0);

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2,COLOR_MAGENTA,COLOR_CYAN);
    init_pair(3,COLOR_GREEN,COLOR_RED);
    init_pair(4,COLOR_BLUE,COLOR_YELLOW);
    wbkgd(stdscr,COLOR_PAIR(1));
    wrefresh(stdscr);

    keypad(file_win, true);
    wbkgd(file_win,COLOR_PAIR(2));
    wrefresh(file_win);
    keypad(info_win,true);
    wbkgd(info_win,COLOR_PAIR(3));
    wprintw(info_win,":");
    wrefresh(info_win);
    wbkgd(comm_win,true);
    wbkgd(comm_win,COLOR_PAIR(4));
    wrefresh(comm_win);//上色
    werase(info_win);

    int command;
    std::fstream oitfile;
    while((command=getopt(argc,argv,"t:R:"))!=-1){
        filename=optarg;
        switch(command){
            case 't':{oitfile.open(optarg,std::ios::in | std::ios::out | std::ios::trunc);//打开文件，如果没有就创建
                    break;}
            case 'R':{oitfile.open(optarg,std::ios::in);//只读模式
                    break;}
        }
    }

    wmove(file_win,0,0);
    noecho();

    normal_mode();

    endwin();

    return 0;

}

