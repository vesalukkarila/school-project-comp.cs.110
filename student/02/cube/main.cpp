#include <iostream>

using namespace std;

int main()
{

    int luku = 0;
    cout << "Enter a number: ";
    cin >> luku;

    int kuutio = luku * luku * luku;

    if (kuutio < 0 or kuutio/luku/luku != luku)
    {
        cout << "Error! The cube of "<< luku << " is not " << kuutio << ":" << endl;
    }
    else
    cout << "The cube of " << luku << " is " << kuutio << "." << endl;



    return 0;
}
