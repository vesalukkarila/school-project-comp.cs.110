#include <iostream>
#include <vector>
#include <cctype>
#include <random>
#include <string>
using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';

// Muuttaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan.
//
// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns zero.
unsigned int stoi_with_check(const string& str) // joka muuttaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
{                                               //MITÄ TOI CONST TOS EDESSÄ TEKIKÄÄN? funktio ei tee muutoksia parametriin, &on viiteparametri
    bool is_numeric = true;                     //eli viittaa välitettyyn parametriin joten voisi muuttaa mutta const estää sen, isot tiedostot..
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Tulostaa pelilaudan rivi- ja sarakenumeroineen.
//
// Prints the game board with row and column numbers.
void print(const vector<vector<int>>& gameboard)

{
    cout << "=================" << endl;
    cout << "|   | 1 2 3 4 5 |" << endl;
    cout << "-----------------" << endl;
    for(unsigned int i = 0; i < BOARD_SIDE; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < BOARD_SIDE; ++j)
        {
            if(gameboard.at(i).at(j) == 0)
            {
                cout << EMPTY << " ";
            }
            else
            {
                cout << gameboard.at(i).at(j) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "=================" << endl;
}

void arvo_pelilaudan_numerot(vector<vector<int>>& pelilauta)

{
    int siemen;
    cout<< "Enter a seed value: ";
    cin >> siemen;
    default_random_engine satunnaislukugeneraattoriolio(siemen);
    uniform_int_distribution<int> jakauma(1,5);

    for (int ulompilaskuri = 0; ulompilaskuri < 5; ++ulompilaskuri)
    {
        vector<int> rivi;
        for (int sisempilaskuri = 0; sisempilaskuri < 5; ++sisempilaskuri)
        {
            int luku = jakauma(satunnaislukugeneraattoriolio);
            rivi.push_back(luku);
        }
        pelilauta.push_back(rivi);

    }
}

void kysy_pelilaudan_numerot(vector<vector<int>>& pelilauta)  //patametrina ja paluuarvona pelilauta viiteparametrina johon tehdään muutoksia
{
    int syote;
    cout << "Input: ";
    for (int ulompilaskuri = 0; ulompilaskuri < 5; ++ulompilaskuri)
    {
        vector<int> rivi;
        for ( int sisempilaskuri = 0; sisempilaskuri < 5; ++sisempilaskuri)
        {
            cin >> syote;
            rivi.push_back(syote);
        }
        pelilauta.push_back(rivi);
    }

}

string kysy_tayttotapaa()
{
    while (true)
    {
        string syote;
        cout << "Select start (R for random, I for input): ";
        cin >> syote;
        if (syote.length()==1)
        {
            char merkki;
            merkki = syote.at(0);
            if (tolower(merkki) == 'r')
                return "arvo";

            else if (tolower(merkki) == 'i')
                return "kysy";
        }

        else
            continue;
    }
}

void kysy_poistettavat(vector<vector<int>>& pelilauta)
{
    while (true)                    // ohjaus funktioon joka poistaa alkion josta tarkistus jääkö irralleen-huomioi kulmat-"youlost"+paluuarvo
    {                               //"allready removed" tarkistus uupuu, ylläolevasta ohjaus toiseen funktioon
        string x_mjonona;           // uuden pelilaudan tulostus siitä funkusta jonka poistit, sille parametrina vektoriolio
        string y_mjonona;           //näistä paluu tähän funkkuun joka kysyy koordinaatteja aina uudelleen ja tarkistaa syötteet
                                    //voiton tarkistusfunktio jostain ja tulostus, main:sta?
        cout << "Enter removable element (x, y): ";
        cin >> x_mjonona;
        if (tolower(x_mjonona.at(0)) == 'q')        //Lopetus jos 'q'
        {
            cout << "Quitting" << endl;
            return;
        }
        cin >> y_mjonona;
        int x_lukuna = stoi_with_check(x_mjonona);
        int y_lukuna = stoi_with_check(y_mjonona);


        if (x_lukuna == false or y_lukuna == false  //Tarkistaa "out of board" kriteerit
                or x_lukuna < 1 or x_lukuna > 5
                or y_lukuna < 1 or y_lukuna > 5)
        {
            cout << "Out of board" << endl;
            continue;
        }
        if (pelilauta.at(y_lukuna-1).at(x_lukuna-1) == 0)   //onko poistettu aiemmin
        {
            cout << "Already removed" << endl;
            continue;
        }
        pelilauta.at(y_lukuna-1).at(x_lukuna-1) = 0;
        //tulostus
        print(pelilauta);
        //virhetarkistukset - ilmoitus ja paluu ja lopetus
        //voitontarkistus - ilmoitus ja paluu ja lopetus

    }
}



int main()
{
    vector<vector<int>> pelilauta;
    string paluuarvo = kysy_tayttotapaa();

    if (paluuarvo == "arvo")
        arvo_pelilaudan_numerot(pelilauta);
    else if (paluuarvo == "kysy")
        kysy_pelilaudan_numerot(pelilauta);

    print(pelilauta);
    kysy_poistettavat(pelilauta);

    cout << "Palasi mainiin poistettavista koordinaateista" << endl;


    return 0;
}
