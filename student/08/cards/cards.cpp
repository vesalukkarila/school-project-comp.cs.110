#include "cards.hh"
#include <iostream>
#include <string>

using namespace std;

// TODO: Implement the methods here

//luo deck olio, jolle attribuutin top_, alussa osoittaa nullptr.
Cards::Cards(): top_(nullptr)
{

}


//joku hiriö jota ei sais olla, return top_ (?)
Card_data *Cards::get_topmost()
{
    return top_;
}


//lisätään uusi kortti top paikalle eli ekaksi, id arvoina tulee i:n arvot eli 0,1,2,3,4 ekassa testissä
void Cards::add(int id)
{
    //luodaan paikallismuuttujaosoitin jonka muistipaikalle tallentuu uuden dynaamisen muuttujan osoite
    Card_data* paikallisosoitin = new Card_data{id, nullptr};   //paikallisosoittimeen tallentuu uuden dynaamisen muuttujan osoite
    if (top_ == nullptr)
    {
        top_ = paikallisosoitin;                //attribuutin muistiin kopioidaan paikallisosoittimen osoittama osoite
    }
    else
    {
        paikallisosoitin->next = top_;          //paikallisosoittimeen tallentuu entisen topin osoittama osoite
        top_ = paikallisosoitin;                //uudeksi topiksi tulee paikallisosoittimen osoittama osoite
    }
}


//tulostaa ekasta vikaan
void Cards::print_from_top_to_bottom(std::ostream &s)
{

    if (top_ == nullptr)
        return;
    else
    {
        int laskuri = 1;

        Card_data* osoitin = top_;
        while (true)
        {
            s << laskuri << ": " << osoitin->data << endl;
            laskuri += 1;
            osoitin = osoitin->next;
            if (osoitin == nullptr)
                break;
        }
    }
}


//siirto vikasta ekaks
bool Cards::bottom_to_top()
{
    if (top_ == nullptr)
        return false;
    Card_data* osoitin = top_;  //paikallismuuttujaosoittimeen kopioidaan topin osoittama osoite
    Card_data* viimeinen;
    Card_data* tokavika;
    while (true)
    {

        if (osoitin->next == nullptr)   //jos kysessä on viimeinen alkio
        {
            viimeinen = osoitin;
            //entisen tokavikan next pitää saada osoittamaan nullprt!!
            viimeinen->next = top_; //viimeinen joka siirretään ensimmäiseksi laitetaan osoittamaan entistä ensimmäistä
            top_ = viimeinen;       // attribuuti top_ osoittaa uuteen ensimmäiseen
            tokavika->next = nullptr; // tokavikan next osoittamaan nullptr
            return true;
        //tän ois voinut tehdä ilman "viimeinen" osoittajaa, "osoitin" osoittajalla ois pärjännyt hyvin
        }
        else
        {
            tokavika = osoitin;
            osoitin = osoitin->next;
        }
    }
}


//poistaa ekan eli päällimmäisen eli top_, poistaa siis dynaamisen muuttujan
bool Cards::remove(int &id)
{

}





//siirto ekasta vikaks
bool Cards::top_to_bottom()
{

}


//tulostus vikasta ekaan INNOKKAILLE! JEE!
void Cards::print_from_bottom_to_top(std::ostream &s)
{

}

//Purkaja jee!
Cards::~Cards()
{

}

int Cards::recursive_print(Card_data *top, std::ostream &s)
{

}
