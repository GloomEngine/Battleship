#ifndef BATTLESHIP_CPP
#define BATTLESHIP_CPP

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class battleship
{

  private:
    string player_name;

    struct ship_info
    {
        int size, start;

        string ship_name;
    };

    ship_info *ships = new ship_info[5];
    int *ship_position = NULL, ship_spaces;

  public:
  
    void setplayername(string n)
    {
        player_name = n;
    }

    string getplayername()
    {
        return player_name;
    }

    void setship(int *pos, int ship_size, string ship_name)
    {
        if(ship_position == NULL)
        {
            ship_spaces = ship_size;
            ship_position = new int[ship_spaces];
        }

        else
        {
            ship_spaces += ship_size;
            int *temp = new int[ship_size];
            
            for(int x = 0; x < sizeof(ship_position)/sizeof(int); x++)
                temp[x] = ship_position[x];
            
            delete [] ship_position;
            ship_position = temp;
        }

        for(int x = 0; x < ship_size; x++)
            ship_position[(ship_spaces-ship_size)+x] = pos[x];

    }

    bool bad_ship_placement(char letter, int number)
    {
        if(!isalpha(letter))
            return true;
        
        letter = toupper(letter);

        if(letter < 'A' || letter > 'J')
            return true;

        if(number < 1 || number > 10)
            return true;

        return false;
    }

};

#endif