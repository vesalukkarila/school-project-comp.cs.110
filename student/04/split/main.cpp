#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

// Toteuta funktio split, joka jakaa parametrina annetun merkkijonon erotinmerkkien
//kohdalta osiin ja palauttaa osat vector-muuttujaan tallennettuna.

vector <std::string> split(string rivi, char erottaja, bool totuusarvo = false)
{



}
int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
