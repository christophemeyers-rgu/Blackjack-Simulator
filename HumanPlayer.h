//
//  HumanPlayer.h
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 12/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#ifndef __Blackjack_Simulator__HumanPlayer__
#define __Blackjack_Simulator__HumanPlayer__

#include <iostream>

#include "Player.h"

class HumanPlayer: public Player{
public:
    
    HumanPlayer(std::string PlayerName, double InitialMoney);
    
    
    void InsuranceDecision();
    void Decision(Deckof52 &Deck);
    
    void EvaluateWinnings(bool Won, bool SixFive);
    

    double BankRoll, Bet, InsuranceBet;
    bool BJ, Surrendered, Insured;
};

#endif /* defined(__Blackjack_Simulator__HumanPlayer__) */
