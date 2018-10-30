#ifndef BATTLESHIP_CPP
#define BATTLESHIP_CPP

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
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
    int num_ship = 0;
    vector <int> master_ship_pos;

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

    int setstartingposition()
    {
        string position;

        cout << "Enter starting position(Ex: A1): ";
        getline(cin, position);

        while(bad_ship_placement(position))
        {
            cout << "\n\nEnter starting position(Ex: A1): ";
            getline(cin, position);
            bad_ship_placement(position);
        }

        return convert(position);
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

    void set_position(int ship_num)
    {
        int position = setstartingposition();
        char dir = find_direction(position, ship_num);
        
        while(dir == '\0')
        {
            cout << "\nError: Not enough space for ship\n\n";
            position = setstartingposition();
            dir = find_direction(position, ship_num);
        }

        ship_info *temp = get_ship_info(ship_num);
        int ship_length = temp->size;

        temp->pos = new int[ship_length];

        temp->pos[0] = position; 

        switch(dir)
        {
            case 'r':

                for(int x = 1; x < ship_length; x++)
                    temp->pos[x] = temp->pos[x-1]+1;

                break;

            case 'l':

                for(int x = 1; x < ship_length; x++)
                    temp->pos[x] = temp->pos[x-1]-1;

                break;

            case 'u':

                for(int x = 1; x < ship_length; x++)
                    temp->pos[x] = temp->pos[x-1]-10; 

                break;

            case 'd':

                for(int x = 1; x < ship_length; x++)
                    temp->pos[x] = temp->pos[x-1]+10; 

                break;
        }

        add_master_pos(ship_num);
    }

    char find_direction(int position, int ship_num)
    {
        int ship_length = get_ship_info(ship_num)->size;
        string dir;

        int *pos = convert(position);

        while(dir.empty())
        {
            if(pos[1]+ship_length < 10)
            {
                if(master_ship_pos.empty())
                    dir += "r";

                else
                {
                    int start = convert(pos[0], pos[1]);
                    int finish = convert(pos[0], pos[1]+ship_length);

                    for(int x = 0; x < master_ship_pos.size(); x++)
                    {
                        if(master_ship_pos[x] > start && master_ship_pos[x] < finish)
                            break;

                        else if(x == master_ship_pos.size()-1)
                            dir += "r";
                    }
                }
            }

            if(pos[1]-ship_length >= 0)
            {
                if(master_ship_pos.empty())
                    dir += "l";

                else
                {
                    int start = convert(pos[0], pos[1]);
                    int finish = convert(pos[0], pos[1]-ship_length);

                    for(int x = 0; x < master_ship_pos.size(); x++)
                    {
                        if(master_ship_pos[x] > finish && master_ship_pos[x] < start)
                            break;

                        else if(x == master_ship_pos.size()-1)
                            dir += "l";
                    }
                }
            }

            if(pos[0]-ship_length >= 0)
            {
                if(master_ship_pos.empty())
                    dir += "u";

                else
                {
                    int start = convert(pos[0], pos[1]);
                    int finish = convert(pos[0]-ship_length, pos[1]);

                    for(int x = 0; x < master_ship_pos.size(); x++)
                    {
                        if(master_ship_pos[x] > finish && master_ship_pos[x] < start)
                            break;

                        else if(x == master_ship_pos.size()-1)
                            dir += "u";
                    }
                }
            }

            if(pos[0]+ship_length < 10)
            {
                if(master_ship_pos.empty())
                    dir += "d";

                else
                {
                    int start = convert(pos[0], pos[1]);
                    int finish = convert(pos[0]+ship_length, pos[1]);

                    for(int x = 0; x < master_ship_pos.size(); x++)
                    {
                        if(master_ship_pos[x] > (start+(x*10)) && master_ship_pos[x] < (finish+(x*10)))
                            break;

                        else if(x == master_ship_pos.size()-1)
                            dir += "d";
                    }
                }
            }

            if(dir.empty())
                return '\0';
        }

        char direction;

        cout << "Enter Direction (" << dir << "): ";
        cin >> direction;

        while(dir.find(direction) == string::npos)
        {
            cout << "\nError: Must enter given direction\n";
            cout << "Enter Direction (" << dir << "): ";
            cin >> direction;
        }

        return direction;
    }

    bool bad_ship_placement(string position)
    {
        if(position.length() < 2 || position.length() > 3)
        {
            cout << "Error: Expecting only a letter and number up to 10";
            return true;
        }

        char letter = position.at(0);

        if(!isalpha(letter))
        {
            cout << "Error: Expected a letter followed by a number";
            return true;
        }
        
        letter = toupper(letter);

        for(int x = 1; x < position.length(); x++)
        {
            if(!isdigit(position.at(x)))
            {
                cout << "Error: Expecting only a letter and number up to 10";
                return true;
            }
        }

        int number = stoi(position.substr(1));

        if(letter < 'A' || letter > 'J')
        {
            cout << "Error: Letter must be between A and J";
            return true;
        }

        if(number < 1 || number > 10)
        {
            cout << "Error: Number must be between 1 and 10";
            return true;
        }

        int temp = convert(toupper(position.at(0))-65, position.at(1) - 49);

        for(auto &x : master_ship_pos)
        {
            if (x == temp)
            {
                cout << "Error: Position collides with another ship: ";
                return true;
            }
        }

        return false;
    }

    ship_info *get_ship_info(int ship_number)
    {
        ship_info *temp = ships;

        for(int x = 0; x < ship_number; x++)
        {
            if(temp -> next != NULL)
                temp = temp -> next;
        }

        return temp;
    }

    void add_master_pos(int ship_num)
    {
        ship_info *temp = get_ship_info(ship_num);

        for(int x = 0; x < temp->size; x++)
            master_ship_pos.push_back(temp->pos[x]);
    }

    int convert(string position)
    {
        return convert(toupper(position.at(0))-65, position.at(1) - 49);
    }

    int convert(int row, int col)
    {
        if(row == 0)
            return col;
        
        if(col == 0)
            return row * 10;

        return (row*10) + col;
    }

    int *convert(int position)
    {
        int *pos = new int[2];

        pos[1] = (position % 10);
        pos[0] = (position/10) % 10;

        return pos;
    }

    void print_board()
    {

        vector<int> temp = master_ship_pos;
        sort(temp.begin(), temp.end());
        
		cout << "     1   2   3   4   5   6   7   8   9   0\n";

		for (int x = 0; x < 11; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				if (y == 0) { cout << "    ---"; }
				else { cout << " ---"; }

				if (y == 9 && x != 0 && x != 10)
					cout << "\t|";
			}

			cout << endl;

			if (x < 10)
			{
				cout << ' ' << char(x + 65);

				for (int y = 0; y < 11; y++)
				{
					cout << " | ";

					if (y < 10)
                    {
                        if(!temp.empty() && convert(x, y) == temp.at(0))
                        {
                            cout << "X";
                            temp.erase(temp.begin());
                        } 
                        else
                            cout << " ";                        
                    }

					else { cout << "\t|"; }
				}
			}
            cout << endl;
		}
    }
};

#endif