#ifndef MAMMAL_HH
#define MAMMAL_HH
#include "animal.hh"

class Mammal : public Animal    //periyttää animal-luokan julkiset metodit
{
public:
    Mammal();
    void suckle(std::ostream& output);
};

#endif // MAMMAL_HH
