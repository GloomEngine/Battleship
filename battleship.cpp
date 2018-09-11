#include <iostream>
#include <string>
#include "battleship_class.cpp"
using namespace std;

void setname(battleship*, int);
void playgame(battleship*, int);
int play();
void position_ships(battleship*, int);

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
    position_ships(player, player_count);
}

int play()
{
    return 0;
}

void position_ships(battleship *player, int player_count)
{
    string ship_names[] = {"Aircraft Carrier", "Battleship", "Cruiser", "Submarine", "Patrol Boat"};

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