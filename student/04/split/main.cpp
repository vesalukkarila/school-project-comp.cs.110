#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

// Toteuta funktio split, joka jakaa parametrina annetun merkkijonon erotinmerkkien
//kohdalta osiin ja palauttaa osat vector-muuttujaan tallennettuna.

vector <std::string> split(string rivi, char erottaja, bool totuusarvo = false)
{
    string::size_type pituus = rivi.length();
    string::size_type indeksi;
    for (indeksi = 0; indeksi < pituus; ++indeksi)
    {


    }


}
//erotinmerkin löytäminen, jakaminen osiin ja lisääminen vectoriin jonka palautus (tässä tarkkana, paikallinen muuttuja), tulostus tapahtuu mainissa
//2 versiota, toisessa ei tyhjiä alkioita

//Jos päädyt sellaiseen ratkaisuun, jossa käyt merkkijonon indeksejä läpi toistorakenteessa,
//käytä indeksimuuttujan tietotyyppinä string::size_type, älä int.          //MIKSI?

//lfind + laskuri jota verrataan string pituuteen, toistorakenteessa indeksi kerrallaan, lisäis kaikki vectoriin ja poistais vectorista 2:ssa versiossa
//käy string toistossa läpi ja jos indeksi = erotin ja indeksi-1=erotin niin lisää teksti.at(erotin) vektoriin
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
