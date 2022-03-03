#include "cards.hh"

using namespace std;

// TODO: Implement the methods here

//luo deck olio, jolle attribuutin top_, alussa osoittaa nullptr.
Cards::Cards():
    top_(nullptr)
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

}


//poistaa ekan eli päällimmäisen eli top_, poistaa siis dynaamisen muuttujan
bool Cards::remove(int &id)
{

}


//siirto vikasta ekaks
bool Cards::bottom_to_top()
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
