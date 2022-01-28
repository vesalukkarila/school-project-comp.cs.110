#ifndef BOOK_HH
#define BOOK_HH
#include "date.hh"                                //#include "Date" ???
#include <iostream>
#include <string>
using namespace std;

class Book
{
public:
    //constructor
    Book(string const& tekija, string const& teos);       //const ja &, kato cpp

    //metodit..
    bool loan(Date& olio);       //parametrina tulee toisen luokan olio. &ainakin mukana, tällöin siirtyy viiteparametrina
    void print() const;
    void renew() const;
    void give_back() const;


private:
    //attribuutit..

};

#endif // BOOK_HH
