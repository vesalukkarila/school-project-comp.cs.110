#include "giraffe.hh"

Giraffe::Giraffe() : Mammal()   //tämä toimi ilman että kutsuin mammalin rakentajaa, mielestäni se kuitenkin pitää tehdä
{                               //mammal kutsuu animalin rakentajaa kipkop äänellä

}

void Giraffe::make_noise(std::ostream &output)
{
    output << "Ori ori ori!" << std::endl;
}
