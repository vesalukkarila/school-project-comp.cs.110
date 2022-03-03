#include "cards.hh"
#include <iostream>

using namespace std;

// TODO: Implement the methods here

//luo deck olio, jolle attribuutin top_, alussa osoittaa nullptr.
Cards::Cards(): top_(nullptr), bottom_(nullptr)
{

}

//Purkaja jee!
Cards::~Cards()
{
   while ( top_ != nullptr ) {
      Card_data* item_to_be_released = top_; //first on attribuuttii jonka tyyppi List_item. paikallisosoittimeen kopioidaan first:n osoittama muistiosoite
      top_ = top_->next;    //attribuuttiosoittimen muistipaikka laitetaan osoittamaan next:n osoittamaan alkioon
                    // Se kopioi ekalla rivillä first_:n osoittaman muistiosoitteen paikallismuuttujaosoittimen muistipaikalle
      delete item_to_be_released;
   }
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
    Card_data* paikallisosoitin = new Card_data{id, nullptr, nullptr};   //paikallisosoittimeen tallentuu uuden dynaamisen muuttujan osoite
    if (top_ == nullptr)
    {
        top_ = paikallisosoitin;                //attribuutin muistiin kopioidaan paikallisosoittimen osoittama osoite
        bottom_ = paikallisosoitin;         //ekan alkion lisäyksessä määräytyy bottom!!!!
    }
    else
    {
        paikallisosoitin->next = top_;          //paikallisosoittimeen tallentuu entisen topin osoittama osoite
        top_->previous = paikallisosoitin;      //topin eteen ilmestyneeseen po osoittamaan muistipaikaan osoittaa previous!!

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
    Card_data* viimeinen = nullptr;
    Card_data* tokavika = nullptr;
    while (true)
    {
        //vikasta ekaks siirretyn previous osoittamaan nullptr
        //entinen ekan osoittamaan uuteen ekaan
        //bottom_ osoittamaan uutta viimeistä

        if (osoitin->next == nullptr)   //jos kysessä on viimeinen alkio
        {
            viimeinen = osoitin;
            //entisen tokavikan next pitää saada osoittamaan nullprt!!
            viimeinen->next = top_; //viimeinen joka siirretään ensimmäiseksi laitetaan osoittamaan entistä ensimmäistä
            viimeinen->previous = nullptr;  //ekaksi siirrettävän previous osoittamaan nullptr!!!
            top_->previous = viimeinen;     //entinen eka osoitaa uuteen ekaan!!!
            top_ = viimeinen;       // attribuuti top_ osoittaa uuteen ensimmäiseen
            //tokavika->next = nullptr; // tokavikan next osoittamaan nullptr
            bottom_ = tokavika;
            bottom_->next = nullptr;    //sama kuin 2 riviä ylempänä5

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

//siirto ekasta vikaks
bool Cards::top_to_bottom()
{
    if (top_ == nullptr)
        return false;
    Card_data* eka_vikaks = top_;
    Card_data* osoitin = top_;
    //Card_data* toka;
    int laskuri = 1;
    while (true)
    {

        if (osoitin->next == nullptr)   //jos viimeinen alkio, siirretään se osoittamaan uutta viimeistä
        {
            osoitin->next = eka_vikaks;
            top_ = eka_vikaks->next;
            eka_vikaks->next->previous = nullptr;
            eka_vikaks->next = nullptr; //uuuden viimeisen next osoittamaan nullptr
            eka_vikaks->previous = osoitin; //uuden vikan previous osoittamaan vanhaa vikaa!!
            bottom_ = eka_vikaks;       //bottom attribuutti osoittaa uutta vvikaa
            //top_ siirretään osoittamaan uutta ekaa
           // top_ = toka;  toisiks ylin lisätty
            //toka->previous = nullptr;   //uusi ekan previous osoittaa nullptr     siirretty eri muotoon kolmanneks ylimmäks

            return true;
        }
        else
        {
            osoitin = osoitin->next;
            laskuri += 1;
            /*if (laskuri == 2)     poistettu kun ei hyvksy toka osoittimen käyttöä jostain syystä
                toka = osoitin;*/
        }

    }

}



//poistaa ekan eli päällimmäisen eli top_, poistaa siis dynaamisen muuttujan
bool Cards::remove(int &id)
{

    if (top_->data != id)
        return false;
    else
    {
        if (top_->data == id)
        {
            Card_data* poistettava = top_;
            top_ = top_->next;      //top osoittaa tokaa
            top_->previous = nullptr;   //tokan previous osoittaa nullptr
            delete poistettava;
        }


    }
    return true;
}



//tulostus vikasta ekaan INNOKKAILLE! JEE!
void Cards::print_from_bottom_to_top(std::ostream &s)
{
    if (bottom_ == nullptr)
        return;

    else
    {
        int laskuri = 1;
        Card_data* osoitin = bottom_;
        while(true)
        {
            s << laskuri << ": " << osoitin->data << endl;
            laskuri += 1;
            osoitin = osoitin->previous;
            if (osoitin == nullptr)
                break;
        }
    }
}


/*
int Cards::recursive_print(Card_data *top, std::ostream &s)
{

}
*/
