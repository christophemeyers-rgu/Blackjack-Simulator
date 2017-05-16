//
//  Deckof52.h
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 10/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#ifndef __Blackjack_Simulator__Deckof52__
#define __Blackjack_Simulator__Deckof52__

#include <iostream>
#include <string>



#include "House.h"
#include "Player.h"

class Hand;
class House;
class Player;


class Deckof52{
public:
    Deckof52();
	~Deckof52();

    void FillDeck();
    void ShowDeck();  //Deck-specific way of printing, shows deck as neatly as possible for how it is filled
    void Shuffle();
    
    Card Hit();
    

    //These are only used when filling the deck
	std::vector<std::string> Values;

	std::vector<Card> Cards;
    
};



#endif /* defined(__Blackjack_Simulator__Deckof52__) */
