#include "animal.hh"

Animal::Animal(): x_(0), y_(0), moving_noise_("")   //tyhjän olion rakentaja? attribuuttien alustus
{

}

Animal::Animal(const std::string& moving_noise):    //varsinainen rakentaja jolle parametrina liikkumisenääni
    x_(0), y_(0), moving_noise_(moving_noise)
{

}

Animal::~Animal()   //purkaja, animal luokan
{

}
void Animal::move(int x, int y, std::ostream& output)
{
    x_ = x;
    y_ = y;

    output << moving_noise_ << std::endl;
}

void Animal::print_location(std::ostream &output) const
{
    output << "Location: " << x_ << " " << y_ << std::endl;

}
