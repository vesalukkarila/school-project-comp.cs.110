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

bool tyhjat_vierekkain(vector<vector<int>>& pelilauta)
{
    for (int y_laskuri = 0; y_laskuri<5; ++y_laskuri)   //tarkistaa ensin vaakasuuntaiset rivit, onko tyhjiä vierekkäin
    {
        for (int x_laskuri = 1; x_laskuri<4; ++x_laskuri)
        {
            if (pelilauta.at(y_laskuri).at(x_laskuri) == 0 and
                    (pelilauta.at(y_laskuri).at(x_laskuri-1) ==0 or
                     pelilauta.at(y_laskuri).at(x_laskuri+1) ==0))
                return false;
        }
    }

    for (int x_laskuri = 0; x_laskuri<5; ++x_laskuri)   //sitten tarkistetaan pystyrivit
    {
        for (int y_laskuri = 1; y_laskuri<4; ++y_laskuri)
        {
            if (pelilauta.at(y_laskuri).at(x_laskuri) == 0 and
                    (pelilauta.at(y_laskuri-1).at(x_laskuri) ==0 or
                     pelilauta.at(y_laskuri+1).at(x_laskuri) ==0))
                return false;
        }
    }

    return true;
}

bool jaako_numero_yksin(vector<vector<int>>& pelilauta) //tää on raskas tyyli käydä läpi mutten keksinyt mikä olisi oikea tapa
{
    bool vasen_ylakulma = pelilauta.at(0).at(1) == 0 and pelilauta.at(1).at(0) == 0;
    bool oikea_ylakulma = pelilauta.at(0).at(3) == 0 and pelilauta.at(1).at(4) == 0;
    bool vasen_alakulma = pelilauta.at(4).at(1) == 0 and pelilauta.at(3).at(0) == 0;
    bool oikea_alakulma = pelilauta.at(4).at(3) == 0 and pelilauta.at(3).at(4) == 0;

    if (vasen_ylakulma == true or oikea_ylakulma == true or vasen_alakulma == true or oikea_alakulma == true)
        return false;
    for (int x = 1; x < 4; ++ x)    //eka rivi keskeltä 0,1 0,2 0,3
    {
        if (pelilauta.at(0).at(x-1)==0 and pelilauta.at(0).at(x+1)==0 and pelilauta.at(1).at(x)==0)
            return false;
    }

    for (int y = 1; y < 4; ++y)       //vasen laita
    {
        if (pelilauta.at(y-1).at(0)==0 and pelilauta.at(y+1).at(0)==0 and pelilauta.at(y).at(1)==0)
            return false;
    }

    for (int y = 1; y < 4; ++y)       //oikea laita
    {
        if (pelilauta.at(y-1).at(4)==0 and pelilauta.at(y+1).at(4)==0 and pelilauta.at(y).at(3)==0)
            return false;
    }

    for (int x = 1; x < 4; ++ x)    //ala laita
    {
        if (pelilauta.at(4).at(x-1)==0 and pelilauta.at(4).at(x+1)==0 and pelilauta.at(3).at(x)==0)
            return false;
    }

    for (int y = 1; y<4; ++y)
    {
        for (int x = 1; x < 4; ++x)     //ylös, alas, vasen, oikea
        {
            if (pelilauta.at(y-1).at(x) == 0 and pelilauta.at(y+1).at(x) == 0
                    and pelilauta.at(y).at(x-1) == 0 and pelilauta.at(y).at(x+1) == 0)
                return false;
        }
    }
    return true;
}

void kysy_poistettavat(vector<vector<int>>& pelilauta)
{
    while (true)
    {
        string x_mjonona;
        string y_mjonona;

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
        //virhetarkistukset -
        //  -kaks nollaa vierekkäin
        if (tyhjat_vierekkain(pelilauta) == false)
        {
            cout << "You lost" << endl;
            return;                         //muuta jos muutat paluuarvontyyppiä
        }
        //  -numero jää yksin, huomioi reunat ja kulmat
        if (jaako_numero_yksin(pelilauta) == false)
        {
            cout << "You lost" << endl;
            return;
        }

        //voitontarkistus - ilmoitus ja paluu ja lopetus

    }
}


//5 COMMITTIA, PITIKÖ NE PUSHATA VAI RIITTIKÖ TUO COMMIT MITKÄ TEIN
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
