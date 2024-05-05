#include "WordCounter.hpp"

WordCounter::WordCounter(const std::string& filename) : filename(filename) {}


void WordCounter::setWord(const std::string& word) 
{
    this->word = word;
}

int WordCounter::count() 
{
    int count = 0;
    std::string ch;
    std::ifstream input_file(filename.c_str());

    while (input_file >> ch) 
    {
        if (icompare(ch, word))
            count++;
    }
    input_file.close();
    return count;
}

bool WordCounter::icompare(const std::string& a, const std::string& b) 
{
    if (a.length() == b.length())
        return std::equal(a.begin(), a.end(), b.begin(), icompare_pred);
    return false;
}

bool WordCounter::icompare_pred(unsigned char a, unsigned char b) 
{
    return tolower(a) == tolower(b);
}
