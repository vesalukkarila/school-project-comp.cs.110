
#include "orienteeringmap.hh"
#include <iostream>
#include <cmath>
#include <set>

using namespace std;

// Rakentaja
OrienteeringMap::OrienteeringMap():
    kartta_(), rasti_map_(), reitti_map_()
{

}

// Purkaja kääntää lopussa kaikki osoittimet nullptr:n
// vapauttaen dynaamisesti luodut oliomuuttujat.
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


// Luo vektorinvektorin alkioihin älykkäät osoittimet
// Vektoreiden ja alkioiden määrä saadaan syötetiedostosta
// Ei paluuarvoa, parametreina kartan koko kokonaislukuina
void OrienteeringMap::set_map_size(int width, int height)
{
    for (int l = 0; l < height; ++l)
    {
        vector<shared_ptr<Rasti>> sisempi_vektori; //muutettu normaalipointteri
        for (int p = 0; p < width; ++p)

        {
            // Älykäs osoitin sisemmän vektorin alkioksi
            shared_ptr <Rasti> osoitin = nullptr;
            sisempi_vektori.push_back(osoitin);

        }
        // Lisätään sisempi vektori ulomman vektorin alkioksi
        kartta_.push_back(sisempi_vektori);
    }
}


// Lisää rastin tiedot tietorakenteeseen rasti_map.
// Lisäksi luo dynaamisen Rasti-olion johon kartta_-tietorakenteen
// osoitin käännetään osoittamaan.
void OrienteeringMap::add_point(std::string name, int x, int y, int height, char marker)
{
    if (rasti_map_.find(name) == rasti_map_.end())
    {
        rasti_map_.insert({name, {name, x, y, height, marker, nullptr}});    //nimi avaimena, hkuormana kaikki Rastin_tiedot structissa
        kartta_.at(y-1).at(x-1) = make_shared<Rasti>(name, x, y, height, marker);
    }
}



// Tallentaa reittien tiedot reitti_map:iin
// Paluuarvona bool
//Parametreina yhdistettävät rastit ja reitin nimi
bool OrienteeringMap::connect_route(std::string from, std::string to, std::string route_name)
{
    // Jos jompikumpi rasteista ei löydy rasti_map:sta - false
    if (rasti_map_.find(from) == rasti_map_.end()
            or rasti_map_.find(to) == rasti_map_.end())
        return false;

    // Jos reitti on uusi - tallenetaan tiedot
    if (reitti_map_.find(route_name) == reitti_map_.end())
    {
        reitti_map_.insert({route_name, {from, to}});
        return true;
    }

    // Jos reitti jo olemassa, ja 1. parametri tiedoissa viimeisenä
    // tallennetaan 2. parametri sen perään
    else if (reitti_map_.find(route_name) != reitti_map_.end())
    {
        if ( reitti_map_.at(route_name).back() == from)
        {
            reitti_map_.at(route_name).push_back(to);
            return true;
        }
    }
    return false;
}



// Tulostaa kartta_-attribuutin sisällön.
// Ei paluuarvoa, ei parametreja.
void OrienteeringMap::print_map() const
{
    cout << " ";
    int sarake_leveys = 3;

    //Tulostetaan otsikkorivi, eli x-koordinaatit numeroina
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
        // Tulostetaan y-koordinaattien numerot
        cout << setw(rivi_nro_leveys) << right << rivi_nro;
        ++rivi_nro;

        // For-loopissa tulostetaan osoittimen osoittaman olion tunnus
        // tai piste jos osoitin = nullptr
        for (auto alkio : sisempi_vektori)
        {
            if (alkio == nullptr)
                cout << setw(sarake_leveys) << right << ".";
            else
               cout << setw(sarake_leveys) << right << alkio->hae_tunnus();
        }
        cout << endl;
    }
}



