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

        ship_info *next;

        string name;
    };

    ship_info *ships = NULL, *rear = NULL;
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
        if(ships == NULL)
        {
            ships = new ship_info;
            ships -> next = NULL;
            ships -> start = ship_spaces;
            ships -> size = ship_size;
            ships -> name = ship_name;
            rear = ships;
        }

        else
        {
            ship_info *temp = new ship_info;
            temp -> next = NULL;
            temp -> start = ship_spaces;
            temp -> size = ship_size;
            temp -> name = ship_name;
            rear -> next = temp;
            rear = temp;
        }

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
        if(position.length() < 2 || position.length() > 3)
            return 1;

        char letter = position.at(0);

        if(!isalpha(letter))
            return 2;
        
        letter = toupper(letter);

        for(int x = 1; x < position.length(); x++)
        {
            if(!isdigit(position.at(x)))
                return 1;
        }

        int number = stoi(position.substr(1));

        if(letter < 'A' || letter > 'J')
            return 3;

        if(number < 1 || number > 10)
            return 4;

        return 0;
    }

    int* get_ship_positions(string position)
    {
        return 0;
    }

};

#endif