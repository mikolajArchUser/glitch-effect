#ifndef PRINTER_H
#define PRINTER_H

#include<string>
#include<vector>

#include "AsciiBuffer.h"

class Printer
{
    public:
        static void init(const int sleeptimeMS, const int offsetX, const int offsetY);
        static void print(AsciiBuffer &buffer, const int maxVerticalDistortion);

    private:
        static int sleeptimeMS;
        static int offsetX;
        static int offsetY;

        static bool autocenter;
};

#endif
