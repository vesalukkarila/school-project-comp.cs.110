#ifndef RASTI_HH
#define RASTI_HH
#include "orienteeringmap.hh"
#include <string>

using namespace std;
class OrienteeringMap;


class Rasti{

public:
    Rasti(string nimi, int x, int y, int korkeus, char tunnus);

    char hae_tunnus();
    void print();   //mahdollisesti turha jos en keksi keinoa käyttää, ei pakollinen



private:

    string nimi_;
    int x_;
    int y_;
    int korkeus_;
    char tunnus_;

};

#endif // RASTI_HH
