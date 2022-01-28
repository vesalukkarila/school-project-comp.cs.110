#include "book.hh"


Book::Book(const string &tekija, const string &teos):                   // täson nyt olio strinmuuttujaan alustettuna
    tekijaattr_(tekija), teosattr_(teos), availabiltyattr_('y'),
    olioattr_(""), lainausattr_(""), palautusattr_("")

{

}

bool Book::loan(Date &olio)
{
    if (availabiltyattr_ == 'y')
        availabiltyattr_ = 'n';

}

void Book::print() const
{

}

void Book::renew()
{

}

void Book::give_back()
{

}
