#include <iostream>

using namespace std;

int main()
{

    int luku = 0;
    cout << "Enter a positive number: ";
    cin >> luku;


    int kertoja1 = 0;
    int kertoja2 = 100;
    int luku1 = 0;
    int luku2 = 0;

    if (luku <= 0)
    {
        cout << "Only positive numbers accepted" << endl;

    }
    else
    {
        luku1 = luku / 2;
        if (luku1 * luku1 == luku )
        {
            cout << luku << " = " << luku1 << " * " << luku1 << endl;
        }



    }
    return 0;
}
