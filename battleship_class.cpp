#ifndef BATTLESHIP_CPP
#define BATTLESHIP_CPP

#include <iostream>
#include <string>
using namespace std;

class battleship
{

  private:
    string name;

  public:
  
    void setname(string n)
    {
        name = n;
    }

    string getname()
    {
        return name;
    }

};

#endif