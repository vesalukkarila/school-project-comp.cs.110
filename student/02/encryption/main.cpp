#include <iostream>
#include <cctype>

using namespace std;


int pienaakkoset(string mjono)
{

    int lkm = mjono.size();
    for (int laskuri = 0; laskuri < lkm; laskuri++)
    {
        if (islower(mjono.at(laskuri)))
                continue;

        else
        {

            return 1;
        }

    }
    return 0;
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
    return 0;
}


void kaanna_salattava(string viesti, string salaus)
{
    string uusimerkki = "";
    string uusimjono = "";
    int merkkilkm = viesti.size();
    for (int laskuri = 0; laskuri < merkkilkm; ++laskuri)
    {
        char merkki;
        merkki = viesti.at(laskuri);
        int merkin_ascii_arvo_eli_kryptauksen_indeksikohta = static_cast<int>(merkki);

        uusimerkki = salaus.at(merkin_ascii_arvo_eli_kryptauksen_indeksikohta-97);
        uusimjono += uusimerkki;

    }

    cout << "Encrypted text: " << uusimjono << endl;
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
    {
        cout << "Error! The encryption key must contain only lower case characters." << endl;
        return EXIT_FAILURE;
    }

    int toinen = kaikkipienaakkoset(annettukoodirivi);
    if (toinen == 1)
        return EXIT_FAILURE;

    string salattava = "";
    cout << "Enter the text to be encrypted: ";
    getline (cin, salattava);
    int kolmas = pienaakkoset(salattava);
    if (kolmas == 1)
    {
        cout << "Error! The encryption key must contain only lower case characters." << endl;
        return EXIT_FAILURE;


    kaanna_salattava(salattava, annettukoodirivi);
    }
    return 0;
}



