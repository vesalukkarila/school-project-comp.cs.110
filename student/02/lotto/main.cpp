#include <iostream>

using namespace std;

unsigned long int kertomafunktio (unsigned long int p)
{
    unsigned long int kertoja = 1;
    unsigned long int tulo = 1;
    while (kertoja <= p )
    {
        tulo *= kertoja;
        ++kertoja;
    }

    return tulo;
}

unsigned long int laskenta(unsigned long int t, unsigned long int n)
{
    unsigned long int totaalinkertoma = kertomafunktio (t);
    unsigned long int os_sulkeet = kertomafunktio (t-n);
    unsigned long int nostettujenkertoma = kertomafunktio (n);
    return totaalinkertoma/(os_sulkeet * nostettujenkertoma);

}

int main()
{
    unsigned long int totaalimr = 0;
    unsigned long int nostetut = 0;
    cout << "Enter the total number of lottery balls: ";
    cin >> totaalimr;
    cout << "Enter the number of drawn balls: ";
    cin >> nostetut;

    if (totaalimr >0 and nostetut > 0)
    {
        unsigned long int tulos = laskenta (totaalimr, nostetut);

    }


    return 0;
}


//mitkä kaikki pitää olla unsigned long int????
