#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

int main()
{
    string tiedosto;
    cout << "Input file: ";
    getline(cin, tiedosto);     // sijoitetaan syöte muuttujaan tiedosto

    ifstream avausolio(tiedosto);   //esitellään tiedostoolio joka avaa muuttujaan sijoitetun tiedoston
    if (not avausolio)
    {
        cout << "Error! The file " << tiedosto << " cannot be opened." << endl;
        avausolio.close();
        return 1;
    }

    else
    {
        string rivi;
        string pisteet;
        int luku = stoi(pisteet);
        map<string, int> mapisto;
        //mapisto.insert({nimi, pisteet})
        //erottelu : kohdalta tiedostoa lukiessa jos onnistuu, tarkistus löytyykö mapistosta,
        //jos löytyy hyötykuorman kasvatus suoraan mapistoon
        //jos ei insertillä uusi avain-hyötykuorma pari
        while (getline(avausolio, rivi, ':'))
        {
            cout << rivi;
            getline(avausolio, pisteet);
            cout <<  " ja " << pisteet << endl;

            if (mapisto.find(rivi) != mapisto.end())    //eli jos löytyy sanakirjasta
                mapisto.at(rivi) += luku;
            else                                        //jos ei löydy sanakirjasta, lisätään uutena parina
                mapisto.insert({rivi, luku});

        }
        }

    avausolio.close();

    return 0;
}
