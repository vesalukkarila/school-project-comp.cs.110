#include <iostream>

using namespace std;

int main()
{
    double lampotila = 0;
    cout << "Enter a temperature: "<< endl;
    cin >> lampotila;
    double fahrenheit = (lampotila * 1.8) +32;
    cout << lampotila <<" degrees Celsius is " << fahrenheit <<" degrees Fahrenheit" << endl;


    return 0;
}
