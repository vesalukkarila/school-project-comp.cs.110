#include "orienteeringmap.hh"
#include "rasti.hh"
#include <iostream>

using namespace std;
OrienteeringMap::OrienteeringMap():
    kartta_(), rasti_map_(), reitti_map_()
{

}

//Purkaja kääntää kaikki osoittimet nullptr:n vapauttaen dynaamisesti luodut oliomuuttujat.
OrienteeringMap::~OrienteeringMap()
{
    for (auto sisempi_vektori : kartta_)
    {
        for (auto alkio : sisempi_vektori)
        {
            alkio = nullptr;
        }
    }

}

// Sets the width and height for the map.
//luo vektorinvektoreihin pointterit, shared perhaps
void OrienteeringMap::set_map_size(int width, int height)
{
    for (int l = 0; l < height; ++l)
    {
        vector<shared_ptr<Rasti>> sisempi_vektori; //muutettu normaalipointteri
        for (int p = 0; p < width; ++p)
            //tehdään uusi älykäs osoitin joka osoittaa nullptr ja lisätään sisempään vektoriin
        {
            shared_ptr <Rasti> osoitin = nullptr;   //muutettu normaali pointteri
            sisempi_vektori.push_back(osoitin);

        }
        kartta_.push_back(sisempi_vektori); //lisätään sisempi vektori(jossa osoittimia alkioissa) ulomman vektorin alkioksi
    }
}

// Adds a new point in the map, with the given name, position (x and y
// coordinates), height and marker.
//Entä jos luo rasti-olioita tästä samalla, tarvitaan silti tulostusta varten map?
void OrienteeringMap::add_point(std::string name, int x, int y, int height, char marker)
{

}


// Connects two existing points such that the point 'to' will be immediately after the point 'from' in the route 'route_name'.
// The given route can be either a new or an existing one, if it already exists, the connection between points will be
// updated in the aforementioned way. Returns true, if connection was successful, i.e. if both the points
// exist, otherwise returns false.
//tarkistaa että rastit ovat olemassa, jos ei false OK
//tarkistaa onko reitti jo olemassa, jos on from pitäisi olla viimeisenä hkuormana ja lisää to:n sen perään OK
//jos reitti uusi luo uuden reitin ja lisää hkuormaksi  OK
bool OrienteeringMap::connect_route(std::string from, std::string to, std::string route_name)
{



}

//MAP-KOMENTO Prints the map
void OrienteeringMap::print_map() const
{




}

// ROUTES-KOMENTO , tulostaa reitit aakkostettuna
//TOIMII KATSO KOMMENTTI ALLA
void OrienteeringMap::print_routes() const
{


}

// POINTS-KOMENTO, tulostaa rastit aakkostettuna. Prints all points' names and their markers on the map.
//TOIMII MUTTA PITÄISIKÖ NÄITÄ TIETOJA TULOSTAA TOISESTA LUOKASTA KTS. OHJEET, KUN TÄSSÄ ON MODUULIJAKO AIHEENA
//TULOSTUS LÄHTEE TÄSTÄ LUOKASTA MUTTA HAKEE TIETOJA TOISESTA - LÄPPÄ
void OrienteeringMap::print_points() const
{


}


//ROUTES <ROUTE>-KOMENTO, tulostaa reitin alkuperäisessä muodossa
// Prints points belonging to the given route in the order they are
// in the route.
//HERJAA EXPRESSION RESULT UNUSED, tulostus toimii hyvin silti
void OrienteeringMap::print_route(const std::string &name) const
{


}



// Prints the given route's combined length,
// the length is counted as a sum of the distances of adjacent points.???? ETÄISYYDEN LASKENTA????
void OrienteeringMap::route_length(const std::string &name) const
{

}

// Finds and prints the highest rise in any of the routes after the given
// point.
void OrienteeringMap::greatest_rise(const std::string &point_name) const
{

}
