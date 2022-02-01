#include "book.hh"
#include <string>
#include <iostream>

using namespace std;

Book::Book(const string &tekija, const string &teos):                   // täson nyt olio strinmuuttujaan alustettuna
    tekijaattr_(tekija), teosattr_(teos), availabilityattr_("yes"),
    olioattr_(), lainausattr_(), palautusattr_()

{

}

void Book::loan(Date olio)
{
    if (availabilityattr_ == "yes")
    {
        availabilityattr_ = "no";

        lainausattr_= olio;
        palautusattr_ = olio;
        palautusattr_.advance(28);

    }
    else
        cout << "Already loaned: cannot be loaned" << endl;
}

//loan metodiin (mikäli kirja on vapaa) tarvitsen today-olion päivämäärän jotta saan lainausattr:n ja palautusattr:n saan kun edistän tätä 28 vrk.
//pitääkö niiden olla omia date luokan olioita, koska hyödynnän dateluokan metodeja?


void Book::print() const
{
    cout << tekijaattr_ << " : " << teosattr_ << endl;
    if (availabilityattr_ == "yes")
    {
        cout << "-available" << endl;
    }

    else
    {
        cout << "- loaned: ";
        lainausattr_.print();
        cout << "- to be returned: ";
        palautusattr_.print();
    }
}

//Varatun kirjan tulostukseen tarvitaan lainaus ja palautuspäivämäärä (attribuutit, eikö? oliokohtainen joihin metodeilla tunkeudutaan).
//tulostetaanko tässä vai kutsutaanko dateluokan printtiä lainaus ja palautusolioilla jotka datetyyppiä
void Book::renew()
{
    if (availabilityattr_ == "yes")
        cout << "Not loaned: cannot be renewed" << endl;
    else
        palautusattr_.advance(28);
}

//Renew funktioon tarvii palautuspvm:n (attribuutti) edistämistä 28 vuorokaudella

void Book::give_back()
{
    if (availabilityattr_ == "no")
        availabilityattr_ = "yes";

}
//availabilityattr_ muutos ja pal&lainausattribuuteille toimet?


//kirjan lainaus ja palautus päivämäärä pitäs saada tallennettua johonkin ja palautuspäivämäärää verrattua today olion päivämäärään
//mikäli  kirja on varattu.
