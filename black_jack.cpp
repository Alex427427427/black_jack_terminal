#include "Card.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>


using namespace std;




//Functions

/** shuffle
* Iterating through the vector of Card pointers, swapping each with another random pointer in the vector.
* @param vector of Card pointers.
*/
void shuffle(vector<Card*> &aDeck);

/** deckSizeCheck
* Checks if size of deck is less tahn or equal to 15. If yes, add Discard pile to deck, then shuffle.
* @param vector of Card pointers for deck and discard pile
*/
void deckSizeCheck(vector<Card*> &aDeck, vector<Card*> &aDiscardPile);

/**displayBoard
*displays game board for all dealer cards and player cards and game scores
*@param unsigned int of dealer and player values, vector of card pointers of player and dealer hands.
*/
void displayBoard(unsigned int aDealerValue, vector<Card*> &aDealerHand, unsigned int aPlayerValue, vector<Card*> &aPlayerHand);

/**deal
*deals a card to dealer, and beginning player cards, where no interaction is needed.
*updates value
*@param vector of card pointers of deck, hand, unsigned int of value
*/
void deal(vector<Card*> &aDeck, vector<Card*> &aHand, unsigned int &aValue);

/**interactiveDeal
*used for when card is dealt to player, where interaction is needed in case of Ace.
*@param vector of deck, hand, unsigned int of value
*/
void interactiveDeal(vector<Card*> &aDeck, vector<Card*> &aHand, unsigned int &aValue);






//main code
int main()
{
    //declare vectors
    vector<Card*> deck;
    vector<Card*> dealerHand;
    vector<Card*> playerHand;
    vector<Card*> discardPile;
    unsigned int dealerValue = 0;
    unsigned int playerValue = 0;
    bool roundFinished = false; ///boolean to break out of round

    srand(time(0));
    char userInput;


    //generate and shuffle deck
    for (unsigned int valNum = 0; valNum < 13; valNum++) {///for each value
        for (unsigned int suitNum = 0; suitNum < 4; suitNum++) {///for each suit
            Card* pCard = new Card(valNum, suitNum);///dynamically declare a new card with value and suit
            deck.push_back(pCard);///add to vector
        }
    }
    shuffle(deck);

    //Game start screen with instructions and rules.
    cout << "Black Jack. " << endl << endl;

    cout << "Numbered cards have their numbers as values for this game. Jack, Queen, King have values of 10. " << endl;
    cout << "Ace has a value of either 1 or 11 as your choice. " << endl << endl;

    cout << "You and your dealer will both have 2 cards in the beginning. " << endl;
    cout << "You will be handed cards one by one until you call stop. " << endl;
    cout << "Your dealer will then start drawing cards for herself, until her total value is at least 17. " << endl << endl;

    cout << "Aim to accumulate a total value of 21, but not exceeding it. " << endl;
    cout << "Whoever manages to get as close to 21 as possible without passing it, will win." << endl;
    cout << "If your dealer has the same value as you, she also wins. " << endl << endl;

    cout << "Once you understand the rules, " << endl << flush;
    system("pause"); ///"press any key to continue..."
    system("CLS");


    //game starts, runs indefinitely
    while (true) {
        //deal 2 cards to player and dealer, checking deck size with each deal
        for (unsigned int i=0; i<2; i++) {
            //deal dealer card, remove card from deck
            deal(deck, dealerHand, dealerValue);
            deckSizeCheck(deck, discardPile);

            //deal player card, remove card from deck
            deal(deck, playerHand, playerValue);
            deckSizeCheck(deck, discardPile);
        }

        //display board, black jack check
        displayBoard(dealerValue, dealerHand, playerValue, playerHand);
        if (dealerValue == 21) {
            roundFinished = true;
        }
        else if (playerValue == 21) {
            roundFinished = true;
        }


        //While round is still going
        while (!roundFinished) {
            cout << "> Do you want another card? (y/n): ";
            cin >> userInput;

            //if user wants another card...
            if (userInput == 'y') {
                //deal player card, remove card from deck. Check deck size. Display. Check for win conditions.
                interactiveDeal(deck, playerHand, playerValue);
                deckSizeCheck(deck, discardPile);
                system("CLS");
                displayBoard(dealerValue, dealerHand, playerValue, playerHand);
                if (playerValue >= 21) {
                    roundFinished = true;
                }
            }
            //if not...
            else if (userInput == 'n') {
                system("CLS");
                roundFinished = true;
                while (dealerValue < 17) {
                    //deal dealer card, remove card from deck
                    deal(deck, dealerHand, dealerValue);
                    deckSizeCheck(deck, discardPile);
                }
                cout << "The dealer has drawn her cards. " << endl << endl;
                //display board
                displayBoard(dealerValue, dealerHand, playerValue, playerHand);
            }
        }


        //check for win conditions
        if (playerValue > 21) {
            cout << endl << "Final result: Dealer wins!" << endl << endl;
        }
        else if (dealerValue > 21) {
            cout << endl << "Final result: You win!" << endl << endl;
        }
        else if (dealerValue >= playerValue) {
            cout << endl << "Final result: Dealer wins!" << endl << endl;
        }
        else if (dealerValue < playerValue) {
            cout << endl << "Final result: You win!" << endl << endl;
        }


        //Add player and dealer hands to discard pile, clear dealer hands and player hands.
        while (dealerHand.size() != 0) {
            discardPile.push_back(dealerHand[0]);
            dealerHand.erase(dealerHand.begin());
        }
        while (playerHand.size() != 0) {
            discardPile.push_back(playerHand[0]);
            playerHand.erase(playerHand.begin());
        }
        cout << "Cards on board are moved to the discarded pile." << endl;


        //clear game, prompt next round
        cout << "To play another round, " << endl << flush;
        system("pause"); ///"press any key to continue..."
        dealerValue = 0;
        playerValue = 0;
        userInput = 'o';
        roundFinished = false;
        system("CLS");
    }
    return 0;
}






