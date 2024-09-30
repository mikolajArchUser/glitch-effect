#include <string>
#include <vector>

#include "Logger.h"
#include "AsciiBuffer.h"

using namespace std;

// On create
AsciiBuffer::AsciiBuffer()
{
    lines = vector<string>();
    distortedLines = vector<string>();
    Logger::PrintDebug("Created a new AsciiBuffer.");
}

// On destroy
AsciiBuffer::~AsciiBuffer()
{
    Logger::PrintDebug("Destroyed AsciiBuffer.");
}


// Setters

void AsciiBuffer::AddLine(const string line)
{
    AsciiBuffer::lines.push_back(line);
}

void AsciiBuffer::AddLines(const vector<string> lines)
{
    vector<string> result = vector<string>();

    result.reserve(AsciiBuffer::lines.size() + lines.size());
    result.insert(result.end(), AsciiBuffer::lines.begin(), AsciiBuffer::lines.end());
    result.insert(result.end(), lines.begin(), lines.end());

    AsciiBuffer::lines = result;
}

void AsciiBuffer::OverwriteLines(const vector<string> lines)
{
    AsciiBuffer::lines = lines;
}

void AsciiBuffer::ClearAll()
{
    AsciiBuffer::lines = vector<string>();
}


//Getters

int AsciiBuffer::GetLineCount()
{
    return AsciiBuffer::lines.size();
}

vector<string> AsciiBuffer::GetLines()
{
    return AsciiBuffer::lines;
}


// Filters

void AsciiBuffer::VerticalDistort(const int intensity, const int strength)
{
    if (distortedLines.size() == 0)
    {
        Logger::PrintDebug("Distorted lines buffer is empty. Copying lines to distortedLines.");
        distortedLines = lines;
    }
    
    int i = 0;
    for (const string &str : lines)
    {
        int num = strength;

        int rev_effect = rand() % 2;

        if ((rand() % intensity + 1) == 1)
        {
            if (!rev_effect)
            {
                num += rand() % strength + 1;
            }
            else
            {
                num -= rand() % strength + 1;
            }
        }

        i++;
    }
}
