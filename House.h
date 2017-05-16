//
//  House.h
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 10/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#ifndef __Blackjack_Simulator__House__
#define __Blackjack_Simulator__House__

#include <iostream>

#include "Player.h"
#include "Deckof52.h"


class House: public Player{
public:
    House();
    House(std::string Dealer);
    ~House();
    
    void GetInfo(); //Need specified function for House as its score is initially hidden due to hole card
    
    void Decision(Deckof52 &Deck, bool Soft17);
    
};



#endif /* defined(__Blackjack_Simulator__House__) */
