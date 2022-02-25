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
#include <set>
#include <utility>      //pair
#include <algorithm>    //sort

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

//ALL_GAMES komento VALMIS
void pelien_tulostus(PELIEN_TIETOTYYPPI const& pelit_map)
{
    //VALMIS
    cout << "All games in alphabetical order:" << endl;
    for (auto tietopari : pelit_map)
        cout << tietopari.first << endl;
}



//GAME komento tulostaa pelin pisteet ja pelaajat suuruus- ja aakkosjärjestyksen mukaisesti. Ei palauta tai muuta mitään.
void pelin_tiedot (PELIEN_TIETOTYYPPI const& pelit_map, vector<string> const& apuvektori)
{
    string pelin_nimi = apuvektori.at(1);
    //mikäli peliä ei löydy tietorakenteesta, annetaan virheilmoitus ja poistutaan funktiosta
    if (pelit_map.find(pelin_nimi) == pelit_map.end())
    {
        cout << "Error: Game" << EI_LOYDY_TEKSTI << endl;
        return;
    }

    cout << "Game " << apuvektori.at(1) << " has these scores and players, listed in ascending order:" << endl;

    //map:n avain-arvo alkiot lisätään päinvastaisessa järjestyksessä apusetti:n
    //jolloin ne ovat automaattisesti suuruusjärjestyksessä pisteiden mukaan
    //ja aakkojärjestyksessä mikäli pisteet ovat yhtäsuuret
    set <pair<int, string>> apusetti;

    for (auto tietopari : pelit_map.at(pelin_nimi))
    {
        pair <int, string> apupair = make_pair(tietopari.second, tietopari.first);
        apusetti.insert(apupair);
    }

    //laskuri ensimmäisen parin käsittelemiseksi
    int laskuri = 0;
    //ja pisteet_setti aiempien pisteiden vertailua varten
    set<int> pisteet_setti;
    for ( auto pari : apusetti)
    {
     // Tulosta piste ja nimi jos enimmäinen alkio
     if (laskuri == 0)
     {
         cout << pari.first << " : " << pari.second;
         laskuri++;
         pisteet_setti.insert(pari.first);  //lisätään pisteet vertailua varten
         continue;
     }
     // Tulosta pilkku ja nimi jos pisteet samat kuin aiemmalla
     else if (pisteet_setti.find(pari.first) != pisteet_setti.end())
     {
         cout << ", " << pari.second;
     }
     else
     {
        cout << endl;
        cout << pari.first << " : " << pari.second;     }

     }
     cout << endl;
}

//ALL_PLAYERS komento VALMIS
void kaikki_pelaajat(PELIEN_TIETOTYYPPI const& pelit_map)
{
    set <string> apusetti;
    for (auto ulompi_pari : pelit_map)
        for (auto sisempi_pari : pelit_map.at(ulompi_pari.first))
            apusetti.insert(sisempi_pari.first);
    cout << "All players in alphabetical order: " << endl;
    for (auto alkio : apusetti)
        cout << alkio << endl;

}

//PLAYER komento kaikki pelaajan pelaamat pelit VALMIS
void pelaajan_pelit (PELIEN_TIETOTYYPPI const& pelit_map, vector<string> apuvektori)
{
    set <string> pelisetti;
    string pelaaja = apuvektori.at(1);
    for (auto ulompi_pari : pelit_map)
    {
        if (pelit_map.at(ulompi_pari.first).find(pelaaja) != pelit_map.at(ulompi_pari.first).end())
        {
            pelisetti.insert(ulompi_pari.first);
        }
    }
    if (pelisetti.empty())
        {
            cout << "Error: Player" << EI_LOYDY_TEKSTI << endl; //lähinnä treenin vuoksi
            return;
        }
    cout << "Player " << apuvektori.at(1) << " plays the following games:" << endl;       //esimerkissä playEs
    for (auto alkio : pelisetti)
        cout << alkio << endl;
}


//KOMENTOJEN PERUSTEELLA FUNKTIOIDEN KUTSU TÄSTÄ FUNKTIOSTA, JOTTEI MAIN TÄYTY
void funktio_kutsut (PELIEN_TIETOTYYPPI& pelit_map, string const& komento_isolla, vector<string> const& apuvektori)//pelit_map vain viitteenä, koska sitä muokataan
{
    if (komento_isolla == "ALL_GAMES")
        pelien_tulostus(pelit_map);
    else if (komento_isolla == "GAME")
        pelin_tiedot(pelit_map, apuvektori);

    else if (komento_isolla == "ALL_PLAYERS")
        kaikki_pelaajat(pelit_map);

    else if (komento_isolla == "PLAYER")
        pelaajan_pelit(pelit_map, apuvektori);

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
    //TEKEMÄSSÄ:




    return EXIT_SUCCESS;
}

//1 commit tiedoston luku ja ilmoistukset
//2 COMMIT mainissa komennon ja parametrien tarkistus ja funktio_kutsut valmis


//omia testejä...
//for (auto tietopari : pelit_map)
//{
 //   cout << tietopari.first << endl;
  //  for(auto sisempipari :  pelit_map.at(tietopari.first))
    //    cout << sisempipari.first << endl;
