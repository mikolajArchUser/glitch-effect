#include <vector>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <ncurses.h>

#include "Logger.h"
#include "FileLoader.h"
#include "ConfigLoader.h"
#include "ArgInterpreter.h"

using namespace std;

int getParamFromConf(map<string, int>* conf, const string& param)
{
    auto it = conf->find(param);

    if (it != conf->end())
    {
        Logger::PrintLog("Param '" + param + "' = " + to_string(it->second));
        return it->second;
    } 
    else
    {
        Logger::PrintWarn("Param '" + param + "' not found in config file.");
        return -1;
    }
}

int main(int argc, char *argv[])
{
    srand(time(nullptr));

    argstruct args;

    args.ascii_path = "";
    args.config_path = "";

    int sleeptime_ms = 40;
    int glitch_strength = 6;
    int glitch_intensity = 35;

    bool autocenter = true;

    args = ArgInterpreter::GetArgs(argc, argv);
    if (args.help_requested)
    {
        Logger::PrintDebug("Help requested by user. Exiting...");
        return 0;
    }
    else if (args.exit)
    {
        Logger::PrintDebug("Told to exit by the arginterpreter. Exiting now...");
        return 0;
    }

    int conf_exit_code = 1;
    map<string, int> config;

    if (args.config_specified)
    {
        config = ConfigLoader::LoadConf(args.config_path);
        conf_exit_code = getParamFromConf(&config, "exit-code");
    }

    int* output_tmp;

    if (conf_exit_code == 0)
    {
	Logger::PrintDebug("Config loaded succesfully.");

    	output_tmp = new int(getParamFromConf(&config, "strength"));
    	if (*output_tmp != -1)
    	    glitch_strength = *output_tmp;
    	delete output_tmp;

    	output_tmp = new int(getParamFromConf(&config, "intensity"));
    	if (*output_tmp != -1)
    	    glitch_intensity = *output_tmp;
    	delete output_tmp;

	output_tmp = new int(getParamFromConf(&config, "sleeptime"));
    	if (*output_tmp != -1)
    	    sleeptime_ms = *output_tmp;
    	delete output_tmp;
    }

    const vector<string> lines = FileLoader::GetLines(args.ascii_path);
    if (lines.size() == 0)
    {
        Logger::PrintErr("Ascii file was empty!");
        Logger::PrintWarn("Nothing to display. Quitting...");
        return 0;
    }

    setlocale(LC_ALL, "C.UTF-8");
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    curs_set(0);

    int fileX = 0;
    int maxX, maxY;

    for (const string &str : lines)
    {
        if (static_cast<int>(str.length()) > fileX)
            fileX = str.length();
    }


    while (true)
    {
        getmaxyx(stdscr, maxY, maxX);

        if (fileX + (2 * glitch_strength) > maxX)
        {
            clear();
            move(maxY / 2, maxX / 2 - 21);
            printw("It's a little bit claustrophobic in here...");
	    refresh();
	    usleep(200000);
	    continue;
        }

        clear();
        int i = 0;
        for (const string &str : lines)
        {
            int num = 0;

            if ((rand() % glitch_intensity + 1) == 1)
            {
                num = rand() % glitch_strength + 1;
            }

            int rev_effect = rand() % 2;

            if (autocenter)
            {
                args.ox = 0.5 * (maxX - (fileX + 2 * glitch_strength));
                args.oy = 0.5 * (maxY - lines.size());
            }

            if (rev_effect == 1)
                move(args.oy + i, args.ox - num + glitch_strength);
            else
                move(args.oy + i, args.ox + num + glitch_strength);

            printw("%s", str.c_str());

            i++;
        }

	int ch = getch();
	if (ch == 'q')
            break; 

        refresh();

        usleep(1000 * sleeptime_ms);
    }

    endwin();
    return 0;
}
