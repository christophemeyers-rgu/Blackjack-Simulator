//
//  Game.h
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 10/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#ifndef __Blackjack_Simulator__Game__
#define __Blackjack_Simulator__Game__

#include <iostream>

#include "Deckof52.h"
#include "House.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

    
void SimpleRound(Deckof52 &Deck, House &Dealer, std::vector<HumanPlayer> &HP, std::vector<ComputerPlayer> &CP, bool Soft17, bool SixFive);
    
    


#endif /* defined(__Blackjack_Simulator__Game__) */
