#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Craps.h"

int main()
{
    // Ensure all numbers generated randomly are actually random
    srand(time(NULL));

    Craps TripleH;

    TripleH.theGame();
    return 0;
}