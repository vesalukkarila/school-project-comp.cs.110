#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <utility>
#include <string>
using namespace std;

int main()
{

    string tiedosto;
    cout << "Input file: ";
    getline(cin, tiedosto);

    string rivi;
    string sana;
    set <string> setti;
    map <string, vector<int>> mapisto;
    vector <int> vektori = {0};
    vector <string> lausevektori;
    int rivilaskuri = 0;

    ifstream tiedostonavausolio(tiedosto);  //rakennetaan ja esitellään tiedostonavausolio ja avataan tiedosto joka parametrina

    if (not tiedostonavausolio) //jos avaus ei onnistu ilmoitus sulku ja poistuminen
    {
        cout << "Error! The file " << tiedosto << " cannot be opened." << endl;
        tiedostonavausolio.close();
        return 1;
    }

    else
    {
        //while (getline(tiedostonavausolio, rivi))
        //for ( int laskuri = 1; getline(tiedostonavausolio, rivi); ++laskuri)
        //while (getline(tiedostonavausolio, rivi))
           // cout << rivi << endl;

        while ( tiedostonavausolio >> sana)
        {
            if (sana.length()<3)
                mapisto.insert({sana+" ", vektori});    //tässä on se lyhyiden sanojen kiertäminen
            else
                mapisto.insert({sana, vektori});
        }

        //setin siirtäminen mappiin
        tiedostonavausolio.close();
        ifstream tiedostonavausolio(tiedosto);  //rakennetaan ja esitellään tiedostonavausolio ja avataan tiedosto joka parametrina

        while (getline(tiedostonavausolio, rivi)) //täsä oli while (getline(tiedostoavausolio, rivi), nyt kaikki kerrala yritys
        {
            rivilaskuri +=1;
            for (auto m : mapisto)
            {
                if (rivi.find(m.first) != string::npos)
                {
                    mapisto[m.first].at(0) +=1;
                    mapisto[m.first].push_back(rivilaskuri);
                }
            }

        }
        //LÖYTÄÄ "A" JA "ON" SANOJEN SISÄLTÄ
        for (auto tietopari : mapisto)
        {
            cout << tietopari.first << " " << tietopari.second.at(0)
            << ": ";

            vector<int>::size_type koko = tietopari.second.size();
            for (vector<int>::size_type indeksi = 1; indeksi < koko; ++indeksi)
            {
                if (indeksi == koko-1)
                    cout << tietopari.second.at(indeksi);
                else
                    cout << tietopari.second.at(indeksi) << ", ";

            }
            cout << endl;
        }

        //for (auto v : lausevektori)
        //{
          //  rivilaskuri +=1;
          //  for (auto m : mapisto)
          //      if ()
        //}

    }


    return 0;
}


