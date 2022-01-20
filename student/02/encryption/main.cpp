#include <iostream>

using namespace std;




int main()
{
    string annettukoodirivi = "";
    cout << "Enter the encryption key: ";
    getline (cin, annettukoodirivi);

    string::size_type merkkimr = 0;
    merkkimr = annettukoodirivi.length();
    if (merkkimr != 26)
    {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return 1;
    }


    return 0;
}


//Merkkijonon pitää olla 26 merkkiä pitkä. Jos ei ole,
//tulostetaan virheilmoitus: "Error! The encryption key must contain 26 characters."

//Merkkijono saa sisältää vain anglisia pienaakkosia, eli merkkejä 'a' - 'z'.   APUFUNKTIO 1 TAI METODI
//Jos merkkijono sisältää jotain muuta, tulostetaan virheilmoitus:
//"Error! The encryption key must contain only lower case characters."

//Merkkijonon pitää sisältää KAIKKI angliset pienaakkoset.                      APUFUNKTIO 2
//Jos ei sisällä, tulostetaan virheilmoitus:
//"Error! The encryption key must contain all alphabets a-z."

//Ohjelman suoritus loppuu paluuarvolla EXIT_FAILURE välittömästi virheilmoituksen
//tulostamisen jälkeen, eli ohjelma voi yhdellä suorituskerralla tulostaa vain yhden virheilmoituksista.

//Kun ohjelma on saanut avaimen luettua ja tarkistettua, se kysyy käyttäjältä sanaa, jonka käyttäjä tahtoo salata,
//kehotteella: "Enter the text to be encrypted: " ja lukee tämän jälkeen yhden merkkijonon salattavaksi tekstiksi.

//Salattavasta merkkijonosta tarkistetaan, että se sisältää vain anglisia pienaakkosia. Jos merkkijono sisältää
//jotain muuta, tulostetaan virheilmoitus:                                      APUFUNKTIO 1 TAI METODI
//"Error! The text to be encrypted must contain only lower case characters."
//ja ohjelman suoritus lopetetaan paluuarvolla EXIT_FAILURE.
