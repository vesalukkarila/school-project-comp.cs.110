#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>

using namespace std;

int main()
{

    string tiedosto;
    cout << "Input file: ";
    getline (cin, tiedosto);
    ifstream tiedostonavausolio(tiedosto);

    if (! tiedostonavausolio)
    {
        cout << "Error! The file not_a_file.txt cannot be opened." << endl;
        return 1;
    }

    string rivi;
    int laskuri = 1;
    map<string, set<int>> mapisto;
    string sana;
    while (getline(tiedostonavausolio, rivi))
    {
        istringstream sanoiksi_pilkkomis_olio(rivi);
        while(sanoiksi_pilkkomis_olio >> sana)
        {
            if (mapisto.find(sana) == mapisto.end())    //jos uusi avain, lisätään tyjällä hyöytkuormalla
            {
                mapisto.insert({sana, {}});
            }
            mapisto.at(sana).insert(laskuri); //Nyt avain on olemassa aina, jten lisätään rivilaskuri hyötykuormasettiin
        }
        ++laskuri;

    }

    for (auto tietopari : mapisto)
    {

        cout << tietopari.first << " " << tietopari.second.size() << ": " ;

        set<int>::iterator iter = tietopari.second.begin();
        set<int>::iterator vika = tietopari.second.end();
        for (iter; iter != vika; ++iter)
        {
            cout << *iter;
            if (iter != --vika )
                cout << ", ";
            ++vika;
        }

        cout<<endl;


    }



    tiedostonavausolio.close();
    return 0;
}
