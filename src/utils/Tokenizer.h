#pragma once
#include <iostream>
#include <sstream>
#include <string>

using std::istream;
using std::string;
using std::stringstream;

class Tokenizer
{
private:
    stringstream ss;

public:
    Tokenizer()
    {
        /*
            About: stream failures (reading a string into an int) don't throw failures.
                    It fails in silences and sets the error state flag failbit or badbit.
                    in putting .exceptions(std::ios::failbit) I am telling the stream to throw
                    the std::ios_base::failure exception instead
        */
        ss.exceptions(std::ios::failbit); // Bit flag for when a stream operation fails
    }

    Tokenizer(const string &source)
    {
        ss.str(source);
        ss.exceptions(std::ios::failbit);
    }

    void setString(const string &str);
    bool isEmpty();
    bool readLine(string &line);
    bool readInt(int &val);
    bool readDouble(double &val);
    bool readWord(string &val);
    bool readChar(char &val);

    void rewind();
    void clear();
    void clear(string &line);
};