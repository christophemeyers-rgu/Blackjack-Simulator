//
//  Blackjack.h
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 02/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#ifndef __Blackjack_Simulator__Functions__
#define __Blackjack_Simulator__Functions__

#include <iostream>
#include <vector>
#include <string>

#include "House.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"


const char Pound = 156; //Prints Pound Sterling

bool Yes(std::string Y);

void Pause(std::vector<HumanPlayer> HP);

void DealHands(Deckof52 &Deck, House &Dealer, std::vector<HumanPlayer> &HP, std::vector<ComputerPlayer> &CP);

void ComputerDecision(std::vector<ComputerPlayer> &CP, Deckof52 &Deck, std::vector<HumanPlayer> HP); //Func of Human as well, for Pause(HP)

void HumanEvaluation(std::vector<HumanPlayer> &HP, House &Dealer, bool SixFive);

void ComputerEvaluation(std::vector<ComputerPlayer> &CP, House &Dealer, bool SixFive);



#endif /* defined(__Blackjack_Simulator__Functions__) */
