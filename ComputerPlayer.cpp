//
//  ComputerPlayer.cpp
//  Blackjack Simulator
//
//  Created by Christophe Meyers on 12/12/2013.
//  Copyright (c) 2013 Christophe Meyers. All rights reserved.
//

#include "ComputerPlayer.h"
#include "Functions.h"



ComputerPlayer::ComputerPlayer(std::string PlayerName, double InitialMoney):Player(PlayerName){
    BankRoll = InitialMoney;
}


void ComputerPlayer::SidneyDecision(Deckof52 &Deck){            //Sidney only plays 1 Hand
    GetAllInfo();
    while(Hands[0].PrintedValues().front()<=11){
        std::cout << Name << " hits." << std::endl;
        Hands[0].Cards.push_back(Deck.Hit());
        GetAllInfo();
    }
    if(Hands[0].isBust()){
        std::cout << Name << " is BUST." << std::endl;
    }
    else if(!Hands[0].isBust()){
        std::cout << Name << " sticks." << std::endl;
        std::cout << Name << "'s hand is worth " << Hands[0].PrintedValues().front() << "." << std::endl;
    }
}




void ComputerPlayer::AlexDecision(Deckof52 &Deck){              //Alex only plays 1 Hand
    GetAllInfo();
    while(Hands[0].PrintedValues().front()<21){
        std::cout << Name << " hits." << std::endl;
        Hands[0].Cards.push_back(Deck.Hit());
        GetAllInfo();
    }
    if(Hands[0].isBust()){
        std::cout << Name << " is BUST." << std::endl;
    }
    else if(!Hands[0].isBust()){
        std::cout << Name << " sticks." << std::endl;
        std::cout << Name << "'s hand is worth " << Hands[0].PrintedValues().front() << "." << std::endl;
    }
}

void ComputerPlayer::DarylDecision(Deckof52 &Deck){
    
}

void ComputerPlayer::SamDecision(Deckof52 &Deck){
        
}



void ComputerPlayer::EvaluateWinnings(bool Won, bool SixFive){      //SO FAR JUST FOR ONE HAND
    if(Won){
        if(Hands[0].Cards.size()==2 && Hands[0].GetValue()==21){  //Blackjack Payout
            if(SixFive){
                BankRoll += (6./5.)*Bet;
                std::cout << "£" << (6./5.)*Bet << "." << std::endl;
            }
            else{
                BankRoll += (3./2.)*Bet;
                std::cout << "£" << (3./2.)*Bet << "." << std::endl;
            }
        }
        else{                                   //Normal Win Payout
            BankRoll += Bet;
            std::cout << "£" << Bet << "." << std::endl;
        }
    }
    else{                                       //Loss
        BankRoll -= Bet;
        std::cout << "£" << Bet << "." << std::endl;
    }
}

