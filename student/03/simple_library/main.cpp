#include "date.hh"
#include "book.hh"
#include <iostream>

using namespace std;

int main()
{
    // Creating a date
    Date today(5, 5, 2020);

    // Creating a book
    Book book1("Kivi", "Seitseman veljesta");
    book1.print();              //Kivi : Seitseman veljesta
                                //- available

    // Loaning a book
    book1.loan(today);

    // Two weeks later
    today.advance(14);

    // Trying to loan a loaned book
    book1.loan(today);          //Already loaned: cannot be loaned
    book1.print();              //Kivi : Seitseman veljesta
                                //- loaned: 05.05.2020
                                //- to be returned: 02.06.2020

    // Renewing a book
    book1.renew();
    book1.print();              //Kivi : Seitseman veljesta
                                //- loaned: 05.05.2020
                                //- to be returned: 30.06.2020

    // Returning the book
    book1.give_back();

    // Trying to renew an available book
    book1.renew();              //Not loaned: cannot be renewed
    book1.print();              //Kivi : Seitseman veljesta
                                //- available

    // Loaning again (two weeks later)
    book1.loan(today);          //Kivi : Seitseman veljesta
    book1.print();              //- loaned: 19.05.2020
                                //- to be returned: 16.06.2020

    return 0;
}
