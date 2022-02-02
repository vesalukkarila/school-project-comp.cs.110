
#include <iostream>
#include <string>

using namespace std;

int main() {


    string mjono= "a";
    string mjono2 = "b";
    string& viite = mjono;
    cout << mjono << mjono2 << viite << endl;
    mjono2 = viite;
    cout << mjono << mjono2 << viite << endl;

}

//tällä saa tehtyä encryption tehtävän, aakkosjärjestystä ei vielä löytynyt. Apufunktio 1 ja 2 onnistuu.
