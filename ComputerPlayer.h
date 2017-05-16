//
//  ComputerPlayer.h
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 12/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#ifndef __Blackjack_Simulator__ComputerPlayer__
#define __Blackjack_Simulator__ComputerPlayer__

#include <iostream>

#include "Player.h"

class ComputerPlayer: public Player{
public:
    
    ComputerPlayer(std::string PlayerName, double InitialMoney);
    
    
    void SidneyDecision(Deckof52 &Deck);
    void AlexDecision(Deckof52 &Deck);
    void DarylDecision(Deckof52 &Deck);
    void SamDecision(Deckof52 &Deck);
    
    void EvaluateWinnings(bool Won, bool SixFive);
    
    double BankRoll, Bet;
    bool BJ, Surrendered;
};

#endif /* defined(__Blackjack_Simulator__ComputerPlayer__) */
