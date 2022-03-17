#include "rasti.hh"
#include "orienteeringmap.hh"


//ei pitäis tarvita purkajaa, oliot luodaan dynaamisesti ja orienteeringmap.cpp siirretään koordinaattiosoitin vian nullptr:ksi
Rasti::Rasti(string nimi, int x, int y, int korkeus, char tunnus):
    nimi_(nimi), x_(x), y_(y), korkeus_(korkeus), tunnus_(tunnus)
{

}

char Rasti::hae_tunnus()
{
    return tunnus_;
}

void Rasti::print()
{

}
