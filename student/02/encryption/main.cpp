#include <iostream>
#include <cctype>

using namespace std;


int pienaakkoset(string mjono)
{

    int lkm = mjono.size();
    for (int laskuri = 0; laskuri < lkm; laskuri++)
    {
        if (islower(mjono.at(laskuri)))
        {   cout << "Oikein" << endl;
                continue;
        }
        else
        {
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return 1;
        }

        return 0;

    }
}


int kaikkipienaakkoset(string mjono)
{

    for (char pienaakkonen = 'a'; pienaakkonen < 'z'; ++pienaakkonen)
    {
        string::size_type lukuarvo = 0;
        lukuarvo = mjono.find(pienaakkonen);
        if (lukuarvo == string::npos)
        {
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            return 1;
        }


    }

}


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
        return EXIT_FAILURE;           //Tämä tarkista varmaan sama kuin return 1
    }

    int eka = pienaakkoset(annettukoodirivi);
    if (eka == 1)
        return EXIT_FAILURE;

    int toinen = kaikkipienaakkoset(annettukoodirivi);
    if (toinen == 1)
        return EXIT_FAILURE;


    return 0;
}


//Merkkijonon pitää olla 26 merkkiä pitkä. Jos ei ole,
//tulostetaan virheilmoitus: "Error! The encryption key must contain 26 characters."    DONE!!!!

//Merkkijono saa sisältää vain anglisia pienaakkosia, eli merkkejä 'a' - 'z'.   APUFUNKTIO 1 TAI METODI
//Jos merkkijono sisältää jotain muuta, tulostetaan virheilmoitus:              for alkio in mjono, if islower(alkio) conitnue else...
//"Error! The encryption key must contain only lower case characters."          for alkio in mjono, if alkio in verrokki
                                                                                //KATO C++ KIRJASTOT!! for alkio in mjono
//Merkkijonon pitää sisältää KAIKKI angliset pienaakkoset.                      APUFUNKTIO 2
//Jos ei sisällä, tulostetaan virheilmoitus:                                    for alkio in verrokki, if alkio not in mjono
//"Error! The encryption key must contain all alphabets a-z."                   tai for alkio in verrokki, mjono.find(alkio)
                                                                                // jos ois sorted niin sais aakkosjärjestykseen,
//Ohjelman suoritus loppuu paluuarvolla EXIT_FAILURE välittömästi virheilmoituksen  KATO C++ KIRJASTOT!!
//tulostamisen jälkeen, eli ohjelma voi yhdellä suorituskerralla tulostaa vain yhden virheilmoituksista.

//Kun ohjelma on saanut avaimen luettua ja tarkistettua, se kysyy käyttäjältä sanaa, jonka käyttäjä tahtoo salata,
//kehotteella: "Enter the text to be encrypted: " ja lukee tämän jälkeen yhden merkkijonon salattavaksi tekstiksi.

//Salattavasta merkkijonosta tarkistetaan, että se sisältää vain anglisia pienaakkosia. Jos merkkijono sisältää
//jotain muuta, tulostetaan virheilmoitus:                                      APUFUNKTIO 1 TAI METODI
//"Error! The text to be encrypted must contain only lower case characters."
//ja ohjelman suoritus lopetetaan paluuarvolla EXIT_FAILURE.
