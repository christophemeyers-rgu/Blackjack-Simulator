//
//  Hand.h
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 10/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#ifndef __Blackjack_Simulator__Hand__
#define __Blackjack_Simulator__Hand__

#include <iostream>
#include <vector>


#include "Card.h"

class Hand{
public:
    Hand();
    Hand(Card ACard);
    ~Hand();
    
    void GetCards();
    int GetValue();
    int AceCount();
    
    std::vector<int> PrintedValues();
    bool isBust();

	std::vector<Card> Cards;
};

#endif /* defined(__Blackjack_Simulator__Hand__) */
