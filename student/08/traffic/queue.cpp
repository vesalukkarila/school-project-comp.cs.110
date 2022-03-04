#include "queue.hh"
#include <iostream>
using namespace std;

// Implement the member functions of Queue here

const string EI_AUTOJA_JONOSSA = "No vehicles waiting in traffic lights";   //print ja switch_lights
const string g = "GREEN: ";
const string r = "RED: ";

// Constructor that initializes the attribute cycle_.
// (The other attibutes are initialized in the private part below.)
//VALMIS
Queue::Queue(unsigned int cycle):
    first_(nullptr), last_(nullptr), is_green_(false), cycle_(cycle)
{

}

// Destructor that deletes all the remaining vehicles from the queue.
//VALMIS
Queue::~Queue()
{
    while (first_ != nullptr)
    {
        Vehicle* poistettava = first_;
        first_ = first_->next;
        delete poistettava;
    }
}


// Resets the attribute cycle_.
//VALMIS
void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}


// If the color of traffic light is red, inserts a vehicle, the register
// number of which is reg, to the queue.
//jos valo punainen, lisää listan perälle
//VALMIS ( ?)
void Queue::enqueue(const string &reg)
{
    //jos vihreä ei lisää vain tulostaa läpipääsyn VALMIS
    if (is_green_ == true and first_ == nullptr)
    {
        cout << g << "The vehicle " << reg << " need not stop to wait" << endl;
        //esimerkin perusteella ei vaihda valoa punaiseksi tässä vaikka päästi läpi
        return;
    }

    //lisätään ensimmäinen alkio, first ja last osoittaa nyt samaan, alkion next nullptr
    if (is_green_ == false and first_ == nullptr)
    {
        Vehicle* osoitin = new Vehicle {reg, nullptr};
        first_ = osoitin;
        last_ = osoitin;
        return;
    }

    //jos listassa jo alkioita, lisätään loppuun ja siirretään entisen viimeisen next ja last_ osoittamaan uutta viimeistä
    else if (is_green_ == false and first_ != nullptr)
    {
        Vehicle* osoitin = new Vehicle{reg, nullptr};
        last_->next = osoitin;
        last_ = osoitin;
        return;
    }

}

// Prints the color of traffic light and the register numbers of those
// cars that are waiting in the traffic light queue (if any).
//VALMIS
void Queue::print() const
{
    //ei autoja jonossa, 2 tulostusta valon värin mukaan
    if (first_ == nullptr)
    {   if(is_green_ == false)
            cout << r << EI_AUTOJA_JONOSSA << endl;
        else
            cout << g << EI_AUTOJA_JONOSSA << endl;
    }
    //alkioita>0, tulostetaan apuosoittimen avulla regnumerot, attribuutteihin ei muutoksia
    else
    {
        Vehicle* apuosoitin = first_;
        cout << r << "Vehicle(s) ";
        while ( apuosoitin != nullptr)
        {
            cout << apuosoitin->reg_num << " ";
            apuosoitin = apuosoitin->next;
        }
        cout << "waiting in traffic lights" << endl;
    }
}


// Switches the color of traffic light from green to red or vice versa.
// If the new color is green, lets at least <cycle_> vehicles
// go on (i.e. calls dequeue at least <cycle_> times), and finally
// resets the color to red again.
//vaihtaa heti valonvärin, jos läpipäästettäviä, poistaa ne listasta (max cycle_-alkiota/kertaa dequeue) ja vaihtaa valon värin lopusssa
//jos ei läpipäästettäviä first_==nullptr, vaihtaa alussa muttei ei vaihda valon väriä ennen funktiosta poistumista
//tulostaa!!
void Queue::switch_light()
{
    //vaihtaa valon vihreäksi
    if (is_green_ == false)
        is_green_ = true;
    //vaihtaa valon punaiseksi
    else
        is_green_ = false;

    //jos ei läpipäästettäviä, 2 tulostusta printin avulla, ei vaihda valon väriä.
    if (first_ == nullptr)
        print();
    //alkioita löytyy, kutsuu dequeue cycle_kertaa ja tulostaa.jos alkioita vähemmän kuin cycle_
    else
    {
        unsigned int laskuri = 0;
        cout << g << "Vehicle(s) ";
        while (first_ != nullptr and laskuri < cycle_)
        {
            cout << first_->reg_num << " ";
            dequeue();
            ++laskuri;
        }
        cout << "can go on" << endl;
        is_green_ = false;
    }
}


//poistaa ensimmäisen alkion, eimielestäni tarvitse parametreja
//
void Queue::dequeue()
{
    if (first_ != nullptr)
    {
        Vehicle* poistettava = first_;
        first_ = first_->next;
        delete poistettava;
    }
}





