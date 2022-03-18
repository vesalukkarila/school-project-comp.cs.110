/*
#############################################################################
# COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures          #
# Project3: Suunnistus / Orienteering                                       #
# File: rasti.hh                                                            #
# Description: Rasti-luoka esittelytiedosto                                 #
# Notes: * Luokan olioita luodaan dynaamisesti orienteeringmap.cpp käsin    #
#############################################################################
*/

#ifndef RASTI_HH
#define RASTI_HH
#include <string>

using namespace std;

class Rasti{

public:
    // Rakentaja
    Rasti(string nimi, int x, int y, int korkeus, char tunnus);

    // Huom. Ei purkajaa, koska dynaamisesti luotu ja Orienteeringmap:n purkaja
    // kääntää kaikki osoittimet nullptr:n vapauttaen luodut oliomuuttujat.

    // Palauttaa olion attribuuttina olevan tunnus-merkin
    // Ei parametreja
    char hae_tunnus();

private:

    string nimi_;
    int x_;
    int y_;
    int korkeus_;
    char tunnus_;

};

#endif // RASTI_HH
