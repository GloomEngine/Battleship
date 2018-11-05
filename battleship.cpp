#include <iostream>
#include <string>
#include "battleship_class.cpp"
using namespace std;

void playgame(battleship *[], int);
bool game_over(battleship *[], int);
void position_ships(battleship *[], int);
void game_config(battleship *[]);

int main(void)
{
    int player_count = 2;
    battleship *player[2];

    player[0] = new battleship;
    player[1] = new battleship;

    playgame(player, player_count);
}

void playgame(battleship *player[], int player_count)
{
    //game_config(player);
    position_ships(player, player_count);

    while(!game_over(player, player_count))
    {
        for(int x = 0; x < player_count; x++)
        {
            int z = 0;
            for(int y = x+1; z < player_count-1; y++)
            {
                if(y == player_count)
                    y = 0;

                system("cls");

                cout << " " << player[x]->getplayername() << " it's time to sink some ships!";
                player[x]->print_board(player[y]);
                player[x]->attack(player[y]);
                z++;
            }
        }
    }
}

bool game_over(battleship *player[], int player_count)
{
    return player[0]->get_game_state(player, player_count);
}

void position_ships(battleship *player[], int player_count)
{
    string default_ship_names[5] = {"Carrier", "Battleship", "Cruiser", "Submarine", "Patrol Boat"};
    int default_ship_size[5] = {5, 4, 3, 3, 2};

    for(int x = 0; x < 1; x++)
        player[0]->setship(default_ship_size[x], default_ship_names[x], player[1]);

    for(int x = 0; x < player_count; x++)
    {
        cout << "Look away while "<< player[x]->getplayername() << " positions their ships";

        getchar();
        system("cls");

        for(int y = 0; y < player[x]->getnumships(); y++)
        {
            cout << " " << player[x]->getplayername() << " enter your ships";
            player[x]->print_board(y);
            player[x]->set_position(y);

            cin.ignore();
            cout << endl;
            system("cls");
        }
        player[x]->reposition();
    }
}

void game_config(battleship *player[])
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

        player[0]->setship(ship_size, ship_name, player[1]);
    }

    system("cls");

    for(int x = 0; x < ship_count; x++)
    {
        cout << player[1]->get_ship_info(x)->name << endl;
    }

    system("pause");
}