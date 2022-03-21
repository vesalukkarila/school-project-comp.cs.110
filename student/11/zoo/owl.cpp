#include "owl.hh"

Owl::Owl() : Bird() //kutsuu birdin rakentajaa joka kutsuu animalin rakentajaa "flap flap" parametrilla
{

}

void Owl::hoot(std::ostream &output) const
{
 output << "Hoo hoo!" << std::endl;
}


