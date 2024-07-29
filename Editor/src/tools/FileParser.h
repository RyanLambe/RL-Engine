#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace rl::ed
{
    class FileParser
    {
    public:
        static void BreakupFileToWords(std::vector<std::string>& words, std::ifstream& file)
        {
            std::string word;
            char nextLetter;
            while (file >> std::noskipws >> nextLetter)
            {
                if (std::isspace(static_cast<unsigned char>(nextLetter)))
                {
                    if (!word.empty())
                    {
                        words.push_back(word);
                        word = "";
                    }
                    continue;
                }
                switch (nextLetter)
                {
                    case ':':
                        if (words.back() == ":")
                        {
                            words.back() += ':';
                            continue;
                        }
                    case '{':
                    case '}':
                    case '(':
                    case ')':
                    case '<':
                    case '>':
                    case ';':
                    case '*':
                    case ',':
                    case '=':
                        if (!word.empty())
                        {
                            words.push_back(word);
                            word = "";
                        }
                        word += nextLetter;
                        words.push_back(word);
                        word = "";
                        break;
                    default:
                        word += nextLetter;
                }
            }
            if (!word.empty())
            {
                words.push_back(word);
                word = "";
            }
        }
    };
}
