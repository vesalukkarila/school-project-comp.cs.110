#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    string tiedostonimi;
    string kirjoitettavatiedosto;
    cout << "Input file: ";
    getline (cin, tiedostonimi);
    cout << "Output file: ";
    getline(cin, kirjoitettavatiedosto);
    ofstream tiedostoon_kirjoitus_olio(kirjoitettavatiedosto);
    ifstream tiedosto_olio(tiedostonimi);   //esitellään ifstream-tyyppinen olio, jonka rakentajalle parametrina luettava tiedosto
    if (not tiedosto_olio)
    {
        cout << "Error! The file " << tiedostonimi << " cannot be opened." << endl;
        return 1;
    }
    else
    {

        string rivi;
        int l = 1;
        while (getline(tiedosto_olio, rivi))    //toistorakenteeseen mennään jos tiedostosta saadaan luettua rivi
        {
            tiedostoon_kirjoitus_olio << l <<" " << rivi << endl;
            ++l;
        }
    }
    tiedosto_olio.close();
    tiedostoon_kirjoitus_olio.close();

    return 0;
}

//Toteuta ohjelma, joka lukee tiedoston ja kirjoittaa sen sisällön toiseen tekstitiedostoon siten,
//että jokaisen rivin alkuun on lisätty kyseisen rivin järjestysnumero ja välilyönti.

//OK Tiedoston avaamisen yritys ja ilmoitus jos ei onnistu (ei tarvitse txt päätettä)
// OK Välivaiheena tiedoston lukeminen ja tulostaminen näytölle
//Tulostamisen sijaan kirjoitus toiseen tiedostoon siten että loopissa lisätään rivinumero ja välilyönti
//Kummankin avatun tiedoston sulkeminen lopuksi
