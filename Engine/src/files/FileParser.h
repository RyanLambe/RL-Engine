#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace rl
{
    class FileParser
    {
    public:
        static void ReplaceKeyword(const std::filesystem::path& path, const std::string& from, const std::string& to) {
            try {
                // Open the file for reading
                std::ifstream inputFile(path);
                if (!inputFile.is_open()) {
                    throw std::ios_base::failure("Failed to open the file.");
                }

                // Read the content of the file
                std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
                inputFile.close();

                // Replace all occurrences of "from" with "to"
                size_t pos = 0;
                while ((pos = content.find(from, pos)) != std::string::npos) {
                    content.replace(pos, from.length(), to);
                    pos += to.length(); // Advance position
                }

                // Open the file for writing (overwrite mode)
                std::ofstream outputFile(path);
                if (!outputFile.is_open()) {
                    throw std::ios_base::failure("Failed to open the file for writing.");
                }

                // Write the modified content back to the file
                outputFile << content;
                outputFile.close();
            }
            catch (const std::exception& e) {
                RL_LOG_ERROR("Error: ", e.what());
            }
        }

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
