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
        int num_ship = 0, *master_ship_pos;

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

        int getnumships()
        {
            return num_ship;
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

            num_ship++;
        }

        void setposition(int *position, int ship_num, char dir)
        {
            int ship_length = getshipspaces(ship_num);
            ship_info *temp = ships;

            for(int x = 0; x < ship_num; x++)
            {
                if(temp->next != NULL)
                    temp = temp->next;
            }

            temp->pos = new int[10];

            temp->pos[0] = position[0];
            temp->pos[1] = position[1];

            switch(dir)
            {

                case 'r':

                    for(int x = 2; x < ship_length*2; x+=2)
                    {
                        temp->pos[x] = position[0];
                        temp->pos[x+1] = temp->pos[x-1] + 1;
                    } 

                    break;

                case 'l':

                    for(int x = 2; x < ship_length*2; x+=2)
                    {
                        temp->pos[x] = position[0];
                        temp->pos[x+1] = temp->pos[x-1] - 1;
                    } 

                    break;

                case 'u':

                    for(int x = 2; x < ship_length*2; x+=2)
                    {
                        temp->pos[x] = temp->pos[x-2] - 1;
                        temp->pos[x+1] = position[1];
                    } 

                    break;

                case 'd':

                    for(int x = 2; x < ship_length*2; x+=2)
                    {
                        temp->pos[x] = temp->pos[x-2] + 1;
                        temp->pos[x+1] = position[1];
                    } 

                    break;
            }
        }

        string find_direction(int *pos, int ship_num)
        {
            int ship_length = getshipspaces(ship_num);
            string dir = "";

            if(pos[1]+ship_length < 10)
                dir += "r";

            if(pos[1]-ship_length >= 0)
                dir += "l";

            if(pos[0]-ship_length >= 0)
                dir += "u";

            if(pos[0]+ship_length < 10)
                dir += "d";

            return dir;
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

        int getshipspaces(int ship_number)
        {
            ship_info *temp = ships;

            for(int x = 0; x < ship_number; x++)
            {
                if(temp -> next != NULL)
                    temp = temp -> next;

            }

            return temp->size;
        }

};

#endif