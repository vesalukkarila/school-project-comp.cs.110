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
    //Tarkistaa että vektorissa on 3 alkiota ja ettei pelin (indeksi 0) tai pelaajan (indeksi 1) kohta ole tyhjä
    return rivivektori.size() == 3
            && !rivivektori.at(0).empty()
            && !rivivektori.at(1).empty();
}

bool tiedoston_avaus (PELIEN_TIETOTYYPPI& pelit_map)
{
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

int main()
{
    //tiedostorakenne
    PELIEN_TIETOTYYPPI pelit_map;
    if (!tiedoston_avaus(pelit_map))
        return 1;


    //omia testejä...
    for (auto tietopari : pelit_map)
    {
        cout << tietopari.first << endl;
        for(auto sisempipari :  pelit_map.at(tietopari.first))
            cout << sisempipari.first << endl;
    }




    return EXIT_SUCCESS;
}