// Tulostaa reitit reitti_map:sta
// Ei paluuarvoa, ei parametreja
void OrienteeringMap::print_routes() const
{
    cout << "Routes:" << endl;
    for (auto tietopari : reitti_map_)
    {
        cout << " - " << tietopari.first << endl;
    }

}



// Tulostaa rastien nimen ja tunnuksen rasti_map:sta
// Ei paluuarvoa, ei parametreja
void OrienteeringMap::print_points() const
{
    cout << "Points:" << endl;
    for (auto tietopari : rasti_map_)
    {
        cout << " - " << tietopari.first << " : " << tietopari.second.tunnus << endl;   //tulosta rastin nimi ja tunnus
    }

}



//Tulostaa reitin tiedot reitti_map:sta
// Ei paluuarvoa, viiteparametrina reitin nimi
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



// Laskee reitin pituuden ohjeistuksessa annetulla kaavalla.
// Ei paluuarvoa, viiteparametrina reitin nimi.
void OrienteeringMap::route_length(const std::string &name) const
{
    if (reitti_map_.find(name) == reitti_map_.end())
    {
        cout << "Error: Route named " << name << " can't be found" << endl;
        return;
    }

    // Iteroidaan kahden iteraattorin avulla kerrallaan kahden rastin
    // välinen etäisyys ja lisätään tulos-muuttujaan.
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



// Tutkii kullakin reitillä suurinta nousua annetulta rastilta lähtien ja
// tulostaa tuloksen.
// Ei paluuarvoa, viitearametrina rastin nimi.
void OrienteeringMap::greatest_rise(const std::string &point_name) const
{
    if (rasti_map_.find(point_name) == rasti_map_.end())
    {
        cout << "Error: Point named " << point_name << " can't be found" << endl;
        return;
    }

    set<string> reitti_setti;
    int suurin_nousu = 0;

    for (auto tietopari : reitti_map_)  //tutkii kutakin reittiä
    {
        vector<string>::iterator iter= tietopari.second.begin();
        bool reitti_aloitettu = false;
        int vertailu = 0;
        int aloitus_korkeus = 0;
        //lähtee selvittään yhden reitin suurinta nousua kyseiseltä rastilta
        for (; iter != tietopari.second.end(); ++iter)
        {
            // Kun rasti löytyy reitiltä, alustetaan lähtökorkeus ja vertailukorkeus
            if (*iter == point_name)
            {
                aloitus_korkeus = rasti_map_.at(*iter).korkeus;
                vertailu = rasti_map_.at(*iter).korkeus;
                reitti_aloitettu = true;
            }
            // Jos aloitusrasti on löytynyt ja
            //seuraava rasti sitä korkeampi tai yhtä korkea
            else if (reitti_aloitettu == true
                     and rasti_map_.at(*iter).korkeus >= vertailu)
            {
                vertailu = rasti_map_.at(*iter).korkeus;

            }
            // Jos aloitusrasti on löytynyt mutta seuraava rasti sitä matalampi
            else if (reitti_aloitettu == true
                     and rasti_map_.at(*iter).korkeus < vertailu)
                break;
        }
        //Ennen seuraavaan reittiin siirtymistä muokataan
        // muuttujia suurin_nousu ja reitti_setti
        if (vertailu - aloitus_korkeus > suurin_nousu)
        {
            reitti_setti.clear();
            reitti_setti.insert(tietopari.first);
            suurin_nousu = vertailu - aloitus_korkeus;
        }
        else if (vertailu - aloitus_korkeus == suurin_nousu and suurin_nousu > 0)
            reitti_setti.insert(tietopari.first);
    }

    // Tulostukset
    if (reitti_setti.size() > 0)
    {
        cout << "Greatest rise after point " << point_name << ", "<<suurin_nousu
             <<" meters, is on route(s):" << endl;
        for (auto alkio : reitti_setti)
            cout << " - "<< alkio << endl;
    }

    else
        cout << "No route rises after point " << point_name << endl;
}
