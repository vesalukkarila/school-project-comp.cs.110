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

unsigned long int laskenta(int t, int n)
{
    unsigned long int totaalinkertoma = kertomafunktio (t);
    unsigned long int os_sulkeet = kertomafunktio (t-n);
    unsigned long int nostettujenkertoma = kertomafunktio (n);
    return totaalinkertoma/(os_sulkeet * nostettujenkertoma);

}

int main()
{
    int totaalimr = 0;
    int nostetut = 0;
    cout << "Enter the total number of lottery balls: ";
    cin >> totaalimr;
    cout << "Enter the number of drawn balls: ";
    cin >> nostetut;

    if (totaalimr >0 and nostetut > 0 and nostetut <= totaalimr)
    {
        unsigned long int tulos = laskenta (totaalimr, nostetut);
        cout << "The probability of guessing all " << nostetut << " balls correctly is 1/" << tulos << endl;
    }

    else if (totaalimr <= 0 or nostetut <= 0)
        cout << "The number of balls must be a positive number." << endl;

    else if (nostetut > totaalimr)
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;

    return 0;
}


//mitkä kaikki pitää olla unsigned long int????