//Function definitions

void shuffle(vector<Card*> &aDeck) {
    for (unsigned int i = 0; i < aDeck.size(); i++) {
        //Creates random position index, then swaps pointers at current position and generated index using temporary variable.
        unsigned int swapPos = rand() % aDeck.size();
        Card* pTemp = aDeck[i]; ///move first card into temporary variable
        aDeck[i] = aDeck[swapPos];
        aDeck[swapPos] = pTemp;
    }
}


void deckSizeCheck(vector<Card*> &aDeck, vector<Card*> &aDiscardPile) {
    if (aDeck.size() <= 15) {
        //while discard pile is not empty, add first card to deck, erase first card.
        while (aDiscardPile.size() != 0) {
            aDeck.push_back(aDiscardPile[0]);
            aDiscardPile.erase(aDiscardPile.begin());
        }
        shuffle(aDeck);
        cout << "Card deck running out. Discarded Pile is added back to the deck and shuffled." << endl << endl;
    }
}

void displayBoard(unsigned int aDealerValue, vector<Card*> &aDealerHand, unsigned int aPlayerValue, vector<Card*> &aPlayerHand) {
    //display dealer hand and value
    cout << "Dealer's Hand -> Value: " << aDealerValue << endl;
    for (unsigned int i=0; i<aDealerHand.size(); i++) {
        cout << (*aDealerHand[i]).stringify() << endl;
    }
    cout << endl;
    //display player hand and value
    cout << "Player's Hand -> Value: " << aPlayerValue << endl;
    for (unsigned int i=0; i<aPlayerHand.size(); i++) {
        cout << (*aPlayerHand[i]).stringify() << endl;
    }
}


void deal(vector<Card*> &aDeck, vector<Card*> &aHand, unsigned int &aValue) {
    //deal card, remove card from deck
    aHand.push_back(aDeck[0]);
    aDeck.erase(aDeck.begin());

    //check if Ace, update dealer value
    if ((*aHand[aHand.size()-1]).getValueId() == 0) {
        //Design AI
        if (aValue > 10) {
            (*aHand[aHand.size()-1]).setGameValue(1);
        }
        else if (aValue >= 6) {
            (*aHand[aHand.size()-1]).setGameValue(11);
        }
        else if (aValue > 3) {
            (*aHand[aHand.size()-1]).setGameValue(1);
        }
        else {
            (*aHand[aHand.size()-1]).setGameValue(11);
        }
    }
    aValue = aValue + (*aHand[aHand.size()-1]).getGameValue(); ///update value
}

void interactiveDeal(vector<Card*> &aDeck, vector<Card*> &aHand, unsigned int &aValue) {
    //deal player card, remove card from deck
    aHand.push_back(aDeck[0]);
    aDeck.erase(aDeck.begin());

    //check if Ace, prompt player choice, update player value
    if ((*aHand[aHand.size()-1]).getValueId() == 0) {
        unsigned int aceValue;
        bool correctInput = false;

        while (!correctInput) {
            cout << "You got an Ace. Will its value be 1 or 11? (1/11): ";
            cin >> aceValue;
            if (aceValue == 11) {
                (*aHand[aHand.size()-1]).setGameValue(11);
                correctInput = true;
            }
            else if (aceValue == 1) {
                (*aHand[aHand.size()-1]).setGameValue(1);
                correctInput = true;
            }
        }
        correctInput = false;
    }
    aValue = aValue + (*aHand[aHand.size()-1]).getGameValue();
}

