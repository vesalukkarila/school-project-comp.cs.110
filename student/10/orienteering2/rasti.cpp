
#include "rasti.hh"

// Luokan rakentaja
Rasti::Rasti(string nimi, int x, int y, int korkeus, char tunnus):
    nimi_(nimi), x_(x), y_(y), korkeus_(korkeus), tunnus_(tunnus)
{

}
// Palauttaa olion attribuuttina olevan tunnus-merkin
// Ei parametreja
char Rasti::hae_tunnus()
{
    return tunnus_;
}


