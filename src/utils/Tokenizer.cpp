#include "Tokenizer.h"

void Tokenizer::setString(const string &str)
{
    ss.str(str);
}

bool Tokenizer::isEmpty()
{
    return ss.peek() == EOF; // peek returns EOF on empty/EOF values
}

bool Tokenizer::readLine(string &line)
{
    if (isEmpty())
        return false;

    if (getline(ss, line)) // read whole stream from ss into line
        return true;

    return false;
}

bool Tokenizer::readInt(int &val)
{
    if (isEmpty())
        return false;

    try
    {
        ss >> val;
    }
    catch (std::ios_base::failure)
    {
        ss.clear(); // resets internal error state flags - failbit, eofbit, badbit [stringstream]
        ss.unget(); // Put last character read back into the stream - think putting rotten fruit back in the fridge instead of throwing it away

        // If stream still in a bad state, clear again for good measures
        if (ss.bad())
            ss.clear();

        return false;
    }

    return true;
}

bool Tokenizer::readDouble(double &val)
{
    if (isEmpty())
        return false;

    std::streampos pos = ss.tellg();

    try
    {
        ss >> val;
    }
    catch (std::ios_base::failure)
    {
        ss.clear(); // resets internal error state flags - failbit, eofbit, badbit [stringstream]
        ss.unget(); // Put last character read back into the stream - think putting rotten fruit back in the fridge instead of throwing it away

        // If stream still in a bad state, clear again for good measures
        if (ss.bad())
            ss.clear();

        return false;
    }

    // In the event a Int val is passed
    if (std::floor(val) == val)
    {
        // Rewind the stream to let another parser try
        ss.clear();    // clear flags just in case
        ss.seekg(pos); // reset stream position
        return false;
    }

    return true;
}

bool Tokenizer::readWord(string &val)
{
    if (this->isEmpty())
        return false;

    try
    {
        ss >> val;
    }
    catch (std::ios_base::failure)
    {
        ss.clear(); // resets internal error state flags - failbit, eofbit, badbit [stringstream]
        ss.unget(); // Put last character read back into the stream - think putting rotten fruit back in the fridge instead of throwing it away

        // If stream still in a bad state, clear again for good measures
        if (ss.bad())
            ss.clear();

        return false;
    }

    return true;
}

bool Tokenizer::readChar(char &val)
{
    if (this->isEmpty())
        return false;

    try
    {
        ss >> val;
    }
    catch (std::ios_base::failure)
    {
        ss.clear(); // resets internal error state flags - failbit, eofbit, badbit [stringstream]
        ss.unget(); // Put last character read back into the stream - think putting rotten fruit back in the fridge instead of throwing it away

        // If stream still in a bad state, clear again for good measures
        if (ss.bad())
            ss.clear();

        return false;
    }

    return true;
}

bool Tokenizer::isDone()
{
    // Skip any trailing whitespace
    char c;
    while (ss >> std::ws && ss.peek() != EOF)
    {
        ss >> c;
        if (!isspace(c))
            return false;
    }

    return true;
}

void Tokenizer::rewind()
{
    ss.seekg(0, ss.beg);
}

void Tokenizer::clear()
{
    setString("");
    ss.setstate(std::ios::eofbit);
}

void Tokenizer::clear(string &line)
{
    line = " ";
}