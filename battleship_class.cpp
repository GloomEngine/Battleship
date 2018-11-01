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
    vector <int> miss_list;

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

    int setstartingposition(int ship_num)
    {
        string position;

        cout << " Enter starting position(Ex: A1): ";
        getline(cin, position);

        while(bad_ship_placement(position, ship_num))
        {
            cout << "\n\n Enter starting position(Ex: A1): ";
            getline(cin, position);
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
        second->num_ship = num_ship;
    }

    void set_position(int ship_num)
    {
        int position = setstartingposition(ship_num);
        char dir = find_direction(position, ship_num);
        
        while(dir == '\0')
        {
            system("cls");
            print_board(ship_num);
            cout << "\n Error: Not enough space for ship\n\n";
            position = setstartingposition(ship_num);
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
                    bool bad = false;

                    for(int y = 0; y < ship_length; y++)
                    {
                        for(int x = 0; x < master_ship_pos.size(); x++)
                        {
                            if(master_ship_pos[x] == convert((pos[0]-y), pos[1]))
                            {
                                bad = true;
                                break;
                            }
                        }

                        if(bad)
                            break;
                    }

                    if(!bad)
                        dir += 'u';
                }
            }

            if(pos[0]+ship_length < 10)
            {
                if(master_ship_pos.empty())
                    dir += "d";

                else
                {
                    bool bad = false;

                    for(int y = 0; y < ship_length; y++)
                    {
                        for(int x = 0; x < master_ship_pos.size(); x++)
                        {
                            if(master_ship_pos[x] == convert((pos[0]+y), pos[1]))
                            {
                                bad = true;
                                break;
                            }
                        }

                        if(bad)
                            break;
                    }

                    if(!bad)
                        dir += 'd';
                }
            }

            if(dir.empty())
                return '\0';
        }

        string direction;

        cout << " Enter Direction (" << dir << "): ";
        cin >> direction;

        while(dir.find(direction) == string::npos || direction.size() > 2)
        {
            system("cls");
            print_board(ship_num);
            cout << "\n Error: Must enter given direction\n";
            cout << " Enter Direction (" << dir << "): ";
            cin.ignore();
            cin >> direction;
        }

        return direction.at(0);
    }

    bool bad_ship_placement(string position, int ship_num)
    {
        if(position.length() < 2 || position.length() > 3)
        {
            system("cls");
            print_board(ship_num);
            cout << " Error: Expecting only a letter and number up to 10";
            return true;
        }

        char letter = position.at(0);

        if(!isalpha(letter))
        {
            system("cls");
            print_board(ship_num);
            cout << " Error: Expected a letter followed by a number";
            return true;
        }
        
        letter = toupper(letter);

        for(int x = 1; x < position.length(); x++)
        {
            if(!isdigit(position.at(x)))
            {
                system("cls");
                print_board(ship_num);
                cout << "Error: Expecting only a letter and number up to 10";
                return true;
            }
        }

        int number = stoi(position.substr(1));

        if(letter < 'A' || letter > 'J')
        {
            system("cls");
            print_board(ship_num);
            cout << " Error: Letter must be between A and J";
            return true;
        }

        if(number < 0 || number > 10)
        {
            system("cls");
            print_board(ship_num);
            cout << " Error: Number must be between 1 and 10";
            return true;
        }

        if(number == 0)
            number = 10;

        int temp = convert(toupper(letter)-65, number-1);

        for(auto &x : master_ship_pos)
        {
            if (x == temp)
            {
                system("cls");
                print_board(ship_num);
                cout << " Error: Position collides with another ship: ";
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
        int number = stoi(position.substr(1));

        if(number == 0)
            number = 10;

        return convert(toupper(position.at(0))-65, number-1);
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

    void print_board(int modifier)
    {
        vector<int> temp = master_ship_pos;
        sort(temp.begin(), temp.end());
        string message = get_ship_info(modifier)->name+" ("+to_string(get_ship_info(modifier)->size);
        message += " spaces)";
        
		cout << "\n\n     1   2   3   4   5   6   7   8   9   0\n";

		for (int x = 0; x < 11; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				if (y == 0) { cout << "    ---"; }
				else { cout << " ---"; }

				if (y == 9 && x != 0 && x != 10)
                {
					cout << "\t|";

                    if(x == 1 && modifier >= 0 && modifier < num_ship)
                        cout << '\t' << string(message.size(), '-');
                }
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

            if(x == 0 && modifier >= 0 && modifier < num_ship)
                cout << '\t' << message;
            cout << endl;
		}
    }
};

#endif