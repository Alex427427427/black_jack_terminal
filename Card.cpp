#include "Card.h"
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;


//Getters
unsigned int Card::getValueId() {
    return valueId;
}

unsigned int Card::getSuitId() {
    return suitId;
}

unsigned int Card::getGameValue() {
    return gameValue;
}

//Setter
void Card::setGameValue(unsigned int newValue) {
    if (valueId == 0) {
        gameValue = newValue;
    }
}

//Object Functions
string Card::stringify() {
    string valueStr;
    string suitStr;
    switch (valueId) {
    case 0:
        valueStr = "Ace";
        break;
    case 1:
        valueStr = "Two";
        break;
    case 2:
        valueStr = "Three";
        break;
    case 3:
        valueStr = "Four";
        break;
    case 4:
        valueStr = "Five";
        break;
    case 5:
        valueStr = "Six";
        break;
    case 6:
        valueStr = "Seven";
        break;
    case 7:
        valueStr = "Eight";
        break;
    case 8:
        valueStr = "Nine";
        break;
    case 9:
        valueStr = "Ten";
        break;
    case 10:
        valueStr = "Jack";
        break;
    case 11:
        valueStr = "Queen";
        break;
    case 12:
        valueStr = "King";
        break;
    }
    switch (suitId) {
    case 0:
        suitStr = "Hearts";
        break;
    case 1:
        suitStr = "Spades";
        break;
    case 2:
        suitStr = "Clubs";
        break;
    case 3:
        suitStr = "Diamonds";
        break;
    }
    string display = "[" + valueStr + " of " + suitStr + "]";
    return display;
}

//Constructor
Card::Card(unsigned int valNum, unsigned int suitNum)
{
    valueId = valNum;
    suitId = suitNum;
    if (valNum >= 10) {
        gameValue = 10;
    }
    else {
        gameValue = valNum + 1;
    }
}


