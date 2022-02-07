#include <iostream>
#include <vector>
#include <cctype>

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



void arvo_pelilaudan_numerot()
{

    cout<< "Funktio arpoo pelilaudan numerot ja tallentaa nämä vektorinvektorin alkioihin " << endl;

}

void kysy_pelilaudan_numerot()
{
    cout << "Funktio kysyy käyttäjältä 25 numeroa ja tallentaa nämä vektorinvektorin alkioihin" << endl;

}

void kysy_tayttotapaa()
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
            {
                arvo_pelilaudan_numerot();
                return;
            }
            else if (tolower(merkki) == 'i')
            {
                kysy_pelilaudan_numerot();
                return;
            }
        }
        else
            continue;
    }
}

void kysy_poistettavat()            //"allready removed" tarkistus uupuu
{
    while (true)
    {
        string x_mjonona;
        string y_mjonona;
        int x_lukuna;
        int y_lukuna;
        string koordinaatit_mjono;
        cout << "Enter removable element (x, y): ";
        cin >> x_mjonona;
        cin >> y_mjonona;

        while (true)
        {
            x_lukuna = stoi_with_check(x_mjonona);
            y_lukuna = stoi_with_check(y_mjonona);
            if (x_lukuna == false or y_lukuna == false
                    or x_lukuna < 1 or x_lukuna > 5
                    or y_lukuna < 1 or y_lukuna > 5)
            {
                cout << "Out of board" << endl;
                break;
            }


            cout << x_lukuna << "ja" << y_lukuna << endl;
            cout << x_lukuna * y_lukuna << endl;
            break;
        }
    }
}
int main()
{
    kysy_tayttotapaa();
    cout << "Palasi mainiin ksy_tayttotapa" << endl;        //poista myöhemmin

    kysy_poistettavat();
    cout << "Palasi mainiin poistettavista koordinaateista" << endl;


    return 0;
}
