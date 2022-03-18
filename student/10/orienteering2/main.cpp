/* Hitori
*
* Kuvaus:
* Ohjelma lukee syötetiedostosta suunnistuskartan tietoja ja tallentaa
* ne tietorakenteisiin. Käyttäjä voi tehdä seuraavia hakuja tietorakenteista
* seuraavilla komennoilla:
* MAP - koordinaatiston johon rastit merkitty niiden tunnuksilla
* ROUTES - tulostaa kaikki reitit aakkostettuna
* ROUTE <reitti> - tulostaa parametrina annetun reitin rastit
* POINTS - tulostaa kaikki rastit aakkostettuna ja niiden tunnukset
* RISE <rasti> - laskee suurimman nousu parametrina annetulta
* rastilta lähtien kullakin reitillä
* LENGTH <reitti> - tulostaa parametrina annetun reitin pituuden
*
* Komennoissa hyväksytään pienet ja suuret kirjaimet.
* Parametri on annettava samassa muodossa kuin syötetiedostossa.
*
* Ohjelman kirjoittaja
* Nimi: Vesa Lukkarila
* Opiskelijanumero: 150372523
* Käyttäjätunnus: h6vlukka
* E-Mail: vesa.lukkarila@tuni.fi
*/


#include "orienteeringmap.hh"
#include "parser.hh"
#include "cli.hh"
#include "rasti.hh"
#include <iostream>

int main()
{

    std::shared_ptr<OrienteeringMap> routes(new OrienteeringMap);
    std::cout << "Input> ";
    std::string input;
    getline(std::cin, input);
    if( not read_input_from_file(input, routes) )
    {
        return EXIT_FAILURE;
    }
    Cli cli(routes);
    while( cli.exec_prompt() ){ }
    return EXIT_SUCCESS;
}


