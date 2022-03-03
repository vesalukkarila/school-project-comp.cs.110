#include "cards.hh"
#include <iostream>
#include <string>

using namespace std;

int main() {
    cout << "constructor" << endl;
    Cards deck;

    int n = 0;
    cout << "Enter amount of test cards: ";
    cin >> n;

    cout << endl << "print_from_top_to_bottom (deck is empty)" << endl;
    deck.print_from_top_to_bottom(cout);

    cout << endl << "add * n" << endl;
    for(int i = 0; i < n; i++) {
        deck.add(i);    //add metodia kutsutaan i:llä(arvoilla 0,1,2,3,4) eli  n (5) kertaa. add luo uusia dynaamisia muuttujia, 4 jää top eli ensimmäiseksi
    }


    cout << endl << "print_from_top_to_bottom" << endl;
    deck.print_from_top_to_bottom(cout);        //printtaa metodissa alusta loppuun alkiot

    cout << endl << "bottom_to_top * 2" << endl;
    deck.bottom_to_top();                       //siirtää viimeisen ensimmäiseksi, eli pohjalta päälle
    deck.bottom_to_top();

    cout << endl << "print_from_top_to_bottom" << endl;
    deck.print_from_top_to_bottom(cout);        //tulostus ensimmäisestä viimeiseen, alusta loppuun


    cout << endl << "top_to_bottom * 1" << endl;
    deck.top_to_bottom();                       //siirtää ekan viimeiseksi, eli alusta loppuun


    cout << endl << "print_from_top_to_bottom" << endl;
    deck.print_from_top_to_bottom(cout);




    cout << endl << "print_from_bottom_to_top" << endl;
    deck.print_from_bottom_to_top(cout);        //INNOKKAIMMILLE

/*

    cout << endl;
    int value = 0;
    while(deck.remove(value)) {
        cout << "remove " << value << endl;
    }

*/
    cout << endl << "destructor" << endl;
    return EXIT_SUCCESS;
}
