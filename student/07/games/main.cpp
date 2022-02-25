/*  COMP.CS.100 Project 2: GAME STATISTICS
 * ===============================
 * EXAMPLE SOLUTION
 * ===============================
 *
 *  Acts as a game statistics with n commands:
 * ALL_GAMES - Prints all known game names
 * GAME <game name> - Prints all players playing the given game
 * ALL_PLAYERS - Prints all known player names
 * PLAYER <player name> - Prints all games the given player plays
 * ADD_GAME <game name> - Adds a new game
 * ADD_PLAYER <game name> <player name> <score> - Adds a new player with the
 * given score for the given game, or updates the player's score if the player
 * already playes the game
 * REMOVE_PLAYER <player name> - Removes the player from all games
 *
 *  The data file's lines should be in format game_name;player_name;score
 * Otherwise the program execution terminates instantly (but still gracefully).
 *
 * */
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>          //tiedostojen lukeminen
#include <sstream>          //stringstream
#include <cctype>       //toupper

using namespace std;

//tietorakenne
using PELIEN_TIETOTYYPPI = map<string, map<string, int>>;

//merkkijonovakiot
const string VIRHE_TEKSTI = "Error. Invalid input.";
const string EI_LOYDY_TEKSTI = " could not be found.";


// Casual split func, if delim char is between "'s, ignores it.
std::vector<std::string> split( const std::string& str, char delim = ';' )      //palauttaa vektorin jossa merkillä erotetut sanat omissa alkioissaan
{
    std::vector<std::string> result = {""}; //palautettava vector jonka alkiot string
    bool inside_quatation = false;  //muuttu loopissa trueksi jos '"'
    for ( auto current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quatation = not inside_quatation;        //muuttuu trueksi jos heittomerkki
        }
        else if ( current_char == delim and not inside_quatation )  //jos jotain, lisää tyhjän (ei välilyöntiä) alkioksi erotinmerkin tullessa vastaan
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);      //lisää merkin alkioksi, hetkinen back().pushback, työntää samaan alkioon luulen
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

bool rivit_kunnossa(vector <string> const& rivivektori)
{
    //VALMIS
    //Tarkistaa että vektorissa on 3 alkiota ja ettei pelin (indeksi 0) tai pelaajan (indeksi 1) kohta ole tyhjä
    return rivivektori.size() == 3
            && !rivivektori.at(0).empty()
            && !rivivektori.at(1).empty();
}

bool tiedoston_avaus (PELIEN_TIETOTYYPPI& pelit_map)
{
    //VALMIS, voiko osia käyttää?
    string tiedosto = "";
    cout << "Give a name for input file: ";
    getline(cin, tiedosto);
    ifstream tiedostonavausolio(tiedosto);      //esitellään tiedostonavausolio ja yritetään avata syötetty tiedosto

    if (not tiedostonavausolio)
    {
        cout << "Error: File could not be read." << endl;
        return false;
    }

    string rivi = "";
    vector <string> rivi_vektori;
    while (getline(tiedostonavausolio, rivi))
    {

        rivi_vektori = split(rivi);     //;-merkillä erotetu sanat omissa alkioissaan
        //tarkistetaan että syötetiedoston rivit sisältävät halutut asiat
        if (not rivit_kunnossa(rivi_vektori))       //jos rivit ei ole kunnossa, palautetaan false
        {
            cout << "Error: Invalid format in file." << endl;
            tiedostonavausolio.close();
            return false;
        }

        string peli = rivi_vektori.at(0);
        string pelaaja = rivi_vektori.at(1);
        int pisteet = stoi(rivi_vektori.at(2));

        if (pelit_map.find(peli) == pelit_map.end())    //jos peliä ei ole, lisätään avaimeksi ulompaan sanakirjaan
        {
            pelit_map.insert({peli, {}});
        }
        pelit_map.at(peli).insert({pelaaja, pisteet});  //peli löytyy, lisätään sisempään sanakirjaan avain-arvo-pariksi pelaaja&pisteet
    }

    return true;
}

