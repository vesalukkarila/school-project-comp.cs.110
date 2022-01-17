#include <iostream>

using namespace std;

int main()
{
    double lampotila = 0;
    cout << "Enter a temperature: ";
    cin >> lampotila;
    double fahrenheit = (lampotila * 1.8) +32;
    double celsius = (lampotila - 32) / 1.8;
    cout << lampotila <<" degrees Celsius is " << fahrenheit <<" degrees Fahrenheit" << endl;
    cout << lampotila <<" degrees Fahrenheit is " << celsius <<" degrees Celsius" << endl;


    return 0;
}
