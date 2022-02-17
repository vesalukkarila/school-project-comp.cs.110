#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
using namespace std;

int main()
{

    string tiedosto;
    cout << "Input file: ";
    getline(cin, tiedosto);

    string rivi;
    string sana;
    set <string> setti;
    map <string, set<int>> mapisto;
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

   // else
    //{
      //  while ( tiedostonavausolio >> sana)
        //{

          //  mapisto.insert({sana, vektori});    //lisätään mappiin (uniikki) sana ja tyhjä vektori

        //}


       // tiedostonavausolio.close();         //suljen jotta voin loopata uusiksi
       // ifstream tiedostonavausolio(tiedosto);

        while (getline(tiedostonavausolio, rivi))
        {
            rivilaskuri +=1;
            istringstream sanat(rivi); //lisätty
            while(sanat >> sana)                 //for (auto m : mapisto)
               {
                   if (mapisto.find(sana) == mapisto.end()) //if (rivi.find(m.first) != string::npos)  //koska find aloittaa loopin aina kun yksi löytyy
                   {
                       mapisto.insert({sana, {}});         //mapisto[m.first].at(0) +=1;  //vektorin 0-indeksiin lisää yhden esiintymän
                                                            //mapisto[m.first].push_back(rivilaskuri); //vektorin loppuun lisää rivin jolla esiintyy
                   }
                   mapisto.at(sana).insert(rivilaskuri);
               }
        }




        //TULOSTUS osio OK! ei oo enää kun muutti hyötykuorman setiksi
        for (auto tietopari : mapisto)
        {
            vector<int>::size_type koko = tietopari.second.size();

            cout << tietopari.first << " " << koko
            << ": ";

            for (set<int>::iterator iter = tietopari.second.begin(); iter != tietopari.second.end(); ++iter)
            {

                cout << *iter;
                if ((++iter) != tietopari.second.end())
                    cout << ", ";
                else
                    cout << endl;
                iter--;
            }
        }




    return 0;
}


