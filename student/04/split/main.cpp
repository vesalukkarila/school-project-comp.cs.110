#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

// Toteuta funktio split, joka jakaa parametrina annetun merkkijonon erotinmerkkien
//kohdalta osiin ja palauttaa osat vector-muuttujaan tallennettuna.

vector <std::string> split(string rivi, char erotin, bool totuusarvo = false)
{
    string::size_type pituus = rivi.length();
    string::size_type indeksi;
    vector<string> vektori;
    vector<char> vektori2;

    string::size_type apuindeksi = 0;
    int apulaskuri = 0;         //mahdollisesti sizetype

    if (totuusarvo == false)
    {
        for (indeksi = 0; indeksi < pituus; ++indeksi)
        {
            if (indeksi == 0 and rivi.at(indeksi) == erotin)
            {   if (rivi.at(indeksi+1) == erotin)
                    vektori.push_back("");  //jos eka erotin ja sen perään erotin, lisä tyhjän vektoriin
                else
                    continue;   //ohitta ekan jos erotin ja jälkimmäinen kirjain
            }
            if (rivi.at(indeksi) == erotin and rivi.at(indeksi-1) == erotin)    //jos erotin ja edeltävä erotin
            {
                vektori.push_back("");

            }
            else if (rivi.at(indeksi) != erotin and indeksi< pituus-1)        //jos kirjain ja ei viimeinen
            {
                if (apulaskuri == 0)  //jos eka kirjain
                {
                    apuindeksi = indeksi;
                    apulaskuri +=1;
                }
                else                  //jos aiempia kirjaimia
                    apulaskuri +=1;

             }


            else if (rivi.at(indeksi) == erotin and apulaskuri>0)              //jos erotin ja apulaskuri>0
            {
                string mjono = rivi.substr(apuindeksi, apulaskuri);
                vektori.push_back(mjono);
                apulaskuri = 0;
            }
            else if (rivi.at(indeksi) != erotin and indeksi == pituus-1 and apulaskuri>1) //jos kirjain ja viimeinen ja edeltäviäkirjaimia
            {
                apulaskuri +=1;
                string mjono = rivi.substr(apuindeksi, apulaskuri);
                vektori.push_back(mjono);
                apulaskuri = 0;
            }
            else if (rivi.at(indeksi) != erotin and indeksi == pituus-1 and apulaskuri==0) // jos kirjain ja viimeinen ja ainoa kirjain
            {
                apulaskuri +=1;
                apuindeksi = indeksi;
                string mjono = rivi.substr(apuindeksi, apulaskuri);
                vektori.push_back(mjono);
                apulaskuri = 0;
            }
        }
    }

    else if (totuusarvo == true)
    {
        for (indeksi = 0; indeksi < pituus; ++indeksi)
        {
          if (rivi.at(indeksi) == erotin and indeksi == 0)                  // jos erotin ja indeksi 0
              continue;
          else if (rivi.at(indeksi) == erotin and rivi.at(indeksi-1) == erotin) //jos erotin ja edellinen erotin, continue
              continue;
          else if (rivi.at(indeksi) != erotin and indeksi< pituus-1)        //jos kirjain ja ei viimeinen
          {
              if (apulaskuri == 0)  //jos eka kirjain
              {
                  apuindeksi = indeksi;
                  apulaskuri +=1;
              }
              else                  //jos aiempia kirjaimia
                  apulaskuri +=1;

           }


          else if (rivi.at(indeksi) == erotin and apulaskuri>0)              //jos erotin ja apulaskuri>0
          {
              string mjono = rivi.substr(apuindeksi, apulaskuri);
              vektori.push_back(mjono);
              apulaskuri = 0;
          }
          else if (rivi.at(indeksi) != erotin and indeksi == pituus-1 and apulaskuri>1) //jos kirjain ja viimeinen ja edeltäviäkirjaimia
          {
              apulaskuri +=1;
              string mjono = rivi.substr(apuindeksi, apulaskuri);
              vektori.push_back(mjono);
              apulaskuri = 0;
          }
          else if (rivi.at(indeksi) != erotin and indeksi == pituus-1 and apulaskuri==0) // jos kirjain ja viimeinen ja ainoa kirjain
          {
              apulaskuri +=1;
              apuindeksi = indeksi;
              string mjono = rivi.substr(apuindeksi, apulaskuri);
              vektori.push_back(mjono);
              apulaskuri = 0;
          }
        }
    }

    return vektori;
}
//erotinmerkin löytäminen, jakaminen osiin ja lisääminen vectoriin jonka palautus (tässä tarkkana, paikallinen muuttuja), tulostus tapahtuu mainissa
//2 versiota, toisessa ei tyhjiä alkioita

//Jos päädyt sellaiseen ratkaisuun, jossa käyt merkkijonon indeksejä läpi toistorakenteessa,
//käytä indeksimuuttujan tietotyyppinä string::size_type, älä int.          //MIKSI?

//lfind + laskuri jota verrataan string pituuteen, toistorakenteessa indeksi kerrallaan, lisäis kaikki vectoriin ja poistais vectorista 2:ssa versiossa
//käy string toistossa läpi ja jos indeksi = erotin ja indeksi-1=erotin niin lisää teksti.at(erotin) vektoriin
int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
