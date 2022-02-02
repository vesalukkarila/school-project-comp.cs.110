#ifndef PLAYER_H
#define PLAYER_H
# include <iostream>
#include <string>
 using namespace std;

//mitä tarvii oikeasti inclutoida ja miksi

class Player
{
public:
    //constructor
    Player(string const& nimi);
    //metodit
    string get_name() const;
    int get_points() const;
    void add_points(int points);
    bool has_won() const;

private:
    // attribuutit
    string nimi_;
    int pisteet_;

};

#endif // PLAYER_H
