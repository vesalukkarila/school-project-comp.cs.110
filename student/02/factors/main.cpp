#include <iostream>

using namespace std;

int main()
{

    int luku = 0;
    cout << "Enter a positive number: ";
    cin >> luku;


    int kertoja1 = 0;
    int kertoja2 = 100;

    int k = 1;
    if (luku <= 0)
    {
        cout << "Only positive numbers accepted" << endl;

    }
    else
    {
        for ( k; k < luku/2; ++k )
        {
            if (luku % k == 0)
            {
                if (luku/k - k < kertoja2 - kertoja1 and luku/k - k > 0)
                {
                    kertoja2 = luku/k;
                    kertoja1 = k;
                }
            }
            else
                continue;

        }
        cout << luku << " = " << kertoja1 << " * " << kertoja2 << endl;
    }
    return 0;
}
