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
#include <fstream>
#include<cctype>
#include<map>
#include<algorithm>
#include <set>

using namespace std;
using rakenne = map<string, map<string, int>>;

const map<string, unsigned int> KOMENNOT = {{"QUIT", 1} , {"ALL_GAMES", 1}, {"GAME",2}, {"ALL_PLAYERS",1},
                                   {"PLAYER",2}, {"ADD_GAME",2}, {"ADD_PLAYER",4 },{"REMOVE", 2}};

// Casual split func, if delim char is between "'s, ignores it.
std::vector<std::string> split( const std::string& str, char delim = ';' )
{
    std::vector<std::string> result = {""};
    bool inside_quatation = false;
    for ( auto current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quatation = not inside_quatation;
        }
        else if ( current_char == delim and not inside_quatation )
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

bool rivit_kunnossa(vector<string> v)
{
    return v.size() == 3 && !v.at(0).empty() && !v.at(1).empty();
}

bool onko_komento_ok(string nimi)
{
    string nimi_isona;
    for ( auto c : nimi)    //Muutetaan pelin nimi isoksi
    {
        nimi_isona += toupper(c);
    }
    if (KOMENNOT.find(nimi_isona) != KOMENNOT.end())    //jos löytyy KOMENNOISTA
        return true;
    return false;
}

bool onko_parametrit_ok(vector<string> vektori)
{
    string peli_isolla = "";
    for (auto c : vektori.at(0))
            peli_isolla += toupper(c);
    if (KOMENNOT.at(peli_isolla) <= vektori.size())   //jos hyötykuorma  <= vektorin koko
        return true;
    return false;
}

void all_games(rakenne const& mapisto)
{
    cout << "All games in alphabetical order:" << endl;
    for (auto tietopari : mapisto)
        cout << tietopari.first << endl;
}

void game(rakenne mapisto, vector<string> syote_vektori)
{
    string peli = syote_vektori.at(1);
    if (mapisto.find(peli) == mapisto.end()) //Jos pelin nimeä ei löydy tietorakenteesta
    {
        cout << "Error: Game could not be found." << endl;
        return;
    }
    cout << "Game " << peli << " has these scores and players, listed in ascending order:" << endl;
    //PIsteet settiin ja loopissa vertailu
    set<int> apusetti;
    for (auto tietopari : mapisto.at(peli))
    {
        apusetti.insert(tietopari.second);
    }
    for ( auto luku : apusetti)
    {
        int laskuri = 0;
        for ( auto tietopari : mapisto.at(peli))
        {
            if (tietopari.second == luku && laskuri == 0)
            {
                cout << tietopari.second << " : " << tietopari.first;
                ++laskuri;
            }
            else if (tietopari.second == luku && laskuri > 0)
                cout << ", " << tietopari.first;

        }
        cout << endl;
    }
}

void all_players(rakenne mapisto)
{
    cout << "All players in alphabetical order:" << endl;
    set<string> apusetti;
    for ( auto tietopari : mapisto)
    {
        for (auto sisempipari : tietopari.second)
        {
            apusetti.insert(sisempipari.first);
        }
    }
    for (auto alkio : apusetti)
        cout << alkio << endl;
}

void player(rakenne mapisto, vector<string> syote_vektori)
{
    string pelaaja = syote_vektori.at(1);
    set<string> apusetti;
    for (auto ulompi : mapisto)
    {
        if (ulompi.second.find(pelaaja) != ulompi.second.end())
            apusetti.insert(ulompi.first);
    }
    if (apusetti.empty())
    {
        cout << "Error: Player could not be found." << endl;
        return;
    }
    cout << "Player " << pelaaja << " playes the following games:" << endl;
    for (auto alkio : apusetti)
        cout << alkio << endl;
}

void add_game(rakenne& mapisto, vector<string> syote_vektori)
{
    // jos jo olemassa
    string peli = syote_vektori.at(1);
    if (mapisto.find(peli) != mapisto.end())
    {
        cout << "Error: Already exists." << endl;
        return;
    }
    mapisto.insert({peli, {}});
    cout << "Game was added." << endl;
}

void add_player(rakenne& mapisto, vector<string> syote_vektori)
{
    string peli = syote_vektori.at(1);
    string pelaaja = syote_vektori.at(2);
    int pisteet = stoi(syote_vektori.at(3));

    //Jos peliä ei olemassa
    if (mapisto.find(peli) == mapisto.end())
    {
        cout << "Error: Game could not be found." << endl;
        return;
    }
    //Jos pelaaja jo olemassa, pistepäivitys
    else if (mapisto.at(peli).find(pelaaja) != mapisto.at(peli).end())
    {
        mapisto.at(peli).at(pelaaja) = pisteet;
    }
    // pelaajaa ei olemassa ennestään
    else
        mapisto.at(peli).insert({pelaaja, pisteet});
    cout << "Player was added." << endl;

}

void remove(rakenne& mapisto, vector<string> syote_vektori)
{
    //pelaaja ei löydy

    // pelaaja löytyy ja poistetaan

    string pelaaja = syote_vektori.at(1);
    int laskuri = 0;
    set<string> apusetti;
    for ( auto peli : mapisto)
    {
        if ( peli.second.find(pelaaja) != peli.second.end())
        {
            ++laskuri;
            apusetti.insert(peli.first);
        }
    }

    if (laskuri == 0)
    {
        cout << "Error: Player could not be found." << endl;
        return;
    }
    for (auto a : apusetti)
        mapisto.at(a).erase(pelaaja);
    cout << "Player was removed from all games." << endl;
}

int main()
{
    //MUUTTIN TIETORAKENTEESSA PELI:PELAAJA:PISTEET
    //jos löytyy muuta kuin määritelty
    string tiedosto;
    cout << "Give a name for input file: ";
    getline(cin, tiedosto);
    ifstream tiedoston_avausolio(tiedosto);
    if(!tiedoston_avausolio)
    {
        cout << "Error: File could not be read." << endl;
        return 1;
    }

    map<string, map<string, int>> mapisto;
    string rivi;
    while (getline(tiedoston_avausolio, rivi))  //käsitellään yhtä riviä tiedostosta kunnes rivit loppuu
    {
        vector<string> rivivektori = split(rivi);
        if (!rivit_kunnossa(rivivektori))
        {
            cout << "Error: Invalid format in file." << endl;
            return 1;
        }

        //nyt rivi tiedot ovat vektorissa ja siinä on 3 alkiota, pelin, pelaaja, pisteet
        string peli_pienella = rivivektori.at(0);
        string pelaaja = rivivektori.at(1);
        int pisteet = stoi(rivivektori.at(2));
        if ( mapisto.find(peli_pienella) == mapisto.end() )
        {
            mapisto.insert({peli_pienella, {}});
        }
        mapisto.at(peli_pienella).insert({pelaaja, pisteet});
        //nyt ne on tallennettu tietorakenteeseen

    }

    tiedoston_avausolio.close();

    //Itse käli looppi
    while (true)
    {

        string syote;
        cout << "games> ";
        getline(cin, syote);
        vector<string> syote_vektori = split(syote, ' ');
        if (!onko_komento_ok(syote_vektori.at(0)) || !onko_parametrit_ok(syote_vektori))    //toimii vaikkei param ole
        {
            cout << "Error. Invalid input." << endl;
            continue;
        }
        string kasky = "";
        for (auto c : syote_vektori.at(0))
            kasky += toupper(c);
        if (kasky == "ALL_GAMES")
            all_games(mapisto);
        else if (kasky == "GAME")
            game(mapisto, syote_vektori);
        else if (kasky == "ALL_PLAYERS")
            all_players(mapisto);

        else if (kasky == "PLAYER")
            player(mapisto, syote_vektori);

        else if (kasky == "ADD_GAME")
            add_game(mapisto, syote_vektori);

        else if (kasky == "ADD_PLAYER")
            add_player(mapisto, syote_vektori);

        else if (kasky == "REMOVE")
            remove(mapisto, syote_vektori);

            /*else if (kasky == "")*/

    }


    return EXIT_SUCCESS;
}
