#include <vector>
#include <ncurses.h>
#include <unistd.h>
#include <ctime>
#include <string>

#include "Printer.h"
#include "AsciiBuffer.h"
#include "Logger.h"

using namespace std;

int Printer::sleeptimeMS = 40;
int Printer::offsetX = 0;
int Printer::offsetY = 0;

bool Printer::autocenter = true;

void Printer::init(const int sleeptimeMS, const int offsetX, const int offsetY)
{
    Printer::sleeptimeMS = sleeptimeMS;
    Printer::offsetX = offsetX;
    Printer::offsetY = offsetY;
    
    autocenter = (offsetX == 0 && offsetY == 0);

    setlocale(LC_ALL, "C.UTF-8");
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);

    Logger::SetNCursesMode(true);
}

void Printer::print(AsciiBuffer &buffer, const int maxVerticalDistortion)
{
    int maxX, maxY;
    vector<string>* lines = buffer.GetDistortedLinesPtr();
    int max_size = buffer.GetMaxLength();

    getmaxyx(stdscr, maxY, maxX);

    string message = "It's a little bit claustrophobic in here...";
    if (max_size + (2 * maxVerticalDistortion) > maxX || int(lines->size()) > maxY)
    {
        clear();
        move(maxY / 2, maxX / 2 - message.length() / 2);
        printw("%s" , message.c_str());
	refresh();
	usleep(100000);
        return;
    }

    clear();

    int i = 0;
    int x = 0;
    int y = 0;
    for (const string &line : *lines)
    {
        if (autocenter)
        {
            x = 0.5 * (maxX - (max_size + 2 * maxVerticalDistortion));
            y = 0.5 * (maxY - lines->size());
        }

        move(y + i, x);
        printw("%s", line.c_str());
        i++;
    }
}
