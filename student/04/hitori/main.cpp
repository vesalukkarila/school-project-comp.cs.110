 /* Hitori
 *
 * Kuvaus:
 *   Ohjelma toteuttaa Hitori-pelin. Pelissä on peliruudukko kooltaan
 * 5 x 5. Kukin ruutu sisältää jonkin numeroista 1-5. Vaaka- ja
 * pystyriveillä voi aluksi olla useita samoja numeroita, mutta
 * tarkoituksena on poistaa numeroita niin, että kullakin vaaka- ja
 * pystyrivillä on kutakin numeroa vain yksi tai ei yhtään. Kuitenkaan
 * vierekkäisten ruutujen numeroita ei saa poistaa, eikä mikään jäljelle
 * jäävä numero (ruutu) saa jäädä irralleen muista, eli sen ympäriltä
 * (yläpuolelta, alapuolelta, vasemmalta, oikealta) ei saa poistaa
 * kaikkia numeroita.
 *   Aluksi käyttäjältä kysytään, täytetäänkö peliruudukko satunnaisesti
 * arvottavilla luvuilla 1-5 vai käyttäjän valitsemilla 25 luvulla.
 * Ensimmäisessä vaihtoehdossa käyttäjältä kysytään satunnaisluku-
 * generaattorin siemenlukua ja jälkimmäisessä häntä pyydetään syöttämään
 * 25 lukua.
 *   Joka kierroksella käyttäjältä kysytään poistettavan numeron
 * koordinaatteja eli kahta lukua. Peli päättyy pelaajan voittoon,
 * jos peliruudukon kaikilla vaaka- ja pystyriveillä esiintyy kukin
 * numero 1-5 korkeintaan kerran. Peli päättyy pelaajan häviöön,
 * jos hän poistaa jo poistetun numeron viereisen numeron tai jos
 * jokin numero jää irralleen muista.
 *   Ohjelma tarkistaa annetut koordinaatit. Koordinaattien pitää olla
 * peliruudukon sisällä, ja niiden osoittaman ruudun pitää sisältää
 * numero, eli jo poistettua numeroa ei voi poistaa toiseen kertaan.
 *   Pelin päättyessä kerrotaan, voittiko vai hävisikö pelaaja.
 *
 * Ohjelman kirjoittaja
 * Nimi: Vesa Lukkarila
 * Opiskelijanumero: 150372523
 * Käyttäjätunnus: h6vlukka
 * E-Mail: vesa.lukkarila@tuni.fi
*/

#include <iostream>
#include <vector>
#include <cctype>
#include <random>
#include <algorithm>
using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';

// Muuttaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan.
// Paluuarvona luonnollinen luku, viiteparametrina merkkijono.
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
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
// Viiteparametrina vector-tyypin pelilauta
// jonka alkiot vektoreita, joiden alkion kokonaislukuja.
// Ei paluuarvoa.
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

// Arpoo random kirjaston metodia hyödyntäen 25 lukua, jotka tallentaa
// vector-tyyppisen pelilaudan 5:een vektorin 5:een alkioon
// Ei paluuarvoa, viiteparametrina vector-tyypin pelilauta
// jonka alkiot vektoreita, joiden alkion kokonaislukuja.
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

// Kysyy käyttäjältä 25 lukua, jotka tallentaa
// vector-tyyppisen pelilaudan 5:een vektorin 5:een alkioon
// Ei paluuarvoa, viiteparametrina vector-tyypin pelilauta
// jonka alkiot vektoreita, joiden alkion kokonaislukuja.
void kysy_pelilaudan_numerot(vector<vector<int>>& pelilauta)
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

// Kysyy käyttäjältä kuinka pelilauta esitäytetään.
// Ei parametria, paluuarvona mainiin string.
string kysy_tayttotapaa()
{
    while (true)
    {
        string syote;
        cout << "Select start (R for random, I for input): ";
        getline(cin, syote);
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
        {
            //cout << endl;
            continue;
        }
    }
}




void kysy_koordinaatteja(vector<vector<int>>& pelilauta)
{
    while (true)
    {
        string x_mjonona;
        string y_mjonona;

        cout << "Enter removable element (x, y): ";
        cin >> x_mjonona;
        if (tolower(x_mjonona.at(0)) == 'q')    //Lopetus jos syötteenä 'q'
        {
            cout << "Quitting" << endl;
            return;
        }
        cin >> y_mjonona;
        int x_lukuna = stoi_with_check(x_mjonona);
        int y_lukuna = stoi_with_check(y_mjonona);

        //Tarkistaa onko syöte sallittu
        if (x_lukuna == false or y_lukuna == false
                or x_lukuna < 1 or x_lukuna > 5
                or y_lukuna < 1 or y_lukuna > 5)
        {
            cout << "Out of board" << endl;
            continue;
        }

        //Tarkistaa onko koordinaatit poistettu aiemmin
        if (pelilauta.at(y_lukuna-1).at(x_lukuna-1) == 0)
        {
            cout << "Already removed" << endl;
            continue;
        }

        //Asettaa koordinaatin arvoksi nollan
        pelilauta.at(y_lukuna-1).at(x_lukuna-1) = 0;
        print(pelilauta);

        //Seuraavaksi häviötilanteiden tarkistukset
        if (tyhjat_vierekkain(pelilauta) == false or jaako_numero_yksin(pelilauta) == false)
        {
            cout << "You lost" << endl;
            return;
        }

        //Voitontarkistus
        if (voiton_tarkistus(pelilauta) == true)
        {
            cout << "You won" << endl;
            return;
        }
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
    kysy_koordinaatteja(pelilauta);


    return 0;
}
