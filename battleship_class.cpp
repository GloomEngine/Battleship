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
            int size, *pos;

            ship_info *next;

            string name;
        };

        ship_info *ships = NULL, *rear = NULL;
        int num_ship;

    public:

        battleship()
        {
            setplayername();
        }

        void setplayername()
        {
            string name;   

            cout << "Enter Player name: ";
            getline(cin, name);
            
            while(name.empty() || !isalpha(name.at(0)))
            {
                if(name.empty())
                {
                    cout << "\nError: Name cannot be empty\n";
                    cout << "Enter Player name: ";
                }

                else
                {
                    cout << "\nError: Name must start with a letter\n";
                    cout << "Enter Player name: ";
                }

                getline(cin, name);
            }

            player_name = name;
            cout << endl;
        }

        string getplayername()
        {
            return player_name;
        }

        void setship(int ship_size, string ship_name, battleship *second)
        {
            if(ships == NULL)
            {
                ships = new ship_info;
                ships -> next = NULL;
                ships -> pos = new int[ship_size*2];
                ships -> size = ship_size;
                ships -> name = ship_name;
                rear = ships;
                second -> ships = ships;
                second -> rear = ships;
            }

            else
            {
                ship_info *temp = new ship_info;
                temp -> next = NULL;
                temp -> pos = new int[ship_size*2];
                temp -> size = ship_size;
                temp -> name = ship_name;
                rear -> next = temp;
                second -> rear = temp;
                rear = temp;
                second -> rear = rear;
                
            }
        }

        void setposition()
        {
            //TODO loop through linked-list and set pos

            /*if(ship_position == NULL)
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
            }*/
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

            //TODO check if ship position is taken
            //also check if can place available spaces
        }

        int* get_ship_positions(string position)
        {
            return 0;
        }

        string getshipname(int ship_number)
        {
            ship_info *temp = ships;

            for(int x = 0; x < ship_number; x++)
            {
                if(temp -> next != NULL)
                    temp = temp -> next;

            }

            return temp->name;
        }

};

#endif