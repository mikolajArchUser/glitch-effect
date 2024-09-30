#ifndef ASCII_BUFFER_H
#define ASCII_BUFFER_H

#include <vector>
#include <string>

class AsciiBuffer
{
    public:
        AsciiBuffer();
        ~AsciiBuffer();

        // Setters
        void AddLine(const std::string line);
        void AddLines(const std::vector<std::string> lines);
        void OverwriteLines(const std::vector<std::string> lines);
        void ClearAll();

        // Getters
        int GetLineCount();
        std::vector<std::string> GetLines();

        // Filters
        void VerticalDistort(const int intensity, const int strength);

    private:
        std::vector<std::string> lines;
        std::vector<std::string> distortedLines;
};

#endif
