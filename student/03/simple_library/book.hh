#ifndef BOOK_HH
#define BOOK_HH
#include "date.hh"                                //#include "Date" ??? Minkä takia!
#include <iostream>                                 //mitä tämä teki
#include <string>                                   // ja tämä?
using namespace std;                            //mitä tämän käytöstä sanottiin

class Book
{
public:
    //constructor
    Book(string const& tekijat, string const& teos);       //const ja &, kato cpp

    //metodit..
    bool loan(Date& olio);       //muuttaa lainaus&palautuspvm&availability attribuutteja
    void print() const;            // tutkii ei muuta jäsenmuuttujien arvoja
    void renew();               //muuttaa palautuspäivämäärä attribuuttia
    void give_back();           //muuttaa lainaus&palautsvpm&availability attribuutteja


private:
    //attribuutit..
    string tekijaattr_;
    string teosattr_;
    char availabiltyattr_;  //'y' tai 'n'
    string olioattr_;          //epävarma miten tämä attribuutiksi, voisko olla stringina? sijoittais olion string muuttujan arvoksi koska nyt olion arvoksi pitäis asettaa jtn cpp:sa
                    //lainaus ja palautuspvm pitäisi vielä jotenkin saada, date.print ja date.advance
                    // ja date:lla attribuutit day_ month_ ja year_
                    //date:ssa on vain nykyisen päivän muutto, palautuspvm ei tallennu mihinkään, pitäskö kumpikin olla attribuuttina Book:ssa
                    // jos palautuspvm ois oma Date olio niin daten advance ja print metodeja vois hyödyntää renew funktiossa
                    //muuttamaan palautuspvm 28vrk eteenpäin
    string lainausattr_;        //jos näihin tallentais sen mitä se tulostaa..? mut palautusta pitäs pystyä muuttaa, hmm..
    string palautusattr_;       //oisko joku muu kuin string tietotyyppi
};

#endif // BOOK_HH
