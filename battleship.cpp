#include <iostream>
#include <string>
#include "battleship_class.cpp"
using namespace std;

void setname(battleship*, int);
void playgame(battleship*, int);
int play();
void position_ships(battleship*, int);
void game_config();

int main(void)
{
    int player_count = 2;
    battleship player[2];
    battleship *player_pointer = player;

    setname(player_pointer, player_count);

    do{

        playgame(player_pointer, player_count);

    }while (play());

}

void setname(battleship *player, int size)
{

    string name;    
    
    for(int x = 0; x < size; x++)
    {
        cout << "Enter Player[" << x + 1 << "] name: ";
        getline(cin, name);
        
        while(name.empty() || !isalpha(name.at(0)))
        {
            if(name.empty())
            {
                cout << "\nError: Name cannot be empty\n";
                cout << "Enter Player[" << x + 1 << "] name: ";
            }

            else
            {
                cout << "\nError: Name must start with a letter\n";
                cout << "Enter Player[" << x + 1 << "] name: ";
            }

            getline(cin, name);
        }

        player[x].setplayername(name);
        cout << endl;
    }
    
    system("cls");
    
}

void playgame(battleship *player, int player_count)
{
    game_config();
    position_ships(player, player_count);
}

int play()
{
    return 0;
}

void position_ships(battleship *player, int player_count)
{
    string default_ship_names[] = {"Aircraft Carrier", "Battleship", "Cruiser", "Submarine", "Patrol Boat"};

    for(int x = 0; x < player_count; x++)
    {
        cout << player[!x].getplayername() << " look away while";
        cout << player[x].getplayername() << " positions their ships";

        system("cls");

        for(int y = 0; y < 5; y++)
        {
            string position;

            cout << "Enter starting position(Ex: A1): ";
            getline(cin, position);

            int bad_placement = player[x].bad_ship_placement(position);

            while(bad_placement)
            {
                switch(bad_placement)
                {
                    case 1:
                        cout << "Error: Expecting only a letter and number up to 10";
                        break;

                    case 2:
                        cout << "Error: Expected a letter followed by a number";
                        break;

                    case 3:
                        cout << "Error: Letter must be between A and J";
                        break;

                    case 4:
                        cout << "Error: Number must be between 1 and 10";
                }

                cout << "\n\nEnter starting position(Ex: A1): ";
                getline(cin, position);
                bad_placement = player[x].bad_ship_placement(position);
            }
        }
    }

    getchar();
}

void game_config()
{
    int ship_count, ship_size;
    string ship_name;

    cout << "Enter the number of ships you wish to use (2-8): ";

    for(cin >> ship_count; !cin; cin>>ship_count)
    {
        cin.clear();
        cin.ignore();
        cout << "\nError: Ammount must be between 2 and 8\n";
        cout << "Enter the number of ships you wish to use (2-8): ";
    }

    cout << endl;

    for(int x = 0; x < ship_count; x++)
    {
        cin.ignore();
        cout << "Enter a name for ship " << x+1 << ": ";
        getline(cin, ship_name);

        while(ship_name.empty() || !isalpha(ship_name.at(0)))
        {
            if(ship_name.empty())
            {
                cout << "\nError: ship name cannot be empty\n";
                cout << "Enter a name for ship " << x+1 << ": ";
            }

            else
            {
                cout << "\nError: ship_name must start with a letter\n";
                cout << "Enter a name for ship " << x+1 << ": ";
            }

            getline(cin, ship_name);
        }

        cin.ignore();
        cout << "Enter ship size: ";

        for(cin >> ship_size; !cin; cin>>ship_size)
        {
            cin.clear();
            cin.ignore();
            cout << "\nError: Expected 0 or 1\n";
            cout << "Enter ship size: ";
        }

        while(ship_size < 2 && ship_size > 8)
        {
            cout << "\nError: Size must be between 2 and 8\n";
            cout << "Enter ship size: ";
            cin >> ship_size;
        }

        cout << endl;
    }
}