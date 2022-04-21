#include "queue.hh"

#include <iostream>
#include<string>
using namespace std;
// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle):
     first_(nullptr), last_(nullptr), is_green_(false), cycle_(cycle), vari_("RED")
{

}

Queue::~Queue()
{
    while (first_ != nullptr)
    {
        Vehicle* tuhottava = first_;
        first_ = first_->next;
        delete tuhottava;
    }
    first_ = nullptr;
    last_ = nullptr;

}

void Queue::enqueue(const string &reg)
{
    if (is_green_ && first_ == nullptr)
    {
        cout << vari_ << ": " << "The vehicle " << reg << " need not stop to wait" << endl;
    }
    else if ( is_green_==false)  //jos vihreä
    {
        Vehicle* apu = new Vehicle{reg, nullptr};
        if (first_ == nullptr)  //jos eka
        {
            first_ = apu;
            last_ = apu;
        }
        else    //muutoin jonon perälle jatkoksi
        {
            last_->next = apu;
            last_ = apu;
        }
    }
}
// Switches the color of traffic light from green to red or vice versa.
// If the new color is green, lets at least <cycle_> vehicles
// go on (i.e. calls dequeue at least <cycle_> times), and finally
// resets the color to red again.
void Queue::switch_light()
{
    vaihdavari();
    if (first_ == nullptr)
    {
        cout << vari_ << ": " << "No vehicles waiting in traffic lights" << endl;
        return;
    }
    if (is_green_)
    {
        cout << vari_ << ": ";
        for (unsigned int laskuri = 0; laskuri < cycle_; ++laskuri)
        {
            if (first_ != nullptr)
                {
                cout << first_->reg_num << " ";
                dequeue();
                }
        }
        cout << "can go on" << endl;
        vaihdavari();   //muutetaan punaiseksi ja vari_ samalla
    }
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::dequeue()
{
    if (first_ == nullptr)
        return;
    Vehicle* apu = first_;
    first_ = first_->next;
    delete apu;
}

void Queue::print() const
{
    cout << vari_ << ": ";
    if (first_ == nullptr)
    {
        cout << "No vehicles waiting in traffic lights" << endl;
        return;
    }
    else
    {
        cout << "Vehicle(s) ";
        Vehicle* apu = first_;
        while (apu != nullptr)
        {
            cout << apu->reg_num << " ";
            apu = apu->next;
        }
        cout << "waiting in traffic lights" << endl;
    }
}

void Queue::vaihdavari()
{
    if (!is_green_)
    {
        is_green_ = true;
         vari_ = "GREEN";
    }
    else
    {
        vari_ = "RED";
        is_green_ = false;
    }
}


