#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    cout << "Input file: " ;
    string tiedosto;
    getline (cin, tiedosto);


    cout << "Output file: " ;
    string tulostettava_tiedosto;
    getline (cin, tulostettava_tiedosto);

    ifstream tiedoston_avausolio (tiedosto);

    if (!tiedoston_avausolio)
    {
        cout << "Error! The file not_a_file.input cannot be opened." << endl;
        return 1;
    }

    else
    {
        string rivi;
        int laskuri = 1;
        ofstream kirjoitettava_tiedosto(tulostettava_tiedosto);

        while (getline (tiedoston_avausolio, rivi))
        {
            kirjoitettava_tiedosto << laskuri << " " << rivi << endl;
            ++laskuri;
        }

    }

    tiedoston_avausolio.close();



}
