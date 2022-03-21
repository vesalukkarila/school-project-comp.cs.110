#include "cockatoo.hh"

Cockatoo::Cockatoo() : Bird() //lisätty bird-rakentajan kutsu, bird kutsuu animal "Flap flap" parametrilla
{

}

void Cockatoo::sing(std::ostream &output)
{
    output << "Kee-ow kee-ow!" << std::endl;

}
