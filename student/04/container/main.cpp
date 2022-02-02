#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>    //find:a varten

//Funktio read_integers on osittain toteutettu. Jatka toteutus valmiiksi.
//Funktio antaa käyttäjän syöttää niin monta lukua kuin jälkimmäinen parametri määrää,
//ja tallentaa luvut ensimmäisenä parametrina olevaan vektoriin. (HUOM! Pohdi myös, miksi tehtävänannon laatija
//on päättänyt välittää vektorin parametrina eikä paluuarvona.)
void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}

// TODO: Implement your solution here


//Funktio same_values palauttaa totuusarvon, joka kertoo, ovatko kaikki vektorissa olevat luvut samoja.
bool same_values(std::vector< int > vektori)
{
    for (int vektorin_alkio : vektori)
    {
        int vertailu = vektori.at(0);
        if (vektorin_alkio == vertailu)
            continue;
        else
            return false;


    }
    return true;

}

//Funktio is_ordered_non_strict_ascending palauttaa totuusarvon, joka kertoo, ovatko vektorissa olevat
//luvut ei-tiukassa nousevassa suuruusjärjestyksessä (identtiset arvot sallitaan).
bool is_ordered_non_strict_ascending(std::vector <int> vektori)
{
    int pituus = vektori.size();
    for (int indeksi = 0; indeksi < pituus; ++indeksi)
    {
        if (indeksi == 0)
            continue;
        else if (vektori.at(indeksi) >= vektori.at(indeksi-1))
            continue;
        else
            return false;
    }
    return true;
}

//Funktio is_arithmetic_series palauttaa totuusarvon, joka kertoo, muodostavatko vektorissa olevat
//luvut aritmeettisen lukusarjan. (Sarja on aritmeettinen, jos sen peräkkäisten termien erotus on vakio.)

bool is_arithmetic_series(std::vector <int> vektori)
{
    int pituus = vektori.size();
    int ekojen_erotus = vektori.at(1) - vektori.at(0);
    for (int indeksi = 0; indeksi < pituus; ++indeksi)
    {
        if (indeksi == 0)
            continue;
        else if (vektori.at(indeksi) - vektori.at(indeksi-1) == ekojen_erotus)
            continue;
        else
            return false;
    }
    return true;
}

//Funktio is_geometric_series palauttaa totuusarvon, joka kertoo, muodostavatko vektorissa olevat luvut geometrisen lukusarjan.
//(Sarja on geometrinen, jos sen peräkkäisten termien suhdeluku on vakio. Kokonaislukusarjalla tämä suhdeluku on rationaaliluku,
//jolloin pelkistä nollista koostuvaa sarjaa ei pidetä geometrisena.)

bool is_geometric_series(std::vector <int> vektori)
{
    int nolla = 0;
    if (std::count(vektori.begin(), vektori.end(), nolla))      //TÄÄ ON HYVÄ, MYÖS FIND TARJOLLA MUT SIIHEN LOPPUUN JOKU !=vektori.end
            return false;
    int pituus = vektori.size();
    int kerroin = vektori.at(1)/vektori.at(0);

    for (int indeksi = 0; indeksi < pituus; ++indeksi)
    {
        //if (vektori.at(indeksi) == 0)  //heitto
          //  return false;

        if (indeksi == 0)
            continue;

        else if (vektori.at(indeksi)/kerroin == vektori.at(indeksi-1))
            continue;
        else
            return false;

    }
   return true;
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
