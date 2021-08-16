#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class Card
{
    public:
        //Constructor
        Card(unsigned int valNum, unsigned int suitNum);
        //Getters
        unsigned int getValueId();
        unsigned int getSuitId();
        unsigned int getGameValue();
        //Setter
        void setGameValue(unsigned int newValue);
        //Object Functions
        string stringify(); ///Creates a string representation of Card instance

    private: ///private attributes of value and suit
        unsigned int valueId;
        unsigned int suitId;
        unsigned int gameValue;
};

#endif // CARD_H
