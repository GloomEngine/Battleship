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

    int bad_ship_placement(string position)
    {

        //TODO check for string length over and under 2
        
        char letter = position.at(0);
        int number = stoi(position.substr(1));

        if(!isalpha(letter))
            return 2;
        
        letter = toupper(letter);

        if(letter < 'A' || letter > 'J')
            return 3;

        if(number < 1 || number > 10)
            return 4;

        return 0;
    }

};

#endif