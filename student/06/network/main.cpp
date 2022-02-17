#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

using mapintietotyyppi = unordered_map <string, vector<string>> ;

void store (string id1, string id2, mapintietotyyppi& mapisto)
{
    if (mapisto.find(id1) == mapisto.end()) //jos avain ei löydy mapista..
    {
        mapisto.insert({id1, {}});      //luo avaimen ja alustaa vektorin tyhjäksi
    }
    mapisto.at(id1).push_back(id2);     // joka tapauksessa luo uuden avain-arvo parin

}

void print (string id, mapintietotyyppi const& mapisto, string tulostuspisteet = "")
{
//triviaalitapaus
    if (mapisto.find(id) == mapisto.end()   //jos ei avaimena tai on hkuormana muttei jälkeläisiä
            or mapisto.at(id).empty())
    {
        cout << tulostuspisteet << id << endl;
    }
    //yleistapaus
    else
    {
        cout << tulostuspisteet << id << endl;
        vector<string>::const_iterator iter = mapisto.at(id).begin();
        for (;iter != mapisto.at(id).end(); ++iter)
        {

            print (*iter, mapisto, tulostuspisteet + ".."); //iterillä osoitetaan tietoon joten *, kutsutaan joka alkiolla printtiä

        }
    }
}
//Jos henkilölle ei ole kirjattu värvättyjä tai henkilöä ei ole kirjattu ollenkaan, tulostetaan vain hänen tunnisteensa.
void count (string id, mapintietotyyppi const& mapisto, int& laskuri)
{

    //triviaalitapaus
    if (mapisto.find(id) == mapisto.end())
    {
        laskuri +=0;
    }
    else
    {
        vector<string>::const_iterator iter = mapisto.at(id).begin();
        for (; iter != mapisto.at(id).end(); ++iter)
        {
            laskuri += 1;
            count(*iter, mapisto, laskuri);
        }

    }
}

void depth (string id )
{

}

int main()
{
    // TODO: Implement the datastructure here       //TIETORAKENNE TÄHÄN
    unordered_map <string, vector<string>> mapisto;


    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);        //stringrivi tulee funkusta vektoriin jaettuina takaisin

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!        //STORE TÄHÄN 2 PARAMETRIA
            store(id1, id2, mapisto);

        }



        else if(command == "P" or command == "p")
        {
            string pisteet = "..";
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!        //PRINT TÄHÄN

            print(id, mapisto);

        }


        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!        //COUNT TÄHÄN
            int laskuri = 0;
            count(id, mapisto, laskuri);
            cout << laskuri << endl;


        }

        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!        //DEPTH TÄHÄN

        }






        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
