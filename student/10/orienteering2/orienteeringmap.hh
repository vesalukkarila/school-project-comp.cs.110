/*
#############################################################################
# COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures          #
# Project3: Suunnistus / Orienteering                                       #
# File: orienteeringmap                                                     #
# Description: Datastructure that represents an orienteering map and        #
#        handles information of points and routes                           #
# Notes: * This is a part of an exercise program.                           #
#        * Students aren't allowed to change the public interface!          #
#        * Modifying the private part is allowed (and required).            #
#############################################################################
*/

#ifndef ORIENTEERINGMAP_HH
#define ORIENTEERINGMAP_HH

#include "rasti.hh"

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <iomanip>

using namespace std;

class Rasti;
struct Rastin_tiedot;   //voinee poistaa kunhan siivoaa
using kartan_tietotyyppi = vector < vector < shared_ptr < Rasti >>> ;
using rasti_mapin_tietotyyppi = map<string, Rastin_tiedot>;
using reitti_mapin_tietotyyppi = map<string, vector<string>>;

class Rasti;
//EN TIEDÄ PITÄÄKÖ TÄÄ OLLA TÄSSÄ VAI ENNEN TÄTÄ VAI PRIVATE OSASSA
struct Rastin_tiedot
{
    string rastin_nimi;
    int x;
    int y;
    int korkeus;
    char tunnus;
    shared_ptr<Rastin_tiedot> seuraava;
};


class OrienteeringMap
{
public:
    // Constructor and destructor
    OrienteeringMap();
    ~OrienteeringMap();

    // Sets the width and height for the map.
    void set_map_size(int width, int height);

    // Adds a new point in the map, with the given name, position (x and y
    // coordinates), height and marker.
    void add_point(std::string name, int x, int y, int height, char marker);

    // Connects two existing points such that the point 'to' will be
    // immediately after the point 'from' in the route 'route_name'.
    // The given route can be either a new or an existing one,
    // if it already exists, the connection between points will be
    // updated in the aforementioned way.
    // Returns true, if connection was successful, i.e. if both the points
    // exist, otherwise returns false.
    bool connect_route(std::string from,
                       std::string to,
                       std::string route_name);

    // Prints the map.
    void print_map() const;

    // Prints all routes' names, ordered alphabetically.
    void print_routes() const;

    // Prints all points' names and their markers on the map.
    void print_points() const;

    // Prints points belonging to the given route in the order they are
    // in the route.
    void print_route(const std::string& name) const;

    // Prints the given route's combined length,
    // the length is counted as a sum of the distances of adjacent points.
    void route_length(const std::string& name) const;

    // Finds and prints the highest rise in any of the routes after the given
    // point.
    void greatest_rise(const std::string& point_name) const;

private:
    // Add here attributes and private methods.
    //Lisää attribuutit ja yksityiset metodit
    // At least you need a datastructure for points or routes or for both,
    // containing Point* or Route* objects (pointers).
    //Vähintään tarvitaan tietorakenne joko rasteille tai reiteille tai molemmille (map ja vector ehdokkaina)
    //sisältäen osoittimet joko rasteille tai reiteille
    // Good candidates for such structures are STL maps or vectors.

    kartan_tietotyyppi kartta_;   //SAMA KUIMPI POINTTERI: RASTI WAS NOT DECLARED IN THIS SCOPE
    //vector<vector<Rasti*>> kartta_;  //tehty rasti-luokka mikäli haluaa olioihin viitatat kartasta, muutettu normaalipointteri
    rasti_mapin_tietotyyppi rasti_map_;
    reitti_mapin_tietotyyppi reitti_map_;
    //alla hyötykuormana dynaaminen muuttuja jonka tyyppi rastin_tiedot

};

#endif // ORIENTEERINGMAP_HH
