#include <iostream>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;

    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }

    if (word.length() > 2)
    {
        string::iterator eka = word.begin();
        string::iterator vika = word.end();
        shuffle(eka, vika, generator);

    }

    //vika--;


        std::cout << word << std::endl;
    }
}
