#include "orienteeringmap.hh"
#include "rasti.hh"
#include <iostream>
#include <cmath>
#include <set>

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
//OK
void OrienteeringMap::add_point(std::string name, int x, int y, int height, char marker)
{
    if (rasti_map_.find(name) == rasti_map_.end())
    {
        rasti_map_.insert({name, {name, x, y, height, marker, nullptr}});    //nimi avaimena, hkuormana kaikki Rastin_tiedot structissa
    }
    kartta_.at(y-1).at(x-1) = make_shared<Rasti>(name, x, y, height, marker);
    //**TÄMÄ laitetaan kartan pointteri osoittamaan dynaamisesti luotuun rastiolioon
    //tää vois olla myös dynaaminen struct, mutta koska tarvittiin luokka niin päätin laittaa sen tähän
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
    if (rasti_map_.find(from) == rasti_map_.end()   //jos jompikumpi rasteista ei löydy rastimapista - false
            or rasti_map_.find(to) == rasti_map_.end())
    {
        return false;
    }
    if (reitti_map_.find(route_name) == reitti_map_.end())  //jos uusi reitti, JOS dynaamista rakentaa niihin tähän
    {
        reitti_map_.insert({route_name, {from, to}});
        return true;
    }
    else if (reitti_map_.find(route_name) != reitti_map_.end()) //jos reitti jo olemassa eli Olio jo luotu, JA tähän
    {
        if ( reitti_map_.at(route_name).back() == from) //lähtö (from) nykyisen vektorin viimeisenä
        {
            reitti_map_.at(route_name).push_back(to);
            return true;
        }
    }
    return false;   //epävarma true/false, true kohdat mielestäni käsitelty yllä
}


//MAP-KOMENTO, OK
void OrienteeringMap::print_map() const
{
    cout << " ";
    int sarake_leveys = 3;
    //Tulostetaan otsikkorivi, eli x-koordinaatit eli leveys
    //Laskurin rajoittimena sisemmän vektorin alkioiden eli osoittimien määrä
    for (unsigned int laskuri = 1; laskuri <= kartta_.at(0).size(); ++laskuri)
    {
        cout << setw(sarake_leveys) << right << laskuri;
    }
    cout << endl;

    int rivi_nro_leveys = 2;
    int rivi_nro = 1;

    for (auto sisempi_vektori : kartta_)
    {
        cout << setw(rivi_nro_leveys) << right << rivi_nro;
        ++rivi_nro;
        for (auto alkio : sisempi_vektori)
        {
            if (alkio == nullptr)
                cout << setw(sarake_leveys) << right << "."; //tähän jos nullptr tulosta piste, muutoin rastint tunnus
            else
                //**TÄMÄ hakee dynaamisesti luodusta oliosta sen attribuutin olion omalla metodilla
               cout << setw(sarake_leveys) << right << alkio->hae_tunnus();
        }
        cout << endl;
    }
}

// ROUTES-KOMENTO , OK
void OrienteeringMap::print_routes() const
{
    cout << "Routes:" << endl;
    for (auto tietopari : reitti_map_)
    {
        cout << " - " << tietopari.first << endl;
    }

}

// POINTS-KOMENTO, OK
void OrienteeringMap::print_points() const
{
    cout << "Points:" << endl;
    for (auto tietopari : rasti_map_)
    {
        cout << " - " << tietopari.first << " : " << tietopari.second.tunnus << endl;   //tulosta rastin nimi ja tunnus
    }

}


//ROUTES <ROUTE>-KOMENTO, OK
void OrienteeringMap::print_route(const std::string &name) const
{
    if (reitti_map_.find(name) != reitti_map_.end())
    {
        cout << reitti_map_.at(name).at(0) << endl; //tulostaa ekan rastin ilman nuolta
        vector<string>::const_iterator iter = reitti_map_.at(name).begin();
        ++iter;
        for (; iter != reitti_map_.at(name).end(); ++iter)
        {
            cout << " -> " << *iter << endl;
        }
    }
    else
        cout << "Error: Route named " << name << " can't be found" << endl;

}



// Prints the given route's combined length,
// the length is counted as a sum of the distances of adjacent points.???? ETÄISYYDEN LASKENTA????
void OrienteeringMap::route_length(const std::string &name) const
{
    if (reitti_map_.find(name) == reitti_map_.end())
    {
        cout << "Error: Route named " << name << " can't be found" << endl;
        return;
    }

    //TÄHÄN TULEE NYT ETÄISYYDEN LASKENTA, JOS SELVITÄT MITEN VOI SIIRTÄÄ OMAAN MODUULIIN NIIN SIIRRÄ SITTEN
    float tulos = 0;
    vector<string> reitin_rastit = reitti_map_.at(name);
    vector<string>::const_iterator iteraattori = reitin_rastit.begin();
    ++iteraattori;
    vector<string>::const_iterator edellinen = iteraattori - 1;
    for (; iteraattori < reitin_rastit.end(); ++iteraattori)
    {
        // Seuraavassa haetaan rastien x- ja y-koordinaatit rasti_mapin
        // hyötykuormana olevasta tietueesta.
        tulos +=
            sqrt(pow((rasti_map_.at(*iteraattori).x - rasti_map_.at(*edellinen).x), 2)
             + pow((rasti_map_.at(*iteraattori).y - rasti_map_.at(*edellinen).y), 2));
        ++edellinen;
    }
    cout << "Route " << name << " length was " << setprecision(2) << tulos << endl;

}

// Finds and prints the highest rise in any of the routes after the given
// point.
void OrienteeringMap::greatest_rise(const std::string &point_name) const
{
    if (rasti_map_.find(point_name) == rasti_map_.end())
    {
        cout << "Error: Point named " << point_name << " can't be found" << endl;
        return;
    }

    set<string> setti;
    //string suurin_nousu_reitilla;
    int suurin_nousu = 0;

    for (auto tietopari : reitti_map_)  //tutkii kutakin reittiä
    {
        vector<string>::iterator iter= tietopari.second.begin();
        bool reitti_aloitettu = false;
        int vertailu = 0;
        int start_height = 0;
        //lähtee selvittään yhden reitin suurinta nousua kyseiseltä rastilta
        for (; iter != tietopari.second.end(); ++iter)
        {
            if (*iter == point_name)    //kun rasti löytyy reitiltä, alustetaan lähtökorkeus ja vertailukorkeus
            {
                start_height = rasti_map_.at(*iter).korkeus;
                vertailu = rasti_map_.at(*iter).korkeus;
                reitti_aloitettu = true;

            }
            else if (reitti_aloitettu == true and rasti_map_.at(*iter).korkeus >= vertailu)//reitti aloitettu ja korkeus edellistä suurempi
            {
                vertailu = rasti_map_.at(*iter).korkeus;

            }

            else if (reitti_aloitettu == true and rasti_map_.at(*iter).korkeus < vertailu)//reitti aloitettu mutta korkeus pienempi kuin edellisen
            {
                break;
            }
        }
        if (vertailu - start_height > suurin_nousu)
        {
            setti.clear();
            setti.insert(tietopari.first);
            suurin_nousu = vertailu - start_height;
        }
        else if (vertailu - start_height == suurin_nousu and suurin_nousu > 0)
            setti.insert(tietopari.first);


    }
    if (setti.size() > 0)
    {
        cout << "Greatest rise after point " << point_name << ", "<<suurin_nousu
             <<" meters, is on route(s):" << endl;
        for (auto alkio : setti)
            cout << " - "<< alkio << endl;
    }

    else
        cout << "No route rises after point " << point_name << endl;

}
