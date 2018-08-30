#ifndef BATTLESHIP_CPP
#define BATTLESHIP_CPP

#include <iostream>
#include <string>
using namespace std;

class battleship
{

  private:
    string player_name;

    struct ship_info
    {
        int size = 2, *position = new int[size];

        string ship_name;
    };

    ship_info *ships = new ship_info[5];

  public:
  
    void setplayername(string n)
    {
        player_name = n;
    }

    string getplayername()
    {
        return player_name;
    }

};

#endif