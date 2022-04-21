#include "cards.hh"

// TODO: Implement the methods here
using namespace std;
Cards::Cards():
    top_(nullptr), bottom_(nullptr)
{

}

Card_data *Cards::get_topmost()
{
    return top_;
}

void Cards::add(int id)
{
    if (top_ == nullptr)
    {
        top_ = new Card_data{id, nullptr};
        bottom_ = top_;
    }
    else
    {
        Card_data* apu = new Card_data{id, top_};   //pinoon lisätään eteen
        top_ = apu;
    }
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    int laskuri = 1;
    Card_data* apu = top_;
    while (apu != nullptr)
    {
        s << laskuri << ": " << apu->data << endl;
        ++laskuri;
        apu = apu->next;
    }
}

bool Cards::remove(int &id)
{
    if ( top_ == nullptr)    //lisätty jos top osoittaa tyhjään
        return false;
    else
    {

        Card_data* poistettava = top_;
        id = poistettava->data;

        if (top_ == bottom_)
        {
            top_ = nullptr;
            bottom_ = nullptr;
        }
        else
            top_ = top_->next;

        delete poistettava;

    }
    return true;
}

bool Cards::bottom_to_top()
{
    if (bottom_ == nullptr)
        return false;
    Card_data* apu = top_;
    while(true)
    {
        if (apu->next != bottom_)
            apu = apu->next;
        else
        {
            apu->next = nullptr;
            bottom_->next = top_;
            top_ = bottom_;
            bottom_ = apu;
            break;
        }
    }
}

bool Cards::top_to_bottom()
{
    if (top_ == nullptr)
        return false;
    if (top_->next == nullptr)
        return false;
    Card_data* apu = top_;
    top_ = top_->next;
    bottom_->next = apu;
    bottom_ = apu;
    bottom_->next = nullptr;
    return true;

}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    Card_data* apu = top_;
    recursive_print(apu, s);

}

int Cards::recursive_print(Card_data *apu, std::ostream &s)
{
    if (apu->next == nullptr)
        s<< apu->data<<endl;
    else
    {
        recursive_print(apu->next, s);
        s << apu->data << endl;

    }
    return 0;
}


Cards::~Cards()
{
    while (top_ != nullptr)
    {
        Card_data* osoitin = top_;
        top_ = top_->next;
        delete osoitin;
    }
    top_ = nullptr;
    bottom_ = nullptr;

}


