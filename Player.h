//
//  Player.h
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 10/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#ifndef __Blackjack_Simulator__Player__
#define __Blackjack_Simulator__Player__

#include <iostream>
#include <string>


#include "Hand.h"

class Deckof52;

class Player{
public:
    Player();
    Player(std::string PlayerName);
    ~Player(){}
    
    
    void GetAllInfo();
    void BlackJack();
    void GetHand(int i);
    
    void SplitPairs(int i, Deckof52 &Deck);
    
    std::string Name;
    std::vector<Hand> Hands;
};


#endif /* defined(__Blackjack_Simulator__Player__) */
