#include <iostream>

using namespace std;

int main()
{

    int luku = 0;
    cout << "Enter a positive number: ";
    cin >> luku;


    int kertoja1 = 0;
    int kertoja2 = 100;

    if (luku <= 0)
    {
        cout << "Only positive numbers accepted" << endl;

    }
    else
    {
        for ( int kasvava = 1; kasvava < luku/2; ++kasvava )
        {
            if (luku % kasvava == 0)
            {
                if (luku/kasvava - kasvava < kertoja2 - kertoja1 and luku/kasvava - kasvava > 0)
                {
                    kertoja2 = luku/kasvava;
                    kertoja1 = kasvava;
                }
            }
            else
                continue;

        }
        cout << luku << " = " << kertoja1 << " * " << kertoja2 << endl;
    }
    return 0;
}
