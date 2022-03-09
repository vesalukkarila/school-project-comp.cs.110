#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}


// Removes the topmost card and passes it in the reference parameter id to the caller.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::remove(int &id)
{
    if (top_ == nullptr)
        return false;


    id = top_->data;

    top_ = top_->next;


    return true;

}

void Cards::reverse()
{

    std::shared_ptr <Card_data> vika = top_;
    std::shared_ptr <Card_data> apu = top_;


    while (top_->next != nullptr)
       {
        top_ = top_->next;  //top_ siirretään loppuun
        }
    while (true)
    {
        if (apu->next == top_)
        {
            top_->next = apu;
            apu = vika;
        }
        else if (apu->next.use_count() == 2)
        {
            apu->next->next = apu;
            if (vika.use_count() == 3)
            {
                apu->next = nullptr;
                break;
            }
            apu = vika;
        }
        else
            apu = apu->next;
    }

}




// Tip for writing code more efficiently:
// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file cards.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in cards.cpp
