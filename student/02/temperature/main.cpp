#include <iostream>

using namespace std;

int main()
{
    double lampotila = 0;
    cout << "Enter a temperature: "<< endl;
    cin >> lampotila;
    double celsius = (lampotila - 32) / 1.8;
    cout << lampotila <<" degrees Fahrenheit is " << celsius <<" degrees Celsius" << endl;


    return 0;
}
