#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <string>
#include <fstream>
#include <algorithm>

class WordCounter {
private:
    std::string word;
    std::string filename;

    static bool icompare_pred(unsigned char a, unsigned char b);
public:
    WordCounter(const std::string& word, const std::string& filename);

    int count();

    bool icompare(const std::string& a, const std::string& b);
};

#endif // WORDCOUNTER_H