//ALL_GAMES komento
void pelien_tulostus(PELIEN_TIETOTYYPPI const& pelit_map)
{
    //VALMIS
    cout << "All games in alphabetical order:" << endl;
    for (auto tietopari : pelit_map)
        cout << tietopari.first << endl;
}


//KOMENTOJEN PERUSTEELLA FUNKTIOIDEN KUTSU TÄSTÄ FUNKTIOSTA, JOTTEI MAIN TÄYTY
void funktio_kutsut (PELIEN_TIETOTYYPPI& pelit_map, string const& komento_isolla, vector<string> const& apuvektori)//pelit_map vain viitteenä, koska sitä muokataan
{
    if (komento_isolla == "ALL_GAMES")
        pelien_tulostus(pelit_map);
    //else if (komento_isolla == "")

    //else if (komento_isolla == "")

    //else if (komento_isolla == "")

    //else if (komento_isolla == "")
}
//VAKIOMUUTTUJA MAP, PELIT-MAININ APUVEKTORIA VARTEN VERTAILU ALKIOIDEN MÄÄRISTÄ
const map<string, vector<string>::size_type> KOMENTO_TARKISTUS = {{"ALL_GAMES", 1}, {"GAME", 2},//hyötykuorma muutettu sizetypeksi jotta vertailu onnistuu mainissa, aiemmin int.
                                   {"ALL_PLAYERS", 1}, {"PLAYER", 2},   //int lukua kasvatetu yhdellä helpomman vertailun vuoksi mainissa, todellisuudessa parametreja yksi merkittyä vähemmän
                                   {"ADD_GAME", 2}, {"ADD_PLAYER", 4},
                                   {"REMOVE_PLAYER", 2}};

const map<string, string> KUTSUT = {{"ALL_GAMES", "pelien_tulostus"}};
int main()
{
    //tiedostorakenne
    PELIEN_TIETOTYYPPI pelit_map;
    if (!tiedoston_avaus(pelit_map))
        return 1;

    while (true)
    {
        string rivi;
        //string sana;
        vector <string> apuvektori;
        cout << "games> ";
        getline (cin, rivi);
        apuvektori = split(rivi, ' ');      // split pätkii rivin sanoiksi
        string komento_isolla = "";
        for (auto merkki : apuvektori.at(0))
        {
            komento_isolla += toupper(merkki);
        }
        if (komento_isolla == "QUIT")
            return EXIT_SUCCESS;
        else if (KOMENTO_TARKISTUS.find(komento_isolla) != KOMENTO_TARKISTUS.end() //komennon ja parametrimäärän oikeellisuus tarkistetaan
                && apuvektori.size() >= KOMENTO_TARKISTUS.at(komento_isolla))    //jos syötteenä annettu komento löytyy komennot-vakiosta ja vektorin koko väh.hkuormaa vastaava
        {
            //parametrina pelit_map, komento ja koko apuvektori josta voi kussakin funktiossa valita tarvittavan määrän parametreja
            funktio_kutsut(pelit_map, komento_isolla, apuvektori);

        }
        else
        {
            cout << VIRHE_TEKSTI << endl;    //Jos itse komento ei ole hyväksytty/ parametreja liian vähän: Error: Invalid input.
            continue;
        }



    }
    //TEKEMÄSSÄ: Yleistä komennon tarkistusta, jotta lyhyellä koodilla saan tarkistettua parametrien riittävän määrän ja välitettyä funktiokutsun ja parametrit funktioon.
    //Komennoissa sallitaan sekä pienet että isot kirjaimet. (Tässä voit käyttää char-tyypin toupper-funktiota.
    //Ennen kuin vertaat käyttäjän antamaa syötettä esim. sanaan QUIT, muuta syötteessä olevan komennon kaikki kirjaimet isoiksi.)

    //Kullakin komennolla on 0-3 parametria. Jos parametreja on liian vähän, ohjelma antaa virheilmoituksen HUOM!!
    //ylimääräisistä parametreista ei välitetä

    //isot kirjaimet komennossa vertailuksi







    return EXIT_SUCCESS;
}

//1 commit tiedoston luku ja ilmoistukset
