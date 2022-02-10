#include <iostream>
#include <string>
#include <algorithm>
#include <random>
using namespace std;
int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;     //luodaan satunnaisulukugeneraattori generator

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;

    while (std::cin >> word)    //toistorakenteeseen mennään niiinkauan kuin tietovirrasta onnistuneesti talletetaan sana muuttujaan word
    {
        if (word == "END")      //jos "end" lopetetaan suoritus
        {
            return EXIT_SUCCESS;
        }

        // TODO: implement your solution here
        //string merkkijono = word;

        string::iterator valin_eka = word.begin();   //alku iteraattoriksi
        string::iterator valin_vika = word.end();    //pääty loppuiteraattoriksi
        if (word.length()>2)
        {
            ++valin_eka;                                                //iteraattorin kasvatus
            --valin_vika;                                               //iteraattorin miinustus tokavikaan
        }
        shuffle(valin_eka, valin_vika, generator);  //shufflella määrätyltä väliltä satunnaigeneraattorinavulla sekoitus
        cout << word << endl;

	
    }
}
//syötettyjen sanojen ensimmäinen ja viimeinen kirjain paikallaan, loput sotketaan shuffle
//rivinvaihtomerkki(?)
//string säiliön ja char alkio? joka kirjaimen siirtäminen vectoriin (alustus sanan pituudella) ja vektorin käsittely shufflella
//Käytä tekstin sotkemisessa STL:n algoritmia shuffle ja ohjelmakoodipohjassa main-funktion ensimmäisellä rivillä määriteltyä
//pseudosatunnaislukugeneraattoria generator, jolloin ohjelmalle tuotetaan automaattitesteissä sopivia satunnaislukuja.
