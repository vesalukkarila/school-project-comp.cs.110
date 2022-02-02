//mitä tarvitsee oikeasti inclutoida ja miksi
#include "player.hh"
#include <iostream>
using namespace std;
#include <string>

Player::Player(const string &nimi):
    nimi_(nimi), pisteet_(0)
{

}

std::string Player::get_name() const
{
    return nimi_;
}

int Player::get_points() const
{
    return pisteet_;
}

void Player::add_points(int points)
{
    pisteet_ += points;
    if ( pisteet_ > 50)
    {
        pisteet_ = 25;
        cout << nimi_ << " gets penalty points!" << endl;

    }
}

bool Player::has_won() const
{
    if (pisteet_ == 50)
        return true;
    else
        return false;
}
